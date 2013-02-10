/*
 * ApiObject.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECT_H_
#define APIOBJECT_H_

namespace ymbb10 {
namespace api {
namespace object {

struct ValueType {
	union {
		QString* scalar;
		QMap<QString, ValueType>* complex; // TODO(ebrooks): Legal?
	} value;
	enum { SCALAR, COMPLEX } type;
};

class ApiObject {
public:
	typedef ValueType value_type; // TODO(ebrooks): Use something better herew, boost::any?
	typedef QMap<QString, ValueType> properties_type;
	typedef typename properties_type::iterator iterator;
	typedef typename properties_type::const_iterator const_iterator;

public:
	virtual ~ApiObject() {};
	virtual QString getName() const = 0;
    const_iterator begin() const { return properties_.begin(); }
	const_iterator end() const { return properties_.end(); }
	bool empty() const { return properties_.empty(); }

	virtual QString getContentType() const = 0; // TODO(ebrooks): Not sure if this goes here
												// might be a property for the serializer to return

private:
	properties_type properties_;
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
