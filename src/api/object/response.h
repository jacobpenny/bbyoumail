/*
 * response.h
 *
 *  Created on: Feb 18, 2013
 *      Author: ebrooks
 */

#ifndef RESPONSE_H_
#define RESPONSE_H_

#include "apiobject.h"
#include "constants.h"

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

class Response : public ApiObject {
public:
	static QString getName() const { return "response"; }

	bool hasError() const
	{
		return !errors_.empty();
	}

	bool hasError(QString errorCode, Error* pReturnError = NULL) const {
		for (ListApiObject<Error> e = errors_.begin(); e != errors_.end(); ++e) {
			if (e->getErrorCode() == errorCode) {
				if (NULL != pReturnError) pReturnError = &(*e);
				return true;
			}
		}

		return false;
	}

	Error getError(QString errorCode) const {
		for (ListApiObject<Error> e = errors_.begin(); e != errors_.end(); ++e) {
			if (e->getErrorCode() == errorCode) {
				return *e;
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

class AuthenticationResponse : public Response {
public:
	static QString getName() const { return "authenticationResponse"; }
};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */
#endif /* RESPONSE_H_ */