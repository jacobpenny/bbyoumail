/*
 * AddFolder.h
 *
 *  Created on: 2013-02-10
 *      Author: jpenny
 */

#ifndef ADDFOLDER_H_
#define ADDFOLDER_H_

#include "apiobject.h"

namespace ymbb10 {
namespace api {
namespace method {

class AddFolder : public PostApiMethod<MessageBoxFolder, MessageBoxFolder> {
public:
	AddFolder(const MessageBoxFolder& folder) : PostApiMethod(folder) {}
	virtual ~AddFolder();

	virtual ApiVersion getVersion() const { return VERSION_4; }
	virtual QString getPath() const {
		return QString("messagebox/folders");
	}
};

};
};
};

#endif /* ADDFOLDER_H_ */
