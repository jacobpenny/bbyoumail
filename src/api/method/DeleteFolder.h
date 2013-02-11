/*
 * DeleteFolder.h
 *
 *  Created on: 2013-02-10
 *      Author: jpenny
 */

#ifndef DELETEFOLDER_H_
#define DELETEFOLDER_H_

namespace ymbb10 {
namespace api {
namespace method {

#include "apiobject.h"

class DeleteFolder : DeleteApiMethod<NullApiObject> {
public:
	DeleteFolder(const QString& folderId) : folderId_(folderId) {}
	virtual ~DeleteFolder();

	virtual ApiVersion getVersion() const { return VERSION_4; }
	virtual QString getPath() const {
		QString path = "messagebox/folders/";
		path.append(folderId_);
		return path;
	}

private:
	const QString folderId_;
};

};
};
};

#endif /* DELETEFOLDER_H_ */
