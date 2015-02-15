
#include <stdio.h>

// dependencies (headers)

#include "commons/Config.h"
#include "data/BlobDataService.h"
#include "com/ServerThread.h"

#include "commons/VideoParameters.h"
#include "commons/ImageParameters.h"
#include "core/BlobDetector.h"
#include "core/ThresholdCalibrator.h"
#include "core/BlobDetectorThread.h"

int main()
{
	printf("\nMain thread started!\n");

	BlobsInfoDao* blobsInfoDao = new BlobsInfoDao();
	BlobDataService* dataService = new BlobDataService(blobsInfoDao);

	VideoParameters* videoParams = new VideoParameters(CAM_ID, FRAME_WIDTH, FRAME_HEIGHT);
	ImageParameters* imageParams = new ImageParameters();

//	imageParams->setLowerHsv(ORANGE_LOW_H, ORANGE_LOW_S, ORANGE_LOW_V);
//	imageParams->setUpperHsv(ORANGE_UP_H, ORANGE_UP_S, ORANGE_UP_V);

//	BlobDetector* blobDetector = new BlobDetector(videoParams, imageParams, blobsInfoDao);
	ThresholdCalibrator* calibrator = new ThresholdCalibrator(videoParams, imageParams);

//	ServerThread* serverThread = new ServerThread(5000, 2, dataService);
//	BlobDetectorThread* detectorTread = new BlobDetectorThread(blobDetector);

	calibrator->startHsvCalibration();
//	serverThread->start();
//	detectorTread->start();

//	serverThread->join();
//	detectorTread->join();

	// cleanup
//	delete detectorTread;
//	delete serverThread;
	delete calibrator;
//	delete blobDetector;
	delete videoParams;
	delete imageParams;
	delete dataService;
	delete blobsInfoDao;

	printf("\nMain thread completed!\n");
}
