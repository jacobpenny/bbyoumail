/*
 * pushregistration.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef PUSHREGISTRATION_H_
#define PUSHREGISTRATION_H_

#include "apiobject.h"

namespace ymbb10 {
namespace api {
namespace object {

class PushRegistration : public ApiObject {
public:
	enum Status {
		STATUS_ACTIVE = 1,
		STATUS_ERROR = 9,
		STATUS_INACTIVE = 10,
		STATUS_NOT_AVAILABLE = 11,
		STATUS_INACTIVE_DUE_TO_ERROR = 12,
		STATUS_EXPIRED = 13,
		STATUS_NOT_SUPPORTED = 14
	};

	enum ClientType {
		CLIENT_TYPE_IPHONE = 1,
		CLIENT_TYPE_BLACKBERRY = 2,
		CLIENT_TYPE_ANDROID = 3,
		CLIENT_TYPE_WIN7 = 4,
		CLIENT_TYPE_VOICEPULSE = 5,
		CLIENT_TYPE_RESERVED1 = 6,
		CLIENT_TYPE_RESERVED2 = 7
	};

	PushRegistration();
	static QString getName() { return "pushRegistration"; }

	virtual ~PushRegistration() {}
	virtual QString getContentType() const { return QString(""); } // TODO
	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }


	// TODO: Implementation
private:

};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */
#endif /* PUSHREGISTRATION_H_ */
