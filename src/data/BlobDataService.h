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
		BlobDataService(BlobsInfoDao* dao)
		{ blobsDao = dao; }

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

	private:

		BlobsInfoDao* blobsDao;
		float dataHolder[15] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

		/** Retrieves data for a largest blob from the list of discovered blobs.
		 *  Copies blob data into the array of floats. */
//		void copyBlobData()
//		{
//			if (blobsDao->getBlobsInfo()->size() > 0)
//			{
//				BlobData blobData = blobsDao->getBlobsInfo()->front();
//				blobData.mutex.lock();
//					dataHolder[0] = (float) blobData.blobId;
//					dataHolder[1] = (float) blobData.colorCode;
//					dataHolder[2] = blobData.offsetX;
//					dataHolder[3] = blobData.offsetY;
//					dataHolder[4] = blobData.radius;
//					dataHolder[5] = blobData.width;
//					dataHolder[6] = blobData.height;
//					dataHolder[7] = blobData.angle;
//				blobData.mutex.unlock();
//			}
//		}

		void copyBlobData()
		{
			BlobData blobData = blobsDao->getLargestBlob();
			blobData.mutex.lock();
				dataHolder[0] = 1;
				dataHolder[1] = (float) blobData.blobId;
				dataHolder[2] = (float) blobData.colorCode;
				dataHolder[3] = blobData.offsetX;
				dataHolder[4] = blobData.offsetY;
				dataHolder[5] = blobData.radius;
				dataHolder[6] = blobData.width;
				dataHolder[7] = blobData.height;
				dataHolder[8] = blobData.angle;
			blobData.mutex.unlock();
		}
};

#endif
