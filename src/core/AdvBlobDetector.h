/*
 * AdvBlobDetector.h
 *
 *  Created on: 04/02/2015
 *  Author: zollder
 *  Inspired by: https://code.google.com/p/my-masters-thesis/source/browse/trunk/MastersThesis/Sample/SimpleBlobDetecter_demo.cpp?r=66
 */

// openCV and cvBlob headers
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cvblob.h>

#include <time.h>
#include <iostream>
#include <cmath>

// dependencies (headers)
#include "../commons/Parameters.h"
#include "../data/BlobsInfoDao.h"

// name spaces
using namespace cv;
using namespace cvb;
using namespace std;

#ifndef advblobdetector_h
#define advblobdetector_h

//-----------------------------------------------------------------------------------------
// AdvBlobDetector interface.
//-----------------------------------------------------------------------------------------
class AdvBlobDetector
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		AdvBlobDetector(Parameters params);

		// destructor
		~AdvBlobDetector();

		/**------------------------------------------------------------------------------------
		 * Starts blob detection in HSV color space.
		 * Enables/disables corresponding options with true/false values respectively
		 ------------------------------------------------------------------------------------*/
		int startHsv();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:
		Parameters config;

};

#endif
