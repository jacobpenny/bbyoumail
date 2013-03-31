#include "response.h"
#include <QUuid>

using ymbb10::api::object::ApiResponse;
using ymbb10::api::object::Error;

const QString ymbb10::api::object::Error::INVALID_USER = "InvalidUser";
const QString ymbb10::api::object::Error::TERMS_NOT_AGREED = "TermsNotAgreed";
const QString ymbb10::api::object::Error::ACCOUNT_EXPIRED = "AccountExpired";
const QString ymbb10::api::object::Error::ACCOUNT_DELETED = "AccountDeleted";
const QString ymbb10::api::object::Error::SERVICE_UNAVAILABLE = "ServiceUnavailable";
const QString ymbb10::api::object::Error::UNKNOWN = "Unknown";
const QString ymbb10::api::object::Error::INVALID_AUTH_TOKEN = "InvalidAuthToken";

const QUuid ApiResponse::UUID = QUuid::createUuid();

bool ApiResponse::hasError(QString errorCode, Error* pReturnError = NULL) const {
	for (int i = 0; i < errors_.size(); ++i) {
		if (errors_.typedAt(i)->getErrorCode() == errorCode) {
			if (NULL != pReturnError) *pReturnError = *(errors_.typedAt(i));
			return true;
		}
	}
	return false;
}

Error ApiResponse::getError(QString errorCode) const {
	for (int i = 0; i < errors_.size(); ++i) {
		if (errors_.typedAt(i)->getErrorCode() == errorCode) {
			return *errors_.typedAt(i);
		}
	}
	return Error();
}


const QUuid Error::UUID = QUuid::createUuid();
