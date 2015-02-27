/*
 * BlobDetector.h
 *
 *  Created on: Oct 15, 2014
 *      Author: zollder
 */

// dependencies (headers)
#include "../commons/Parameters.h"
#include "../data/BlobDataService.h"

// openCV and cvBlob headers
#include <cv.h>
#include <highgui.h>
#include <opencv2/opencv.hpp>
#include <cvblob.h>

#include <time.h>
#include <iostream>
#include <cmath>

// name spaces
using namespace cv;
using namespace cvb;
using namespace std;

#ifndef blobdetector_h
#define blobdetector_h

//-----------------------------------------------------------------------------------------
// BlobDetector interface.
//-----------------------------------------------------------------------------------------
class BlobDetector
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		BlobDetector(Parameters params, BlobDataService* service);

		// destructor
		~BlobDetector();

		/**------------------------------------------------------------------------------------
		 * Starts blob detection in HSV color space.
		 * Enables/disables corresponding options with true/false values respectively
		 ------------------------------------------------------------------------------------*/
		int startHsv(bool videoOn, bool fpsOn);

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		// object holders
		Parameters config;
		BlobDataService* dataService;

		// pure RGB color holders
		CvScalar rgbRed, rgbGreen, rgbBlue;

		/**------------------------------------------------------------------------------------
		 * Helper method.
		 * Fills and returns BlobData holder with calculated and retrieved data.
		 --------------------------------------------------------------------------------------*/
		BlobData packageBlobData(CvBlob* blob_p, int width, int height);
};

#endif
