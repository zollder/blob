
#include "BlobDetector.h"

//---------------------------------------------------------------------------------------------
// BlobDetector class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	BlobDetector::BlobDetector(Parameters params, BlobDataService* service)
	{
		printf("\nConstructing BlobDetector ...");
		config = params;
		dataService = service;

		rgbRed = CV_RGB(250, 0, 0);
		rgbGreen = CV_RGB(0, 250, 0);
		rgbBlue = CV_RGB(0, 0, 250);
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	BlobDetector::~BlobDetector()
	{
		printf("\nDestroying BlobDetector ...");
	}


	/**------------------------------------------------------------------------------------
	 * Starts blob detection in HSV color space in FPS test mode.
	 ------------------------------------------------------------------------------------*/
	int BlobDetector::startHsv(bool videoOn, bool fpsOn)
	{
		//-----------------------------fps test variables
	    time_t start, end;
	    double fps, sec;
	    int counter = 0;
	    //-----------------------------

		CvCapture* capture;				// webcam feed structure holder
		CvSize imageSize;				// current frame holder (from the camera feed)

		IplImage *sourceFrame;			// source frame
		IplImage *targetFrame;			// target frame
		IplImage *smoothedFrame;		// blurred frame
		IplImage *hsvFrame;				// frame in the HSV color space
		IplImage *segmentedFrame;		// thresholded frame holder
		IplImage *labelFrame;			// labeled blobs holder

		CvTracks tracks;	// structure to hold tracks
		CvBlobs blobs;		// structure to hold blobs
		CvBlob* blob;		// pointer to the largest blob in the list of blobs

		CvPoint pt1, pt2, pt3, pt4, pt5, pt6;
		int picWidth, picHeight, thickness;

		if (videoOn)
		{
			cvNamedWindow("Webcam Preview", CV_WINDOW_AUTOSIZE);
			cvMoveWindow("Webcam Preview", 100, 100);
		}

	    capture = cvCaptureFromCAM(config.camId);
	    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, config.frameWidth);
	    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, config.frameHeight);

	    sourceFrame = cvRetrieveFrame(capture);
	    if (sourceFrame == NULL) {
	        return -1;
	    }

	    imageSize = cvGetSize(sourceFrame);
	    printf("\nFrame width (pixels): %d | Frame height (pixels): %d", imageSize.width, imageSize.height);

		targetFrame = cvCreateImage(imageSize, sourceFrame->depth, sourceFrame->nChannels);
		smoothedFrame = cvCreateImage(imageSize, targetFrame->depth, targetFrame->nChannels);
		hsvFrame = cvCreateImage(imageSize, targetFrame->depth, targetFrame->nChannels);
		segmentedFrame = cvCreateImage(imageSize, targetFrame->depth, 1);
		labelFrame = cvCreateImage(imageSize, IPL_DEPTH_LABEL, 1);

		printf("\nFrame depth: %d | Frame channels: %d", sourceFrame->depth, sourceFrame->nChannels);

		// fps test
		if (fpsOn)
			time(&start);

		bool quit = false;
		while (!quit && cvGrabFrame(capture))
		{
			sourceFrame = cvRetrieveFrame(capture);
			if(!sourceFrame)
			{
				printf("\nFrame fault.");
				break;
			}

			// fps test
			if (fpsOn)
			{
				time(&end);
				++counter;
				sec = difftime(end, start);
				fps = counter / sec;
				printf("FPS = %.2f\n", fps);
			}

			// copies one array to another with optional scaling and optional type conversion
			// cvConvert can be used instead (scale=1, shift=0 no prescaling is done)
			cvConvertScale(sourceFrame, targetFrame, 1, 0);

			// smoothes the frame with Gaussian filter with 5x5 kernel (done in-place)
			// good results, but slower than other filters (see details on  pp. 111-114 of the "Learning OpenCV")
			cvSmooth(targetFrame, smoothedFrame, CV_GAUSSIAN, 3, 3);

			// converts the frame from RGB to HSV color-space
			cvCvtColor(smoothedFrame, hsvFrame, COLOR_BGR2HSV);

			// TODO: try adaptive thresholding
			// threshold the frame according to predefined lower and upper HSV limits
			cvInRangeS(hsvFrame, config.getLowerHsvLimit(), config.getUpperHsvLimit(), segmentedFrame);

			//morphological opening (removes small objects from the foreground)
			cvMorphologyEx(segmentedFrame, segmentedFrame, 0, 0, CV_MOP_OPEN, 1);

			//morphological closing (removes small holes from the foreground)
			cvMorphologyEx(segmentedFrame, segmentedFrame, 0, 0, CV_MOP_CLOSE, 1);

			// find, filter (by area) and render blobs
			cvLabel(segmentedFrame, labelFrame, blobs);
			cvFilterByArea(blobs, 500, 1000000);
			cvRenderBlobs(labelFrame, blobs, targetFrame, targetFrame, CV_BLOB_RENDER_COLOR, 0.5);

			// update and render blob tracks
			cvUpdateTracks(blobs, tracks, 200., 5);
			cvRenderTracks(tracks, targetFrame, targetFrame, CV_TRACK_RENDER_BOUNDING_BOX, NULL);

			//-----------------------------------------------------------------------------------------
			// Visualize image processing
			//-----------------------------------------------------------------------------------------

			thickness = 1;
			picWidth = targetFrame->width;
			picHeight = targetFrame->height;

			if (videoOn)
			{
				// draw x-axes
		        pt3 = cvPoint(0, picHeight / 2);
		        pt4 = cvPoint(picWidth, picHeight / 2);
		        cvLine(targetFrame, pt3, pt4, rgbRed, thickness);

		        // draw y-axes
		        pt1 = cvPoint(picWidth/2, 0);
		        pt2 = cvPoint(picWidth/2, picHeight);
		        cvLine(targetFrame, pt1, pt2, rgbRed, thickness);
			}

	        // find largest blob (biggest area).
	        int largestBlobIndex = cvGreaterBlob(blobs);
	        if (largestBlobIndex)
	        {
	            blob = blobs[largestBlobIndex];
	            pt5 = cvPoint(picWidth/2, picHeight/2);
	            pt6 = cvPoint(blob->centroid.x, blob->centroid.y);
	            cvLine(targetFrame, pt5, pt6, rgbGreen, thickness);
	            cvCircle(targetFrame, pt6, 3, rgbGreen, 2, CV_FILLED, 0);

	            BlobData tempBlobData = packageBlobData(blob, picWidth, picHeight);

	            dataService->blobData->mutex.lock();
					dataService->blobData->blobId = tempBlobData.blobId;
					dataService->blobData->colorCode = tempBlobData.colorCode;
					dataService->blobData->centroidX = tempBlobData.centroidX;
					dataService->blobData->centroidY = tempBlobData.centroidY;
					dataService->blobData->offsetX = tempBlobData.offsetX;
					dataService->blobData->offsetY = tempBlobData.offsetY;
					dataService->blobData->width = tempBlobData.width;
					dataService->blobData->height = tempBlobData.height;
					dataService->blobData->radius = tempBlobData.radius;
					dataService->blobData->angle = tempBlobData.angle;
				dataService->blobData->mutex.unlock();

	            printf("\nBlobs found: %lu", blobs.size());
	            printf("\ncenter-x: %.2f center-y: %.2f", tempBlobData.centroidX, tempBlobData.centroidY);
	            printf("\noffset-x: %.2f offset-y: %.2f", tempBlobData.offsetX, tempBlobData.offsetY);
	            printf("\nradius: %.2f", tempBlobData.radius);
	            printf("\nwidth: %.2f", tempBlobData.width);
	            printf("\nheight: %.2f", tempBlobData.height);
	            printf("\nBLOB LABEL: %d", tempBlobData.blobId);
	        }

            if (videoOn)
            	cvShowImage("Webcam Preview", targetFrame);

			// escape sequence (5ms delay)
			if (waitKey(30) >= 0)
				quit = true;
		}

		// cleanup
		cvReleaseBlobs(blobs);
		cvReleaseImage(&hsvFrame);
		cvReleaseImage(&labelFrame);
		cvReleaseImage(&segmentedFrame);
		cvReleaseImage(&smoothedFrame);
		cvReleaseImage(&targetFrame);
		cvReleaseImage(&sourceFrame);

		cvDestroyAllWindows();
		cvReleaseCapture(&capture);

		return 0;
	}


	/**------------------------------------------------------------------------------------
	 * Helper method.
	 * Fills and returns BlobData holder with calculated and retrieved data.
	 --------------------------------------------------------------------------------------*/
	BlobData BlobDetector::packageBlobData(CvBlob* blob_p, int width, int height)
	{
		CvPoint origin = cvPoint(width/2, height/2);
		CvPoint blobCentroid = cvPoint(blob_p->centroid.x, blob_p->centroid.y);

		BlobData blobDataHolder;

		// TODO: implement another mechanism for blob tracking, as the current one is not reliable
		blobDataHolder.blobId = blob_p->label;

		// TODO: determine mean color and map it to color codes
		// for now: 1-red, 2-green, 3-blue, 4-orange
		blobDataHolder.colorCode = 1;

		blobDataHolder.centroidX = (float) blob_p->centroid.x;
		blobDataHolder.centroidY = (float) blob_p->centroid.y;
		blobDataHolder.offsetX = (float) (width/2)-(blob_p->centroid.x);
		blobDataHolder.offsetY = (float) (height/2)-(blob_p->centroid.y);
		blobDataHolder.width = (float) blob_p->maxx - blob_p->minx;
		blobDataHolder.height = (float) blob_p->maxy - blob_p->miny;
		blobDataHolder.radius = (float) cvDistancePointPoint(blobCentroid, origin);
		blobDataHolder.angle = (float) cvAngle(blob_p) * 57.2957795;

		return blobDataHolder;
	}
