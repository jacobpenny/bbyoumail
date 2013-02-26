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
	virtual ~ApiObject() {};
	virtual QString getContentType() const = 0; // TODO(ebrooks): Not sure if this goes here
												// might be a property for the serializer to return
	virtual void accept(ApiObjectVisitor*) = 0;
};

class NullApiObject : public ApiObject {
public:
	static QString getName() { return ""; }
	virtual QString getContentType() const { return ""; }
};


class ListApiObjectBase : ApiObject {
public:
	virtual ApiObject* operator[](int) = 0;
	virtual int size() = 0;

	virtual void push_back(ApiObject*) = 0;
	virtual bool empty() = 0;

	virtual QString getName() = 0;
};

template < typename T >
class ListApiObject : public ListApiObjectBase <T> {
public:
	virtual ApiObject* operator[](int i) {
		ApiObject* p = dynamic_cast<ApiObject*>(&list_[i]);
		return p;
	}

	virtual int size() { return list_.size(); }

	virtual void push_back(ApiObject obj) { list_.push_back(obj); }

	virtual bool empty() const { return list_.empty(); }

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	virtual QString getName() { return pluralize(T::getName()); }

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

/*
template < typename T >
class ListApiObject : public ListApiObjectBase {
public:
	virtual QString getName() { return pluralize(T::getName()); }

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

};
*/

};
};
};

#endif /* APIOBJECT_H_ */
