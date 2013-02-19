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
	virtual QString getContentType() const = 0; // TODO(ebrooks): Not sure if this goes here
												// might be a property for the serializer to return
};

class NullApiObject : public ApiObject {
public:
	static QString getName() const { return ""; }
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

	QString getName() { return pluralize(T::getName()); }
	// Finish implementing me

private:
	QList<T> list_;

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
		/*
		if (qs.right(1) == "s" || qs.right(1) == "x") {
			return qs.append("es");
		} else if (qs.right(1) == "y") {
			return qs.left(qs.size() - 1).append("ies");
		} else {
			return qs.append("s");
		}*/
	}

};

};
};
};

#endif /* APIOBJECT_H_ */
