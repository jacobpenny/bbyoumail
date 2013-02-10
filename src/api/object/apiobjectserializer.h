/*
 * apiobjectserializer.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECTSERIALIZER_H_
#define APIOBJECTSERIALIZER_H_

#include "apiobject.h"

class ApiObjectSerializer {
	virtual ~ApiObjectSerializer();
	virtual ApiObject toApiObject(const QByteArray&) = 0;
	virtual void fromApiObject(const ApiObject&, QByteArray&) = 0;
};

#endif /* APIOBJECTSERIALIZER_H_ */
