
#include "Mutex.h"

#ifndef blobdata_h
#define blobdata_h

// blob data structure declaration: single blob info holder
struct BlobData
{
	// general info
	int blobId;
	int colorCode;

	// blob's center coordinates(pixels)
	float centroidX;
	float centroidY;

	// blob's offset from the axes
	float offsetX;
	float offsetY;

	// dimensions (pixels)
	float width;
	float height;
	float radius;

	// blob's angle orientation
	float angle;

	// blob tracking parameters
	int lifetime;	// # of frames the blob exists
	int active;		// # of frames the blob is active from the last inactive period
	int inactive;	// # of frames the blob was missing

	// read/write protection mechanism
	Mutex mutex;
};


#endif
