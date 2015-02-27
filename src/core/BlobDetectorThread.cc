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
	BlobDetectorThread::BlobDetectorThread(BlobDetector* detector, int threadId)
	{
		printf("Constructing BlobDetectorThread ...\n");

		setThreadId(threadId);
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
		//	blobDetector->startHsvCalibration(false);
		blobDetector->startHsv(true, true);

		return NULL;
	}

