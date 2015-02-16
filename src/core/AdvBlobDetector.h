/*
 * AdvBlobDetector.h
 *
 *  Created on: 04/02/2015
 *  Author: zollder
 *  Inspired by: https://code.google.com/p/my-masters-thesis/source/browse/trunk/MastersThesis/Sample/SimpleBlobDetecter_demo.cpp?r=66
 */

// dependencies (headers)
#include "../commons/VideoParameters.h"
#include "../commons/ImageParameters.h"
#include "../data/BlobsInfoDao.h"

// openCV and cvBlob headers
#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <cvblob.h>

#include <time.h>
#include <iostream>
#include <cmath>

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
		AdvBlobDetector(VideoParameters *video_p, ImageParameters* image_p);

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

		// object holders
		VideoParameters* videoParams;
		ImageParameters* imageParams;
};

#endif
