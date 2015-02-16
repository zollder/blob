
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
	params.setCameraId(0);
	params.setLowerHsv(86, 36, 54);
	params.setUpperHsv(117, 121, 255);

	BlobDetector* blobDetector = new BlobDetector(params, blobsInfoDao);
	SocketServer* socketServer = new SocketServer(dataService);

//	ThresholdCalibrator* calibrator = new ThresholdCalibrator(params);
//	calibrator->startHsvCalibration();

	ServerThread* serverThread = new ServerThread(socketServer);
	BlobDetectorThread* detectorTread = new BlobDetectorThread(blobDetector);

	serverThread->start();
	detectorTread->start();

	serverThread->join();
	detectorTread->join();

	// cleanup
//	delete calibrator;
	delete detectorTread;
	delete serverThread;
	delete socketServer;
	delete blobDetector;
	delete dataService;
	delete blobsInfoDao;

	printf("\nMain thread completed!\n");
}
