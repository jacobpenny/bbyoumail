/*
 * storagemanager.h
 *
 *  Created on: Feb 19, 2013
 *      Author: ebrooks
 */

#ifndef STORAGEMANAGER_H_
#define STORAGEMANAGER_H_


#include <QByteArray>

namespace ymbb10 {
namespace storage {

class StorageManager {
public:
	virtual ~StorageManager() = 0;

protected:
	virtual void onCreate() = 0;
	virtual void onUpgrade(int oldVersion, int newVersion) = 0;
	virtual void onOpen(bool readOnly) = 0;
	virtual void onDestroy() = 0;

	virtual void onExport(QByteArray* pOut) = 0;
};


inline StorageManager::~StorageManager() {}
} /* namespace storage */
} /* namespace ymbb10 */
#endif /* STORAGEMANAGER_H_ */
