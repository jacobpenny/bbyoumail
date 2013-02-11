/*
 * apiclient.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APICLIENT_H_
#define APICLIENT_H_

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
public:
	ApiClient(QNetworkAccessManager& nam, QString apiRoot, QString userAgent)
		: networkAccessManager_(nam), apiRoot_(apiRoot), userAgent_(userAgent) {};

public:
	QString getApiRoot() const { return apiRoot_; }
	void setApiRoot(QString apiRoot) { apiRoot_ = apiRoot; }

	QString getUserAgent() const { return userAgent_; }
	void setUserAgent(QString userAgent) { userAgent_ = userAgent; }

	QNetworkReply* execute(ApiMethod* pMethod) {
		Q_ASSERT(NULL != pMethod);

		QString hostAndPath = apiRoot_ + getVersionPathSegment(pMethod) + pMethod->getPath();
		QUrl url(hostAndPath);
		url.setScheme(getScheme(pMethod));

		QNetworkRequest networkRequest(url);
		networkRequest.setHeader(QNetworkRequest::ContentTypeHeader, pSerializer_->getContentType());
		networkRequest.setRawHeader("User-Agent", userAgent_);

		ApiObject* pObj = pMethod->getRequestObject();
		QByteArray objXml;
		if (NULL != pObj) {
			pSerializer_->toXml(pObj, objXml);
			Q_ASSERT(0 != objXml.size());
			networkRequest.setHeader(QNetworkRequest::ContentLengthHeader, objXml.size());
		}

		switch (pMethod->getHttpVerb()) {
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

private:
	QString getVersionPathSegment(const ApiMethod* pMethod) {
		switch (pMethod->getVersion()) {
		case ApiVersion.VERSION_3: return "/v3";
		case ApiVersion.VERSION_4: return "/v4";
		}

		return "/v3"; // default
	}

	QString getScheme(const ApiMethod* pMethod) const {
		switch (useHttps_) {
		case HTTPS_NEVER: return "http";
		case HTTPS_ALWAYS: return "https";
		case HTTPS_AUTH_ONLY:
			{
				// TODO(ebrooks): Expensive, better way of doing this
				Authenticate* pAuth = dynamic_cast<Authenticate*>(pMethod);
				return NULL == pAuth ? "http" : "https";
			}
		}

		return "http"; // default
	}

private:
	QNetworkAccessManager& networkAccessManager_;

	UseHttps useHttps_;
	QString apiRoot_;
	QString userAgent_;
	ApiObjectSerializer* pSerializer_;
};

};
};

#endif /* APICLIENT_H_ */
