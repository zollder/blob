/*
 *	DataService.h
 *  Created on: 15.02.2015
 *	Author: zollder
 */

#include "BlobsInfoDao.h"

#ifndef blobdataservice_h
#define blobdataservice_h

//-----------------------------------------------------------------------------------------
// BlobDataService interface.
//-----------------------------------------------------------------------------------------
class BlobDataService
{
	//-----------------------------------------------------------------------------------------
	// Public members
	//-----------------------------------------------------------------------------------------
	public:

		// constructor
		BlobDataService(BlobData* data)
		{ blobData = data; }

		// destructor
		~BlobDataService() {}

		float* getData()
		{
			// copy blob data into array
			this->copyBlobData();
			return dataHolder;
		}

		int getSize()
		{
			return sizeof(dataHolder);
		}

		BlobData* blobData;

	private:

		float dataHolder[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

		void copyBlobData()
		{
			blobData->mutex.lock();
				dataHolder[0] = 1.0;
				dataHolder[1] = (float) blobData->blobId;
				dataHolder[2] = (float) blobData->colorCode;
				dataHolder[3] = blobData->offsetX;
				dataHolder[4] = blobData->offsetY;
				dataHolder[5] = blobData->angle;
				dataHolder[6] = blobData->radius;
				dataHolder[7] = blobData->width;
				dataHolder[8] = blobData->height;
			blobData->mutex.unlock();
		}
};

#endif
