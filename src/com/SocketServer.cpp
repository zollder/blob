/*
 * SocketServer.cpp
 *
 *      Author: AUV Capstone
 */
#include "SocketServer.h"

//-----------------------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------------------
SocketServer::SocketServer( BlobDataService *data )
{
	init( 5000 , 2 );
	dataService = data;

}

SocketServer::SocketServer( int port, int max , BlobDataService *data)
{
	init( port , max );
	dataService = data;

}
//-----------------------------------------------------------------------------------------
// initialization of variables
//-----------------------------------------------------------------------------------------
void SocketServer::init( int port, int max)
{
	portNumber = port;
	maxUser = max;
	dataService = NULL ;

	// Initialize System Log
	//DEBUG logger = new Logger((char*) "Socket Server [KPI]");
	logger = new Logger("Socket Server [KPI]");

	//Initializing Socket data
	connfd = -1;
	sockfd = -1;

	//Initialize socket structures
	memset(&server_addr, '0', sizeof(server_addr));
	memset(&client_addr, '0', sizeof(client_addr));
}
//-----------------------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------------------
SocketServer::~SocketServer()
{
	stop();
	delete logger;
}
//-----------------------------------------------------------------------------------------
// Class Execution
//-----------------------------------------------------------------------------------------
void SocketServer::start()
{
	if( !dataService )
	{
		logger->error("[ERROR] No Data Holder passing, Not supported for anything else");
		exit(EXIT_FAILURE);
	}

	//create socket inside the kernel and return socket descriptor
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		logger->error("[ERROR] Failed to Open Socket");
		exit(EXIT_FAILURE);
	}

	//initialize server structure
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(portNumber);

	client_len = sizeof(client_addr);

	//bind host address
	if ( bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr) ) < 0)
	{
		int delay=8;
		while( bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr) ) < 0 && --delay)
		{
			//Max Linux delay is 60 seconds by default.
			//creates TIME_WAIT for making sure all socket connection had chance to send data back or from server.
			sleep(10);
		}

		if( delay == 0)
		{
			logger->error("[ERROR] Failed to Bind Socket");
			exit(EXIT_FAILURE);
		}
	}

	logger->info("[INFO] Socket Server initialized");
}

void SocketServer::stop()
{
	// Closing Active Session
	if (connfd < 0)
		logger->notice("[NOTICE] Session already Closed");
	else
	{
		if ( shutdown(connfd, SHUT_RDWR) < 0)
			logger->error("[NOTICE] Invalid session descriptor");
		else
			logger->info("[INFO] Socket Session Closed");

		connfd = -1;
	}

	// Closing Server Socket
	if (sockfd < 0)
	{
		logger->notice("[NOTICE] Socket Server already closed");
	}
	else
	{
		if ( close(sockfd) < 0)
			logger->error("[NOTICE] Failed to Close Socket Server");
		else
			logger->info("[INFO] Socket Server Closed");

		sockfd = -1;
	}
}

void SocketServer::run()
{
	// Start Listening for clients
	listen( sockfd, maxUser );
	logger->info("[INFO] Listening");

	while( sockfd > 1)
	{
		//wait for clients
		connfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *)&client_len);

		if( connfd < 1)
		{
			logger->error( "[ERROR] Failed to Accept Connection");
			close( connfd);
		}
		else
		{
			if( (send(connfd, dataService->getData(), dataService->getSize() ,0 ) ) < 0)
				logger->error( "[ERROR] Failed to Send Buffer to Socket");

			close( connfd);
		}

	}

	logger->info( "[INFO] End Run");
}
