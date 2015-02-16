
#include "AdvBlobDetector.h"

#include <opencv/highgui.h>
#include <opencv2/highgui.hpp>

//---------------------------------------------------------------------------------------------
// AdvBlobDetector class implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	AdvBlobDetector::AdvBlobDetector(VideoParameters *video_p, ImageParameters* image_p)
	{
		printf("\nConstructing AdvBlobDetector ...");

		videoParams = video_p;
		imageParams = image_p;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	AdvBlobDetector::~AdvBlobDetector()
	{
		printf("\nDestroying AdvBlobDetector ...");
	}

	/**------------------------------------------------------------------------------------
	 * Starts blob detection in HSV color space in FPS test mode.
	 ------------------------------------------------------------------------------------*/
	int AdvBlobDetector::startHsv()
	{
	    VideoCapture videoCap(videoParams->cameraId);
	    if (!videoCap.isOpened())
	    	return -1;

	    videoCap.set(CV_CAP_PROP_FRAME_WIDTH, videoParams->captureWidth);
	    videoCap.set(CV_CAP_PROP_FRAME_HEIGHT, videoParams->captureHeight);

	    Mat edges;
	    namedWindow("edges1", 1);
//	    namedWindow("edges2", 1);

		Mat sourceFrame;
		Mat smoothedFrame;
		Mat hsvFrame;
		Mat segmentedFrame;

        vector<KeyPoint> keyPoints;
        vector< vector <Point> > contours;
        vector< vector <Point> > approxContours;

    	// -------------------------------------------------------------------------
        // Initialize blob parameters
        // -------------------------------------------------------------------------

    	// ----------------------------------------------

		// retrieve source frame to determine frame size
		videoCap.retrieve(sourceFrame);

	    bool quit = false;
	    while (!quit)
	    {
	    	// get frame from camera
	    	videoCap >> sourceFrame;
	    	imshow("edges1", sourceFrame);

	    	// prepare image for analysis (smooth, convert to HSV, filter by color, improve)
//	    	GaussianBlur(sourceFrame, smoothedFrame, Size(7,7), 1.5, 1.5);
//	    	cvtColor(smoothedFrame, hsvFrame, COLOR_BGR2HSV);
//	    	inRange(hsvFrame, imageParams->getLowerLimit(), imageParams->getUpperLimit(), segmentedFrame);
//	    	morphologyEx(segmentedFrame, segmentedFrame, CV_MOP_OPEN, 1);
//	    	morphologyEx(segmentedFrame, segmentedFrame, CV_MOP_CLOSE, 2);
//
//	    	Canny(segmentedFrame, segmentedFrame, 0, 30, 3);
//	    	imshow("edges1", sourceFrame);
//	    	imshow("edges2", segmentedFrame);


	    	if (waitKey(30) >= 0)
	    		quit = true;
	    }

	    sourceFrame.release();
	    edges.release();
	    edges.release();
	    videoCap.release();
	    return 0;
	}
