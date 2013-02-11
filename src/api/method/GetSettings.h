/*
 * GetSettings.h
 *
 *  Created on: 2013-02-11
 *      Author: jpenny
 */

#ifndef GETSETTINGS_H_
#define GETSETTINGS_H_

namespace ymbb10 {
namespace api {
namespace method {

class GetSettings : GetApiMethod<Settings> {
public:
	GetSettings();
	virtual ~GetSettings();

	virtual ApiVersion getVersion() const { return VERSION_4; }
	virtual QString getPath() const {
		return QString("settings");
	}
};

};
};
};

#endif /* GETSETTINGS_H_ */
