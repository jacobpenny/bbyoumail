/*
 * apiclient.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APICLIENT_H_
#define APICLIENT_H_

#include <QByteArray>
#include <QString>
#include <QHash>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply> // fwd decl?

#include "api/method/apimethod.h"
#include "api/object/apiobject.h"
#include "api/object/apiobjectvisitor.h"
#include "api/object/apiobjectvisitorfactory.h"
#include "api/object/apiobjectserializer.h"
#include "api/object/apiobjectdeserializer.h"




using ymbb10::api::method::ApiMethod;
using ymbb10::api::method::ApiMethodBase;
using ymbb10::api::method::Authenticate;
using ymbb10::api::object::ApiObject;
using ymbb10::api::object::ApiObjectVisitor;
using ymbb10::api::object::ApiObjectVisitorFactory;
using ymbb10::api::object::ApiObjectSerializer;
using ymbb10::api::object::ApiObjectDeserializer;

namespace ymbb10 {
namespace api {

enum UseHttps {
	HTTPS_NEVER,
	HTTPS_ALWAYS,
	HTTPS_AUTH_ONLY
};

class ApiClient : public QObject {


private:
	typedef QHash<QNetworkReply*, ApiMethodBase> RequestHash;

public:
	ApiClient(QString apiRoot, QString userAgent)
		: apiRoot_(apiRoot), userAgent_(userAgent) {

		pNetworkAccessManager_.reset(new QNetworkAccessManager(this));
		connect(pNetworkAccessManager_.data(),
				SIGNAL(finished(QNetworkReply*)),
		        this, SLOT(onResponse(QNetworkReply*)));
	}

public:
	QString getApiRoot() const { return apiRoot_; }
	void setApiRoot(QString apiRoot) { apiRoot_ = apiRoot; }

	QString getAuthToken() const { return authToken_; }
	void setAuthToken(QString authToken) { authToken_ = authToken; }
	bool isAuthenticated() const { return !authToken_.isEmpty(); }

	QString getUserAgent() const { return userAgent_; }
	void setUserAgent(QString userAgent) { userAgent_ = userAgent; }

private:
	void execute(const ApiMethodBase& method);

	void logOutgoingRequest(const ApiMethodBase& method, QNetworkReply* pReply);

	QNetworkReply* queueRequest(const ApiMethodBase& method);

	QNetworkReply* makeRequest(HttpVerb verb, QNetworkRequest& networkRequest, QByteArray* pRequestBody);

	void onResponse(QNetworkReply* pReply);

	void notifyOnResponse(const ApiMethodBase& method, QNetworkReply* pReply, int statusCode, QSharedPointer<ApiObject> pApiObject);

private:
	QString getVersionPathSegment(const ApiMethodBase& method);
	QString getAuthQueryParam(const ApiMethodBase& method);
	QString getScheme(const ApiMethodBase& method) const;

private:
	QScopedPointer<QNetworkAccessManager> pNetworkAccessManager_;
	RequestHash requests_;

	UseHttps useHttps_;
	QString apiRoot_;
	QString userAgent_;
	QString authToken_;
	ApiObjectVisitorFactory<ApiObjectSerializer> objectSerializerFactory_;
	ApiObjectVisitorFactory<ApiObjectDeserializer> objectDeserializerFactory_;

};

};
};

#endif /* APICLIENT_H_ */
