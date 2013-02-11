/*
 * GetFolders.h
 *
 *  Created on: 2013-02-10
 *      Author: jpenny
 */

#ifndef GETFOLDERS_H_
#define GETFOLDERS_H_

#include "apiobject.h"

namespace ymbb10 {
namespace api {
namespace method {

class GetFolders : public GetApiMethod<ListApiObject<MessageBoxFolder> > {
public:
	GetFolders();
	virtual ~GetFolders();

	virtual ApiVersion getVersion() const { return VERSION_4; }
	virtual QString getPath() const {
		return QString("messagebox/folders");
	}
};

};
};
};

#endif /* GETFOLDERS_H_ */
