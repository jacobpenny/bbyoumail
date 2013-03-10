/*
 * authenticate.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef AUTHENTICATE_H_
#define AUTHENTICATE_H_

#include "api/object/apiobject.h"
#include "api/object/authtoken.h"

namespace ymbb10 {
namespace api {
namespace method {

class Authenticate : public GetApiMethod<object::AuthToken>{
public:
	Authenticate(const QString& uname, const QString& pin) : uname_(uname), pin_(pin) {};

	virtual ApiVersion getVersion() const { return VERSION_3; }
	virtual HttpVerb getHttpVerb() const { return HTTP_GET; }
	virtual QString getPath() const {
		return "authenticate/" + uname_ + ":" + pin_;
	}

	virtual void accept(ApiMethodVisitor* pVisitor) { pVisitor->visit(this); }

private:
	QString uname_;
	QString pin_;
};

} /* namespace method */
} /* namespace api */
} /* namespace ymbb10 */

#endif /* AUTHENTICATE_H_ */
