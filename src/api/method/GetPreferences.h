/*
 * GetPreferences.h
 *
 *  Created on: 2013-02-11
 *      Author: Jacob
 */

#ifndef GETPREFERENCES_H_
#define GETPREFERENCES_H_

namespace ymbb10 {
namespace api {
namespace method {

class GetPreferences : GetApiMethod<Preferences> {
public:
	GetPreferences(const QString& phone) : phone_(phone) {}
	virtual ~GetPreferences();

	virtual ApiVersion getVersion() const { return VERSION_4; }
	virtual QString getPath() const {
		QString path = "accounts/phone/";
		path.append(phone_);
		return path;
	}

private:
	const QString phone_;
};

};
};
};

#endif /* GETPREFERENCES_H_ */
