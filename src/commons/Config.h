/*
 * Config.h
 * Global shared configuration holder.
 */

#ifndef config_h
#define config_h

/* ----------------------------------------------------
 * Camera parameters
 ------------------------------------------------------*/
#define CAM_ID 0
#define FRAME_WIDTH 1024
#define FRAME_HEIGHT 768


/* ----------------------------------------------------
 * Color settings
 ------------------------------------------------------*/

/* Upper orange HSV values */
#define ORANGE_LOW_H 100
#define ORANGE_LOW_S 153
#define ORANGE_LOW_V 214

/* Lower orange HSV values */
#define ORANGE_UP_H 124
#define ORANGE_UP_S 255
#define ORANGE_UP_V 255

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
