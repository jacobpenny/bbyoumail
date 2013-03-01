/*
 * apiobjectvisitorfactory.h
 *
 *  Created on: Feb 24, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECTVISITORFACTORY_H_
#define APIOBJECTVISITORFACTORY_H_

#include <QByteArray>

#include "apiobjectvisitor.h"
#include "apiobjectdeserializer.h"
#include "apiobjectserializer.h"

namespace ymbb10 {
namespace api {
namespace object {

template <typename T>
class ApiObjectVisitorFactory {
public:
	virtual ~ApiObjectVisitorFactory() {};
	virtual ApiObjectVisitor* create(T* pArg) = 0;
};

class ApiObjectDeserializerFactory : public ApiObjectVisitorFactory<QByteArray> {
public:
	ApiObjectVisitor* create(QByteArray* pArg) {
		return new ApiObjectDeserializer(pArg);
	}
};

class ApiObjectSerializerFactory : public ApiObjectVisitorFactory<QByteArray> {
public:
	ApiObjectVisitor* create(QByteArray* pArg) {
		return new ApiObjectSerializer(pArg);
	}
};


}
}
}



#endif /* APIOBJECTVISITORFACTORY_H_ */
