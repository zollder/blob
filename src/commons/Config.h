/*
 * Config.h
 * Global shared configuration holder.
 */

#ifndef config_h
#define config_h

/* ----------------------------------------------------
 * Socket server/client parameters
 ------------------------------------------------------*/
#define SERVER_THREAD_ID 8
#define CLIENT_THREAD_ID 10

#define CLIENT_THREAD_INTERVAL 3.0

#define SERVER_PORT 5000
#define SERVER_CLIENTS 2

/* ----------------------------------------------------
 * Socket server parameters
 ------------------------------------------------------*/
#define PORT 5000
#define CLIENT_NUM 2

/* ----------------------------------------------------
 * Thread parameters
 ------------------------------------------------------*/
#define OBJECT_DETECTOR_THREAD_ID 1
#define SOCKET_SERVER_THREAD_ID 2

/* ----------------------------------------------------
 * Timer parameters
 ------------------------------------------------------*/
#define OBJECT_DETECTOR_INTERVAL 0.50
#define SOCKET_SERVER_INTERVAL 0.50

#endif
