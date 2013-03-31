/*
 * response.h
 *
 *  Created on: Feb 18, 2013
 *      Author: ebrooks
 */

#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "api/object/apiobject.h"
#include "api/object/apiobjectvisitor.h"
#include "api/constants.h"

// debug
#include "messageboxentry.h"

#include <QDateTime>
#include <QString>

namespace ymbb10 {
namespace api {
namespace object {

class Error : public ApiObject {
public:
	static const QUuid UUID;

	static const QString INVALID_USER;
	static const QString TERMS_NOT_AGREED;
	static const QString ACCOUNT_EXPIRED;
	static const QString ACCOUNT_DELETED;
	static const QString SERVICE_UNAVAILABLE;
	static const QString UNKNOWN;
	static const QString INVALID_AUTH_TOKEN;

public:
	//Overrides
	virtual QList<QString> getProjection() const { return QList<QString>(); }

	virtual const QVariantMap& getContentValues() const { return QVariantMap(); }

	virtual void create(const QVariantMap& contentValues) {}

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	virtual QString getContentType() const { return QString("application/xml"); }

public:
	Error() {}
	virtual ~Error() {}

	static QString getName() { return "error"; }

	QString getErrorCode() const
	{
		return errorCode_;
	}

	void setErrorCode(QString errorCode) {
		errorCode_ = errorCode;
	}

	QString getLongMessage() const {
		return longMessage_;
	}

	void setLongMessage(QString longMessage) {
		longMessage_ = longMessage;
	}

	QString getShortMessage() const {
		return shortMessage_;
	}

	void setShortMessage(QString shortMessage) {
		shortMessage_ = shortMessage;
	}



private:
	QString errorCode_;
	QString shortMessage_;
	QString longMessage_;
};


class ApiResponse : public ApiObject {
public:
	static const QUuid UUID;
public:
	//Overrides
	virtual QList<QString> getProjection() const { return QList<QString>(); }

	virtual const QVariantMap& getContentValues() const { return QVariantMap(); }

	virtual void create(const QVariantMap& contentValues) {}

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	virtual QString getContentType() const { return QString("application/xml"); }

public:
	virtual QString getName() const { return "response"; }

	bool hasError() const
	{
		return !errors_.empty();
	}

	bool hasError(QString errorCode, Error* pReturnError) const;

	Error getError(QString errorCode) const;

	const ListApiObject<Error>& getErrors() const
	{
		return errors_;
    }

	ListApiObject<Error>& getErrors()
	{
		return errors_;
	}

	void setErrors(const ListApiObject<Error>& errors)
	{
		errors_ = errors;
	}

	statuscode_t getStatusCode() const
	{
		return statusCode_;
	}

	void setStatusCode(statuscode_t statusCode)
	{
		statusCode_ = statusCode;
	}

	QDateTime getTimestamp() const
	{
		return timestamp_;
	}

	void setTimestamp(QDateTime timestamp)
	{
		timestamp_ = timestamp;
	}

private:
	statuscode_t statusCode_;
	QDateTime timestamp_;
	ListApiObject<Error> errors_;
};

class AuthenticationResponse : public ApiResponse {
public:
	virtual QString getName() const { return "authenticationResponse"; }
};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */

#endif /* RESPONSE_H_ */
