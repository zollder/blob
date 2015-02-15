/*
 * ServerThread.h
 *
 *      Author: AUV Capstone
 */

#include "../sys/BaseThread.h"
#include "SocketServer.h"
#include <signal.h>

#ifndef serverthread_h
#define serverthread_h

class ServerThread : public BaseThread
{
	public:

		ServerThread(int port, int connections, BlobDataService* service);
		~ServerThread();

		void* run();				// overrides BaseThread's run() method

		int stop();
		int kill();

	private:

		SocketServer* server;

};



#endif /* SRC_COMMUNICATION_SERVERTHREAD_H_ */
