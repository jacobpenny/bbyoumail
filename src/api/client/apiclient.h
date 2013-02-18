/*
 * apiclient.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APICLIENT_H_
#define APICLIENT_H_

#include <QString>
#include <QUrl>
#include <QNetworkReply>
#include <QNetworkAccessManager>

#include <QScopedPointer>

#include "api/method/apimethod.h"
#include "api/method/authenticate.h"
#include "api/object/apiobject.h"
#include "api/object/apiobjectserializer.h"

using ymbb10::method::ApiMethod;
using ymbb10::method::Authenticate;
using ymbb10::object::ApiObject;
using ymbb10::object::ApiObjectSerializer;

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
	bool isAuthenticated() const { return !authToken_.empty(); }

	QString getUserAgent() const { return userAgent_; }
	void setUserAgent(QString userAgent) { userAgent_ = userAgent; }

	void execute(const ApiMethodBase& method) {
		QNetworkReply* pReply = queueRequest(method);

		logOutgoingRequest(method, pReply);

		requests_.insert(pReply, method);
	}

private:
	void logOutgoingRequest(const ApiMethodBase& method, QNetworkReply* pReply) {
		QList<QByteArray> requestHeaders = pReply->request().rawHeaderList();
		QList<QByteArray>::const_iterator i;

		qDebug() << "Requesting " << method.getPath() << ", requestObject is "
				<< (method.hasRequestObject() ? "not NULL" : "NULL")
				<< " request headers follow\n";
		for (i = requestHeaders.begin(); i != requestHeaders.end(); ++i) {
			qDebug() << QString(*i) << "\n";
		}
	}

	QNetworkReply* queueRequest(const ApiMethodBase& method) {
		Q_ASSERT(NULL != method);

		QString hostAndPath = apiRoot_ + getVersionPathSegment(method) + method.getPath();
		QUrl url(hostAndPath);
		url.setScheme(getScheme(method));

		if (isAuthenticated()) {
			url.addQueryItem(getAuthQueryParam(method), authToken_);
		}

		QNetworkRequest networkRequest(url);
		networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, pSerializer_->getContentType());
		networkRequest.setRawHeader("User-Agent", userAgent_);

		ApiObject* pObj = method.getRequestObject();
		QByteArray objXml;
		if (NULL != pObj) {
			pSerializer_->fromApiObject(pObj, objXml);
			Q_ASSERT(0 != objXml.size());
			networkRequest.setHeader(QNetworkRequest::ContentLengthHeader, objXml.size());
		}

		switch (method.getHttpVerb()) {
		case HTTP_GET:
			Q_ASSERT(0 == objXml.size());
			return networkAccessManager_.get(networkRequest);

		case HTTP_PUT:
			return objXml.size() > 0
					? networkAccessManager_.put(networkRequest, objXml)
					: networkAccessManager_.put(networkRequest);

		case HTTP_POST:
			return objXml.size() > 0
					? networkAccessManager_.post(networkRequest, objXml)
					: networkAccessManager_.post(networkRequest);

		case HTTP_DELETE:
			Q_ASSERT(0 == objXml.size());
			return networkAccessManager_.deleteResource(networkRequest);
		}

		// TODO(ebrooks): Log warning, throw exception?
		Q_ASSERT(false);
		return NULL;
	}

	void onResponse(QNetworkReply* pReply) {
		RequestHash::iterator i = requests_.find(pReply);
		Q_ASSERT(requests_.end() != i);

		if (QNetworkReply::NoError == pReply->error()) {
			//
			// Success
			//
			QByteArray responseData = pReply->readAll();
			Q_ASSERT(responseData.size() > 0);
			ApiObject::Pointer pResponseObject = pSerializer_->toApiObject(responseData);
			Q_ASSERT(!!pResponseObject);

			// TODO(ebrooks): Need to call some sort of global callback to notify of new API objects
			// pApiDataCallback_->onResponse(i.data(),
			notifyOnResponse(i.value(), i.key(), 200, pResponseObject);
		} else {
			//
			// Failure
			//
			QVariant statusCode = pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
			qWarn() << i.value().getPath() << " received response code " << statusCode.toInt()
					<< " checking extended error code\n";

			QByteArray responseData = pReply->readAll();
			if (responseData.size() > 0) {
				//
				// Possible extended error response
				//
				ApiObject::Pointer pErrorResponseObject = pSerializer_->toApiObject(responseData);
				if (!!pErrorResponseObject) {
					notifyOnResponse(i.value(), i.key(), statusCode.toInt(), pErrorResponseObject);
				}
			}
		}

		requests_.erase(i);
	}

	void notifyOnResponse(const ApiMethodBase& method, QNetworkReply* pReply, int statusCode, ApiObject::Pointer pApiObject) {

	}

private:
	QString getVersionPathSegment(const ApiMethodBase& method) {
		switch (method.getVersion()) {
		case ApiVersion.VERSION_3: return "/v3";
		case ApiVersion.VERSION_4: return "/v4";
		}

		return "/v3"; // default
	}

	QString getAuthQueryParam(const ApiMethodBase& method) {
		switch (method.getVersion()) {
		case ApiVersion.VERSION_3: return "authtoken";
		case ApiVersion.VERSION_4: return "authToken";
		}

		return "authtoken"; // default
	}

	QString getScheme(const ApiMethodBase& method) const {
		switch (useHttps_) {
		case HTTPS_NEVER: return "http";
		case HTTPS_ALWAYS: return "https";
		case HTTPS_AUTH_ONLY:
			{
				// TODO(ebrooks): Expensive, better way of doing this
				Authenticate* pAuth = dynamic_cast<Authenticate*>(&method);
				return NULL == pAuth ? "http" : "https";
			}
		}

		return "http"; // default
	}

private:
	QScopedPointer<QNetworkAccessManager> pNetworkAccessManager_;
	RequestHash requests_;

	UseHttps useHttps_;
	QString apiRoot_;
	QString userAgent_;
	QString authToken_;
	ApiObjectSerializer* pSerializer_;
};

};
};

#endif /* APICLIENT_H_ */
