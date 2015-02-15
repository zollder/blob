/*
 * SocketServer.cpp
 * Author: AUV Capstone
 */
#include "SocketServer.h"

SocketServer::SocketServer( int port, int max , BlobDataService* service)
{
	portNumber = port;
	maxUser = max;
	dataService = service;

	logger = new Logger((char*) "Socket Server [KPI]");
}

SocketServer::~SocketServer()
{
	stop();
	delete logger;
}

void SocketServer::start()
{
	connfd = -1;
	sockfd = -1;

	// create socket inside the kernel and return socket descriptor
	sockfd = socket(AF_INET, SOCK_STREAM, 0);

	if (sockfd < 0)
	{
		logger->error((char*) "[ERROR] Failed to Open Socket");
		exit(EXIT_FAILURE);
	}

	// Initialize socket structures
	memset(&server_addr, '0', sizeof(server_addr));
	memset(&client_addr, '0', sizeof(client_addr));


	//initialize server structure
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(portNumber);

	client_len = sizeof(client_addr);

	//bind host address
	if (bind(sockfd, (struct sockaddr *) &server_addr, sizeof(server_addr) ) < 0)
	{
		logger->error((char*) "[ERROR] Failed to Bind Socket");
		exit(EXIT_FAILURE);
	}

	logger->info((char*) "[INFO] Socket Server initialized");
}

void SocketServer::stop()
{
	// Closing Active Session
	if (connfd < 0)
		logger->notice((char*) "[NOTICE] Session already Closed");
	else
	{
		if (shutdown(connfd, SHUT_RDWR) < 0)
			logger->error((char*) "[DEBUG] Invalid session descriptor");
		else
			logger->info((char*) "[INFO] Socket Session Closed");

		connfd = -1;
	}

	// Closing Server Socket
	if (sockfd < 0)
		logger->notice((char*) "[NOTICE] Socket Server already closed");
	else
	{
		if (close(sockfd) < 0)
			logger->error((char*) "[ERROR] Failed to Close Socket Server");
		else
			logger->info((char*) "[INFO] Socket Server Closed");

		sockfd = -1;
	}
}

void SocketServer::run()
{
	// Start Listening for clients
	listen(sockfd, maxUser);
	logger->info((char*) "[INFO] Listening");

	while (sockfd > 1)
	{
		//wait for clients
		connfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *)&client_len);

		if (connfd < 1)
		{
			logger->error((char*) "[ERROR] Failed to Accept Connection");
			close( connfd);
		}
		else
		{
			if ((send(connfd, dataService->getData(), dataService->getSize(), 0)) < 0)
				logger->error((char*) "[ERROR] Failed to Send Buffer to Socket");

			close (connfd);
		}

	}

	logger->info((char*) "[INFO] End Run");
}
