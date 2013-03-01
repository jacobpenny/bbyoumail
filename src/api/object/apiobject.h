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

#include "apiobjectvisitor.h"

namespace ymbb10 {
namespace api {
namespace object {

class ApiObject {
public:
	virtual ~ApiObject() {}
	virtual QString getContentType() const = 0; // TODO(ebrooks): Not sure if this goes here
												// might be a property for the serializer to return
	virtual void accept(ApiObjectVisitor*) = 0;
};

class NullApiObject : public ApiObject {
public:
	static QString getName() { return ""; }
	virtual QString getContentType() const { return ""; }
	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }
};

class ListApiObjectBase : ApiObject {
public:
	virtual ApiObject* createElement() const = 0;
	virtual int size() const = 0;
	virtual void push_back(ApiObject*) = 0;
	virtual bool empty() const = 0;
	virtual void accept(ApiObjectVisitor*) = 0;
	virtual QString getName() const = 0;
	virtual ApiObject* at(int) = 0;
	virtual const ApiObject* at(int) const = 0;


};

template < typename T >
class ListApiObject : public ListApiObjectBase {
public:
	ListApiObject() : list_(new QList<T>) {}
	virtual ~ListApiObject() { delete list_; }

	virtual QString getContentType() const { return QString(""); } // stub
	ApiObject* createElement() const { return QScopedPointer<ApiObject>(new T()); }
	virtual int size() const { return list_.size(); }
	virtual void push_back(ApiObject* pObj) { list_.push_back(*(dynamic_cast<T*>(pObj))); }
	virtual bool empty() const { return list_.empty(); }
	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }
	virtual QString getName() const { return pluralize(T::getName()); }

	virtual ApiObject* at(int i) { return &list_[i]; }
	virtual const ApiObject* at(int i) const { return &list_[i]; }

	T* typedAt(int i) { return &list_[i]; }
	const T* typedAt(int i) const { return &list_[i]; }

private:
	QString pluralize(const QString& qs) {
		Q_ASSERT(qs.size() > 0);
		QString lastLetter = qs.right(1);
		QByteArray c = lastLetter.toAscii();
		char lastChar = c[0];
		switch (lastChar)
		{
			case 's':
				return qs.append("es");
			case 'x':
				return qs.append("es");
			case 'y':
				return qs.left(qs.size() - 1).append("ies");
			default:
				return qs.append("s");
		}
	}

private:
	QList<T> list_;
};

};
};
};

#endif /* APIOBJECT_H_ */
