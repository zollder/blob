/*
 *	BlobDetectorThread.cpp
 *  Created on: 15.02.2015
 *	Author: zollder
 */

#include "BlobDetectorThread.h"

//---------------------------------------------------------------------------------------------
// BlobDetectorThread thread implementation.
//---------------------------------------------------------------------------------------------

	//-----------------------------------------------------------------------------------------
	// Constructor
	//-----------------------------------------------------------------------------------------
	BlobDetectorThread::BlobDetectorThread(BlobDetector* detector)
	{
		printf("Constructing BlobDetectorThread ...\n");

		setThreadId(OBJECT_DETECTOR_THREAD_ID);
		timer = new FdTimer(getThreadId(), OBJECT_DETECTOR_INTERVAL);
		this->blobDetector = detector;
	}

	//-----------------------------------------------------------------------------------------
	// Destructor
	//-----------------------------------------------------------------------------------------
	BlobDetectorThread::~BlobDetectorThread()
	{
		printf("Destroying BlobDetectorThread thread ...\n");
		delete timer;
	}

	//-----------------------------------------------------------------------------------------
	// Overrides BaseThread's run() method
	//-----------------------------------------------------------------------------------------
	void* BlobDetectorThread::run()
	{
//		bool quit = false;
//		while(!quit)
//		{
			//	blobDetector->startHsvCalibration(false);
			blobDetector->startHsv(true, true);
//
//	    	if (waitKey(30) >= 0)
//	    		quit = true;
//		}

		return NULL;
	}

