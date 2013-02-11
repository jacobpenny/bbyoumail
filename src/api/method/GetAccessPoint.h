/*
 * GetAccessPoint.h
 *
 *  Created on: 2013-02-11
 *      Author: jpenny
 */

#ifndef GETACCESSPOINT_H_
#define GETACCESSPOINT_H_

namespace ymbb10 {
namespace api {
namespace method {

class GetAccessPoint : GetApiMethod<AccessPoint>{
public:
	GetAccessPoint(const QString& phone) : phone_(phone) {}
	virtual ~GetAccessPoint();

	virtual ApiVersion getVersion() const { return VERSION_4; }
	virtual QString getPath() const {
		QString path = "accounts/accesspoint/phone/";
		path.append(phone_);
		return path;
	}

private:
	const QString phone_;
};

};
};
};


#endif /* GETACCESSPOINT_H_ */
