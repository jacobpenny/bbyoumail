/*
 * authtoken.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef AUTHTOKEN_H_
#define AUTHTOKEN_H_

#include "apiobject.h"

namespace ymbb10 {
namespace api {
namespace object {

class AuthToken : public ApiObject {
public:
	virtual QString getName() const { return "authToken"; }

	const QString& getAuthToken() const { return authToken_; }
	void setAuthToken(QString& qs) { authToken_ = qs; }

private:
	QString authToken_;
};

}
}
}

#endif /* AUTHTOKEN_H_ */
