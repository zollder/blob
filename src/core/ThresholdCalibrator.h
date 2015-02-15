/*
 * ThresholdCalibrator.h
 *
 *  Created on: Oct 15, 2014
 *      Author: zollder
 */

// dependencies (headers)
#include "../commons/VideoParameters.h"
#include "../commons/ImageParameters.h"
#include "../data/BlobsInfoDao.h"

// openCV and cvBlob headers
#include <cv.h>
#include <opencv/highgui.h>
#include <opencv2/opencv.hpp>
#include <cvblob.h>

#include <time.h>
#include <iostream>
#include <cmath>

// name spaces
using namespace cv;
using namespace cvb;
using namespace std;

#ifndef thresholdcalibrator_h
#define thresholdcalibrator_h

//-----------------------------------------------------------------------------------------
// ThresholdCalibrator interface.
//-----------------------------------------------------------------------------------------
class ThresholdCalibrator
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		ThresholdCalibrator(VideoParameters *video_p, ImageParameters* image_p);

		// destructor
		~ThresholdCalibrator();

		/**------------------------------------------------------------------------------------
		 * Starts blob detection in calibration mode.
		 * Allows to determine color threshold values with high precision.
		 ------------------------------------------------------------------------------------*/
		int startHsvCalibration();

	//-----------------------------------------------------------------------------------------
	// Private members
	//-----------------------------------------------------------------------------------------
	private:

		// object holders
		VideoParameters* videoParams;
		ImageParameters* imageParams;
};

#endif
