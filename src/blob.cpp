
#include <stdio.h>

// dependencies (headers)

#include "commons/Config.h"
#include "data/BlobDataService.h"
#include "com/ServerThread.h"

#include "commons/Parameters.h"
#include "core/BlobDetector.h"
#include "core/ThresholdCalibrator.h"
#include "core/BlobDetectorThread.h"
#include "core/AdvBlobDetector.h"

int main()
{
	printf("\nMain thread started!\n");

	BlobsInfoDao* blobsInfoDao = new BlobsInfoDao();
	BlobDataService* dataService = new BlobDataService(blobsInfoDao);

	Parameters params;
	params.setCameraId(1);
	params.setLowerHsv(86, 36, 54);
	params.setUpperHsv(117, 121, 255);

//	AdvBlobDetector* detector = new AdvBlobDetector(params);
//	detector->startHsv();

	BlobDetector* blobDetector = new BlobDetector(params, blobsInfoDao);
//	ThresholdCalibrator* calibrator = new ThresholdCalibrator(params);

//	ServerThread* serverThread = new ServerThread(5000, 2, dataService);
	BlobDetectorThread* detectorTread = new BlobDetectorThread(blobDetector);

//	blobDetector->startHsv(true, true);
//	calibrator->startHsvCalibration();
//	serverThread->start();
	detectorTread->start();

//	serverThread->join();
	detectorTread->join();

	// cleanup
	delete detectorTread;
//	delete serverThread;
//	delete calibrator;
	delete blobDetector;
//	delete detector;
	delete dataService;
	delete blobsInfoDao;

	printf("\nMain thread completed!\n");
}
