/*
 * ServerThread.cpp
 *
 *      Author: AUV Capsone
 */


#include "ServerThread.h"

//-----------------------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------------------

ServerThread::ServerThread(int port, int connections, BlobDataService* dataService)
{
	setThreadId(SOCKET_SERVER_THREAD_ID);
	server = new SocketServer(port , connections , dataService);
}

//-----------------------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------------------
ServerThread::~ServerThread()
{
	delete server;
}

//-----------------------------------------------------------------------------------------
// Overrides BaseThread's run() method
//-----------------------------------------------------------------------------------------
void* ServerThread::run()
{
	syslog(LOG_NOTICE,"[KPI::THREAD] START");

	server->start();
	server->run();

	syslog(LOG_NOTICE,"[KPI::THREAD] END");

	return NULL;
}

int ServerThread::stop()
{
	syslog(LOG_NOTICE,"[KPI::THREAD] STOP");
	server->stop();
	return pthread_cancel(getThreadId());
}

int ServerThread::kill()
{
	syslog(LOG_NOTICE,"[KPI::THREAD] KILL");
	return pthread_kill(getThreadId() , SIGQUIT);
}


