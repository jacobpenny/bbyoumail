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

using ymbb10::api::method::ApiMethod;
using ymbb10::api::method::ApiMethodBase;
using ymbb10::api::method::Authenticate;
using ymbb10::api::object::ApiObject;
using ymbb10::api::object::ApiResponse;
using ymbb10::api::object::ApiObjectVisitor;
using ymbb10::api::object::ApiObjectVisitorFactory;
using ymbb10::api::object::ApiObjectSerializer;
using ymbb10::api::object::ApiObjectDeserializer;

namespace ymbb10 {
namespace api {

ApiClient::ApiClient(QString apiRoot, QString userAgent, bb::cascades::Application *app)
	: apiRoot_(apiRoot), userAgent_(userAgent), QObject(app) {

	pNetworkAccessManager_ = new QNetworkAccessManager(this);
	bool success = QObject::connect(pNetworkAccessManager_, SIGNAL(finished(QNetworkReply*)),
	        this, SLOT(onResponse(QNetworkReply*)));
	Q_ASSERT(success);
}

void ApiClient::execute(QSharedPointer<ApiMethodBase> method) {
	QNetworkReply* pReply = queueRequest(method);
	logOutgoingRequest(method, pReply);
	requests_.insert(pReply, method);
}

void ApiClient::logOutgoingRequest(QSharedPointer<ApiMethodBase> method, QNetworkReply* pReply) {
	QList<QByteArray> requestHeaders = pReply->request().rawHeaderList();
	QList<QByteArray>::const_iterator i;

	qDebug() << "Requesting " << method->getPath() << ", requestObject is "
			<< (method->hasRequestObject() ? "not NULL" : "NULL")
			<< " request headers follow\n";
	for (i = requestHeaders.begin(); i != requestHeaders.end(); ++i) {
		qDebug() << QString(*i) << "\n";
	}
}

QNetworkReply* ApiClient::queueRequest(QSharedPointer<ApiMethodBase> method) {
	// Q_ASSERT(NULL != method);
	qDebug() << "Entering queueRequest()";
	QString hostAndPath = apiRoot_ + getVersionPathSegment(method) + method->getPath();
	QUrl url(hostAndPath);
	url.setScheme(getScheme(method));

	if (isAuthenticated()) {
		url.addQueryItem(getAuthQueryParam(method), authToken_);
	}

	QSharedPointer<ApiObject> requestObj = method->getRequestObject();

	QNetworkRequest networkRequest(url);
	networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, "application/xml");
	networkRequest.setRawHeader("User-Agent", userAgent_.toLocal8Bit()); // or toLatin1() ?

	if (method->hasRequestObject()) {
		QByteArray outBuffer;
		ApiObjectVisitor* pSerializer = objectSerializerFactory_.create(&outBuffer); // suspicious, outBuffer will go out of scope
		method->getRequestObject()->accept(pSerializer);

		Q_ASSERT(0 != outBuffer.size());
		networkRequest.setHeader(QNetworkRequest::ContentLengthHeader, outBuffer.size());

		return makeRequest(method->getHttpVerb(), networkRequest, &outBuffer);
	} else {
		return makeRequest(method->getHttpVerb(), networkRequest, NULL);
	}
}

QNetworkReply* ApiClient::makeRequest(HttpVerb verb, QNetworkRequest& networkRequest, QByteArray* pRequestBody) {

	switch (verb) {
	case method::HTTP_GET:
		// Q_ASSERT(0 == pRequestBody->size()); // pRequestBody is null in this case.
		return pNetworkAccessManager_->get(networkRequest);

	case method::HTTP_PUT:
		return NULL != pRequestBody
				? pNetworkAccessManager_->put(networkRequest, *pRequestBody)
						: pNetworkAccessManager_->put(networkRequest, (QIODevice*)NULL); // needs 2nd argument

	case method::HTTP_POST:
		return NULL != pRequestBody
				? pNetworkAccessManager_->post(networkRequest, *pRequestBody)
						: pNetworkAccessManager_->post(networkRequest, (QIODevice*)NULL); // needs 2nd argument

	case method::HTTP_DELETE:
		Q_ASSERT(0 == pRequestBody->size());
		return pNetworkAccessManager_->deleteResource(networkRequest);
	}

	// TODO(ebrooks): Log warning, throw exception?
	Q_ASSERT(false);
	return NULL;
}

void ApiClient::onResponse(QNetworkReply* pReply) {
	qDebug() << "entering onResponse()";
	RequestHash::iterator i = requests_.find(pReply);
	Q_ASSERT(requests_.end() != i);

	if (QNetworkReply::NoError == pReply->error()) {
		//
		// Success
		//
		qDebug() << "No errors in pReply";

		ApiObjectVisitor* pObjectDeserializer = objectDeserializerFactory_.create(new QByteArray(pReply->readAll())); // changed bytearray to heap variable
		i.value()->getResponseObject()->accept(pObjectDeserializer);
		notifyOnResponse(i.value(), i.key(), 200, i.value()->getResponseObject());
	} else {
		//
		// Failure
		//
		QVariant statusCode = pReply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
		qWarning() << i.value()->getPath() << " received response code " << statusCode.toInt()
							<< " checking extended error code\n";

		QByteArray responseData = pReply->readAll();
		if (responseData.size() > 0) {
			//
			// Possible extended error response
			//
			QSharedPointer<ApiObject> pErrorResponseObject(new ApiResponse());
			ApiObjectVisitor* pObjectDeserializer = objectDeserializerFactory_.create(&responseData);
			pErrorResponseObject->accept(pObjectDeserializer);
			if (!!pErrorResponseObject) { // TODO(ebrooks): This will always be true
				qWarning() << i.value()->getPath() << " received error object\n";
				notifyOnResponse(i.value(), i.key(), statusCode.toInt(), pErrorResponseObject);
			}
		}
	}
	requests_.erase(i);
}

void ApiClient::notifyOnResponse(QSharedPointer<ApiMethodBase> method, QNetworkReply* pReply, int statusCode, QSharedPointer<ApiObject> pApiObject) {

	// TODO: Use another visitor here for the callbacks?

}

QString ApiClient::getVersionPathSegment(QSharedPointer<ApiMethodBase> method) {
	switch (method->getVersion()) {
	case method::VERSION_3: return "/v3/";
	case method::VERSION_4: return "/v4/";
	}

	return "/v3/"; // default
}

QString ApiClient::getAuthQueryParam(QSharedPointer<ApiMethodBase> method) {
	switch (method->getVersion()) {
	case method::VERSION_3: return "authtoken";
	case method::VERSION_4: return "authToken";
	}

	return "authtoken"; // default
}

QString ApiClient::getScheme(QSharedPointer<ApiMethodBase> method) const {
	switch (useHttps_) {
	case HTTPS_NEVER: return "http";
	case HTTPS_ALWAYS: return "https";
	case HTTPS_AUTH_ONLY:
	{
		// TODO(ebrooks): Expensive, better way of doing this
		Authenticate* pAuth = (Authenticate*)(&method); // changed from dynamic_cast due to compiler error...
		return NULL == pAuth ? "http" : "https";
	}
	}

	return "http"; // default
}

};
};



