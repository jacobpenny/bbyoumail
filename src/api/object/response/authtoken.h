/*
 * authtoken.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef AUTHTOKEN_H_
#define AUTHTOKEN_H_

#include "apiobject.h"

class AuthToken : public ApiObject {
public:
	virtual std::string getName() const { return "AuthToken"; }
};

#endif /* AUTHTOKEN_H_ */
