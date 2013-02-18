/*
 * ApiObject.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECT_H_
#define APIOBJECT_H_

#include <QString>
#include <QMap>
#include <QSharedPointer>

namespace ymbb10 {
namespace api {
namespace object {

class ApiObject {
public:
	virtual ~ApiObject() {};
	virtual QString getName() const = 0;
	virtual QString getContentType() const = 0; // TODO(ebrooks): Not sure if this goes here
												// might be a property for the serializer to return
};

class NullApiObject : public ApiObject {
public:
	virtual QString getName() const { return ""; }
	virtual QString getContentType() const { return ""; }
};

template < typename T >
class ListApiObject : public ApiObject {
public:
	typedef typename QList<T>::iterator iterator;
	typedef typename QList<T>::const_iterator const_iterator;

public:
	iterator begin() { return list_.begin(); }
	iterator end() { return list_.end(); }

	const_iterator begin() const { return list_.begin(); }
	const_iterator end() const { return list_.end(); }

	// Finish implementing me

private:
	QList<T> list_;
};

};
};
};

#endif /* APIOBJECT_H_ */
