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
#include <QVariant>
#include <QList>
#include <QUuid>

#include "api/object/apiobjectvisitor.h"

namespace ymbb10 {
namespace api {
namespace object {

class ApiObjectVisitor;

class Visitable {
public:
	virtual ~Visitable() = 0;
	virtual void accept(ApiObjectVisitor*) = 0;
};

class Transient {
public:
	virtual ~Transient() = 0;
	virtual QList<QString> getProjection() const = 0;
	virtual const QVariantMap& getContentValues() const = 0;
	virtual void create(const QVariantMap& contentValues) = 0;
};

class ApiObject : public Visitable, Transient {
public:
	virtual ~ApiObject() {}
	virtual QString getContentType() const = 0; // TODO(ebrooks): Not sure if this goes here
	// might be a property for the serializer to return
};

class ApiObjectFactory {
	virtual ~ApiObjectFactory() = 0;
	virtual ApiObject* create(QVariantMap*) = 0;
};

class NullApiObject : public ApiObject {
public:
	static QString getName() { return "nullObj"; }
	virtual QString getContentType() const { return "nulltastic"; }
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
	static const QUuid UUID;

public:
	//Overrides
	//TODO implementation
	virtual QList<QString> getProjection() const { return QList<QString>(); }

	virtual const QVariantMap& getContentValues() const { return QVariantMap(); }

	virtual void create(const QVariantMap& contentValues) {}

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	virtual QString getContentType() const { return QString("application/xml"); }

public:
	ListApiObject() {}
	virtual ~ListApiObject() {}

	ApiObject* createElement() const { return new T(); }
	virtual int size() const { return list_.size(); }
	virtual void push_back(ApiObject* pObj) { list_.push_back(*(dynamic_cast<T*>(pObj))); }
	virtual bool empty() const { return list_.empty(); }
	virtual QString getName() const { return pluralize(T::getName()); }

	virtual ApiObject* at(int i) { return &list_[i]; }
	virtual const ApiObject* at(int i) const { return &list_[i]; }

	T* typedAt(int i) { return &list_[i]; }
	const T* typedAt(int i) const { return &list_[i]; }

private:
	QString pluralize(const QString& qs) const {
		Q_ASSERT(qs.size() > 0);
		QString result = qs;
		QString lastLetter = result.right(1);
		QByteArray c = lastLetter.toAscii();
		char lastChar = c[0];
		switch (lastChar)
		{
		case 's':
		return result.append("es");
		case 'x':
		return result.append("es");
		case 'y':
		return result.left(qs.size() - 1).append("ies");
		default:
			return result.append("s");
		}
	}

private:
	QList<T> list_;
};


};
};
};

#endif /* APIOBJECT_H_ */
