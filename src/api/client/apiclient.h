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
#include "api/object/apiobjectdeserializer.h"
#include "api/object/apiobjectvisitorfactory.h"

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
	// for some reason, having the data members at the bottom generates errors, e.g apiRoot_ field not found
	// I think we should move the implementation into a cpp file
	QScopedPointer<QNetworkAccessManager> pNetworkAccessManager_;
	RequestHash requests_;

	UseHttps useHttps_;
	QString apiRoot_;
	QString userAgent_;
	QString authToken_;
	ApiObjectVisitorFactory objectSerializerFactory_;
	ApiObjectVisitorFactory objectDeserializerFactory_;

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
	void execute(const ApiMethodBase& method) {
		QNetworkReply* pReply = queueRequest(method);

		logOutgoingRequest(method, pReply);

		requests_.insert(pReply, method);
	}

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

		if (method.hasRequestObject()) {
			QByteArray outBuffer;
			QScopedPointer<ApiObjectVisitor> pSerializer = objectSerializerFactory.create(&outBuffer);
			method.getRequestObject()->accept(pSerializer);

			Q_ASSERT(0 != outBuffer.size());
			networkRequest.setHeader(QNetworkRequest::ContentLengthHeader, outBuffer.size());

			return makeRequest(method.getHttpVerb(), networkRequest, &outBuffer);
		} else {
			return makeRequest(method.getHttpVerb(), networkRequest, NULL);
		}
	}

	QNetworkReply* makeRequest(HttpVerb verb, QNetworkRequest& networkRequest, QByteArray* pRequestBody) {
		switch (verb) {
		case HTTP_GET:
			Q_ASSERT(0 == pRequestBody->size());
			return networkAccessManager_.get(networkRequest);

		case HTTP_PUT:
			return NULL != pRequestBody
					? networkAccessManager_.put(networkRequest, *pRequestBody)
					: networkAccessManager_.put(networkRequest);

		case HTTP_POST:
			return NULL != pRequestBody
					? networkAccessManager_.post(networkRequest, *pRequestBody)
					: networkAccessManager_.post(networkRequest);

		case HTTP_DELETE:
			Q_ASSERT(0 == pRequestBody->size());
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

			QSharedPointer<ApiObjectVisitor> pObjectDeserializer = objectDeserializerFactory.create(&responseData);
			i.value().getResponseObject()->accept(pObjectDeserializer);
			notifyOnResponse(i.value(), i.key(), 200, i.value().getResponseObject());
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
				QSharedPointer<ApiObject> pErrorResponseObject = new ApiResponse();
				pErrorResponseObject->accept(pObjectDeserializer_);
				if (!!pErrorResponseObject) { // TODO(ebrooks): This will always be true
					qWarn() << i.value().getPath() << " received error object\n";
					notifyOnResponse(i.value(), i.key(), statusCode.toInt(), pErrorResponseObject);
				}
			}
		}

		requests_.erase(i);
	}

	void notifyOnResponse(const ApiMethodBase& method, QNetworkReply* pReply, int statusCode, QSharedPointer<ApiObject> pApiObject) {

		// TODO: Use another visitor here for the callbacks?

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


};

};
};

#endif /* APICLIENT_H_ */
