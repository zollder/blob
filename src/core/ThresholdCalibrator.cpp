
#include "ThresholdCalibrator.h"

//---------------------------------------------------------------------------------------------
// ThresholdCalibrator class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	ThresholdCalibrator::ThresholdCalibrator(VideoParameters *video_p, ImageParameters* image_p)
	{
		printf("\nConstructing ThresholdCalibrator ...");

		videoParams = video_p;
		imageParams = image_p;

		rgbRed = CV_RGB(250, 0, 0);
		rgbGreen = CV_RGB(0, 250, 0);
		rgbBlue = CV_RGB(0, 0, 250);
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	ThresholdCalibrator::~ThresholdCalibrator()
	{
		printf("\nDestroying ThresholdCalibrator ...");
	}

	/**------------------------------------------------------------------------------------
	 * Starts HSV color space calibrator with the tracker bars for accurate color filtering.
	 ------------------------------------------------------------------------------------*/
	int ThresholdCalibrator::startHsvCalibration(bool logsOn)
	{
		CvCapture* capture;
		CvSize imageSize;
		IplImage *sourceFrame, *targetFrame, *smoothedFrame, *hsvFrame, *segmentedFrame, *labelFrame;

		CvPoint pt1, pt2, pt3, pt4, pt5, pt6;
		int picWidth, picHeight, thickness;

		CvTracks tracks;
		CvBlobs blobs;
		CvBlob* blob;

		cvNamedWindow("Webcam Preview", CV_WINDOW_AUTOSIZE);
		cvMoveWindow("Webcam Preview", 100, 100);

	    capture = cvCaptureFromCAM(videoParams->cameraId);
	    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_WIDTH, videoParams->captureWidth);
	    cvSetCaptureProperty(capture, CV_CAP_PROP_FRAME_HEIGHT, videoParams->captureHeight);

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
		labelFrame = cvCreateImage(cvGetSize(targetFrame), IPL_DEPTH_LABEL, 1);

		printf("\nFrame depth: %d | Frame channels: %d", sourceFrame->depth, sourceFrame->nChannels);

	    // ===========================================color calibrator start
	    namedWindow("Control",CV_WINDOW_AUTOSIZE);

		int iLowH = 0; int iHighH = 179;
		int iLowS = 0; int iHighS = 255;
		int iLowV = 0; int iHighV = 255;

		cvCreateTrackbar("LowH", "Control", &iLowH, 179); //Hue (0 - 179)
		cvCreateTrackbar("HighH", "Control", &iHighH, 179);

		cvCreateTrackbar("LowS", "Control", &iLowS, 255); //Saturation (0 - 255)
		cvCreateTrackbar("HighS", "Control", &iHighS, 255);

		cvCreateTrackbar("LowV", "Control", &iLowV, 255);//Value (0 - 255)
		cvCreateTrackbar("HighV", "Control", &iHighV, 255);
		// ===========================================color calibrator end

		while (cvGrabFrame(capture))
		{
			sourceFrame = cvRetrieveFrame(capture);
			if(!sourceFrame)
			{
				printf("\nFrame fault.");
				break;
			}

			cvFlip(targetFrame, targetFrame, 1);
			cvConvertScale(sourceFrame, targetFrame, 1, 0);
			cvSmooth(targetFrame, smoothedFrame, CV_GAUSSIAN_5x5, 5, 5);
			cvCvtColor(smoothedFrame, hsvFrame, COLOR_BGR2HSV);
			cvInRangeS(hsvFrame, Scalar(iLowH, iLowS, iLowV), Scalar(iHighH, iHighS, iHighV), segmentedFrame);

			cvMorphologyEx(segmentedFrame, segmentedFrame, 0, 0, CV_MOP_OPEN, 2);
			cvMorphologyEx(segmentedFrame, segmentedFrame, 0, 0, CV_MOP_CLOSE, 2);

			cvLabel(segmentedFrame, labelFrame, blobs);
			cvFilterByArea(blobs, 500, 1000000);
			cvRenderBlobs(labelFrame, blobs, targetFrame, targetFrame, CV_BLOB_RENDER_COLOR, 0.5);
			cvUpdateTracks(blobs, tracks, 200., 5);
			cvRenderTracks(tracks, targetFrame, targetFrame, CV_TRACK_RENDER_BOUNDING_BOX, NULL);

	        printf("\nLower threshold: H:%d, S:%d, V:%d", iLowH, iLowS, iLowV);
			printf("\nUpper threshold: H:%d, S:%d, V:%d", iHighH, iHighS, iHighV);

	        cvShowImage("Thresholded Image", segmentedFrame);
			cvShowImage("Webcam Preview", targetFrame);

			// escape sequence
			if (waitKey(10) == 27) //wait for 'esc' key press for 30ms. If 'esc' key is pressed, break loop
				break;

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