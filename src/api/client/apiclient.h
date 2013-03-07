/*
 * apiclient.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APICLIENT_H_
#define APICLIENT_H_

#include <bb/cascades/Application>
#include <QObject>
#include <QByteArray>
#include <QString>
#include <QHash>
#include <QScopedPointer>
#include <QSharedPointer>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkRequest>


#include "api/method/apimethod.h"
#include "api/method/authenticate.h"
#include "api/object/apiobject.h"
#include "api/object/apiobjectvisitor.h"
#include "api/object/apiobjectvisitorfactory.h"
#include "api/object/apiobjectserializer.h"
#include "api/object/apiobjectdeserializer.h"

// must remove these using decls
using ymbb10::api::method::ApiMethod;
using ymbb10::api::method::ApiMethodBase;
using ymbb10::api::method::HttpVerb;
using ymbb10::api::method::Authenticate;
using ymbb10::api::object::ApiObject;
using ymbb10::api::object::ApiObjectVisitor;
using ymbb10::api::object::ApiObjectDeserializerFactory;
using ymbb10::api::object::ApiObjectSerializerFactory;
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
	Q_OBJECT
private slots:
	void onResponse(QNetworkReply* pReply);

private:
	typedef QHash<QNetworkReply*, QSharedPointer<ApiMethodBase> > RequestHash;

public:
	ApiClient(QString apiRoot, QString userAgent, bb::cascades::Application *app, QObject* parent);

public:
	QString getApiRoot() const { return apiRoot_; }
	void setApiRoot(QString apiRoot) { apiRoot_ = apiRoot; }

	QString getAuthToken() const { return authToken_; }
	void setAuthToken(QString authToken) { authToken_ = authToken; }
	bool isAuthenticated() const { return !authToken_.isEmpty(); }

	QString getUserAgent() const { return userAgent_; }
	void setUserAgent(QString userAgent) { userAgent_ = userAgent; }

	void execute(QSharedPointer<ApiMethodBase> method);

signals:
	void responseDeserialized(QSharedPointer<ApiMethodBase> method);

private:
	void logOutgoingRequest(QSharedPointer<ApiMethodBase> method, QNetworkReply* pReply);
	QNetworkReply* queueRequest(QSharedPointer<ApiMethodBase> method);
	QNetworkReply* makeRequest(HttpVerb verb, QNetworkRequest& networkRequest, QByteArray* pRequestBody);
	void notifyOnResponse(QSharedPointer<ApiMethodBase> method, QNetworkReply* pReply, int statusCode, QSharedPointer<ApiObject> pApiObject);

private:
	QString getVersionPathSegment(QSharedPointer<ApiMethodBase> method);
	QString getAuthQueryParam(QSharedPointer<ApiMethodBase> method);
	QString getScheme(QSharedPointer<ApiMethodBase> method) const;

private:
	QNetworkAccessManager* pNetworkAccessManager_;

	RequestHash requests_;

	UseHttps useHttps_;
	QString apiRoot_;
	QString userAgent_;
	QString authToken_;
	ApiObjectSerializerFactory objectSerializerFactory_;
	ApiObjectDeserializerFactory objectDeserializerFactory_;

	QObject* pParent_;



};

};
};

#endif /* APICLIENT_H_ */
