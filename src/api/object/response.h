/*
 * response.h
 *
 *  Created on: Feb 18, 2013
 *      Author: ebrooks
 */

#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "apiobject.h"
#include "apiobjectvisitor.h"
#include "constants.h"

// debug
#include "messageboxentry.h"

#include <QDateTime>
#include <QString>

namespace ymbb10 {
namespace api {
namespace object {

class Error : public ApiObject {
public:
	static const QString INVALID_USER;
	static const QString TERMS_NOT_AGREED;
	static const QString ACCOUNT_EXPIRED;
	static const QString ACCOUNT_DELETED;
	static const QString SERVICE_UNAVAILABLE;
	static const QString UNKNOWN;
	static const QString INVALID_AUTH_TOKEN;

public:
	Error();
	virtual ~Error();

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

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	virtual QString getContentType() const { return QString("application/xml"); }

private:
	QString errorCode_;
	QString shortMessage_;
	QString longMessage_;
};


class ApiResponse : public ApiObject {
public:
	virtual QString getName() const { return "response"; }

	bool hasError() const
	{
		return !errors_.empty();
	}

	bool hasError(QString errorCode, Error* pReturnError = NULL) const {
		for (int i = 0; i < errors_.size(); ++i) {
			if (errors_.typedAt(i)->getErrorCode() == errorCode) {
				if (NULL != pReturnError) *pReturnError = *(errors_.typedAt(i));
				return true;
			}
		}
		return false;
	}

	Error getError(QString errorCode) const {
		for (int i = 0; i < errors_.size(); ++i) {
			if (errors_.typedAt(i)->getErrorCode() == errorCode) {
				return *errors_.typedAt(i);
			}
		}
		return Error();
	}

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
