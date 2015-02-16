/*
 * ServerThread.cpp
 *
 *      Author: AUV Capsone
 */


#include "ServerThread.h"

//-----------------------------------------------------------------------------------------
// Constructors
//-----------------------------------------------------------------------------------------

ServerThread::ServerThread(SocketServer* server)
{
	setThreadId(SOCKET_SERVER_THREAD_ID);
	socketServer = server;
}

//-----------------------------------------------------------------------------------------
// Destructor
//-----------------------------------------------------------------------------------------
ServerThread::~ServerThread()
{
}

//-----------------------------------------------------------------------------------------
// Overrides BaseThread's run() method
//-----------------------------------------------------------------------------------------
void* ServerThread::run()
{
	syslog(LOG_NOTICE,"[KPI::THREAD] START");

	socketServer->start();
	socketServer->run();

	syslog(LOG_NOTICE,"[KPI::THREAD] END");

	return NULL;
}

int ServerThread::stop()
{
	syslog(LOG_NOTICE,"[KPI::THREAD] STOP");
	socketServer->stop();
	return pthread_cancel(getThreadId());
}

int ServerThread::kill()
{
	syslog(LOG_NOTICE,"[KPI::THREAD] KILL");
	return pthread_kill(getThreadId() , SIGQUIT);
}


