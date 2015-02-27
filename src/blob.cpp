
#include <stdio.h>

// dependencies (headers)
#include "data/BlobDataService.h"
#include "com/SocketServer.h"
#include "com/ServerThread.h"

#include "commons/Parameters.h"
#include "core/BlobDetector.h"
#include "core/ThresholdCalibrator.h"
#include "core/BlobDetectorThread.h"

int main()
{
    syslog(LOG_NOTICE,"[KPI::MAIN] START");

    BlobData* blobData = new BlobData();
	BlobDataService* dataService = new BlobDataService(blobData);
	SocketServer* socketServer = new SocketServer(PORT, CONNECTIONS, dataService);

	Parameters params;
	params.setCameraId(0);
	params.setFrameSize(720, 480);
	params.setLowerHsv(90, 36, 131);
	params.setUpperHsv(116, 255, 255);

	BlobDetector* blobDetector = new BlobDetector(params, dataService);

//	ThresholdCalibrator* calibrator = new ThresholdCalibrator(params);
//	calibrator->startHsvCalibration();

	ServerThread* serverThread = new ServerThread(socketServer, SOCKET_SERVER_THREAD_ID);
	BlobDetectorThread* detectorTread = new BlobDetectorThread(blobDetector, OBJECT_DETECTOR_THREAD_ID);

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
	delete blobData;

	printf("\nMain thread completed!\n");
}
