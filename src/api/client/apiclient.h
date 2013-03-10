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
#include <QHash>
#include <QString>
#include <QSharedPointer>

#include "api/method/apimethod.h"
#include "api/object/apiobject.h"
#include "api/object/apiobjectvisitorfactory.h"

class QNetworkReply;

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
	typedef QHash<QNetworkReply*, QSharedPointer<method::ApiMethodBase> > RequestHash;

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

	void execute(QSharedPointer<method::ApiMethodBase> method);

signals:
	void responseDeserialized(ymbb10::api::method::ApiMethodBase* method);

private:
	void logOutgoingRequest(QSharedPointer<method::ApiMethodBase> method, QNetworkReply* pReply);
	QNetworkReply* queueRequest(QSharedPointer<method::ApiMethodBase> method);
	QNetworkReply* makeRequest(method::HttpVerb verb, QNetworkRequest& networkRequest, QByteArray* pRequestBody);
	void notifyOnResponse(QSharedPointer<method::ApiMethodBase> method, QNetworkReply* pReply, int statusCode, QSharedPointer<ApiObject> pApiObject);

private:
	QString getVersionPathSegment(QSharedPointer<method::ApiMethodBase> method);
	QString getAuthQueryParam(QSharedPointer<method::ApiMethodBase> method);
	QString getScheme(QSharedPointer<method::ApiMethodBase> method) const;

private:
	QNetworkAccessManager* pNetworkAccessManager_;

	RequestHash requests_;

	UseHttps useHttps_;
	QString apiRoot_;
	QString userAgent_;
	QString authToken_;
	object::ApiObjectSerializerFactory objectSerializerFactory_;
	object::ApiObjectDeserializerFactory objectDeserializerFactory_;

	QObject* pParent_;



};

};
};

#endif /* APICLIENT_H_ */
