/*
 * apiclient.cpp
 *
 *  Created on: 2013-02-27
 *      Author: jpenny
 */
#include "apiclient.h"

#include <QUrl>


#include "api/method/authenticate.h"
#include "api/object/apiobjectserializer.h"
#include "api/object/apiobjectdeserializer.h"

/*
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
*/

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

void ApiClient::execute(const ApiMethodBase& method) {
	QNetworkReply* pReply = queueRequest(method);

	logOutgoingRequest(method, pReply);

	requests_.insert(pReply, method);
}

void ApiClient::logOutgoingRequest(const ApiMethodBase& method, QNetworkReply* pReply) {
	QList<QByteArray> requestHeaders = pReply->request().rawHeaderList();
	QList<QByteArray>::const_iterator i;

	qDebug() << "Requesting " << method.getPath() << ", requestObject is "
			<< (method.hasRequestObject() ? "not NULL" : "NULL")
			<< " request headers follow\n";
	for (i = requestHeaders.begin(); i != requestHeaders.end(); ++i) {
		qDebug() << QString(*i) << "\n";
	}
}

QNetworkReply* ApiClient::queueRequest(const ApiMethodBase& method) {
	// Q_ASSERT(NULL != method);

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

QNetworkReply* ApiClient::makeRequest(HttpVerb verb, QNetworkRequest& networkRequest, QByteArray* pRequestBody) {
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

void ApiClient::onResponse(QNetworkReply* pReply) {
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

void ApiClient::notifyOnResponse(const ApiMethodBase& method, QNetworkReply* pReply, int statusCode, QSharedPointer<ApiObject> pApiObject) {

	// TODO: Use another visitor here for the callbacks?

}

QString ApiClient::getVersionPathSegment(const ApiMethodBase& method) {
	switch (method.getVersion()) {
	case ApiVersion.VERSION_3: return "/v3";
	case ApiVersion.VERSION_4: return "/v4";
	}

	return "/v3"; // default
}

QString ApiClient::getAuthQueryParam(const ApiMethodBase& method) {
	switch (method.getVersion()) {
	case ApiVersion.VERSION_3: return "authtoken";
	case ApiVersion.VERSION_4: return "authToken";
	}

	return "authtoken"; // default
}

QString ApiClient::getScheme(const ApiMethodBase& method) const {
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


