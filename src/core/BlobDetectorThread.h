/*
 *	BlobDetectorThread.h
 *	Created on: 15.02.2015
 *	Author: zollder
 */

#include <highgui.h>

#include "../commons/Config.h"
#include "../sys/BaseThread.h"
#include "../sys/FdTimer.h"

#include "BlobDetector.h"

#ifndef dmuthread_h
#define dmuthread_h

//-----------------------------------------------------------------------------------------
// BlobDetectorThread interface.
//-----------------------------------------------------------------------------------------
class BlobDetectorThread : public BaseThread
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		BlobDetectorThread(BlobDetector* detector);

		// destructor
		~BlobDetectorThread();

		// overrides BaseThread's run() method
		void* run();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		FdTimer* timer;
		BlobDetector* blobDetector;
};

#endif
