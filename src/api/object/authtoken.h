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

class ApiObjectVisitor;

class AuthToken : public ApiObject {
public:
	static const QUuid UUID;

public:
	// Overrides
	virtual QList<QString> getProjection() const { return QList<QString>(); }

	virtual const QVariantMap& getContentValues() const { return QVariantMap(); }

	virtual void create(const QVariantMap& contentValues) {}

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	virtual QString getContentType() const { return QString("authy"); } // TODO imp me

public:
	static QString getName() { return "authToken"; }

	const QString& getAuthToken() const { return authToken_; }
	void setAuthToken(QString qs) { authToken_ = qs; }



private:
	QString authToken_;
};

}
}
}

#endif /* AUTHTOKEN_H_ */
