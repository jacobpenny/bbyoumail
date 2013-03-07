/*
 * apimethod.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APIMETHOD_H_
#define APIMETHOD_H_


#include "api/object/apiobject.h"
#include "api/method/apimethodvisitor.h"

using ymbb10::api::object::ApiObject;

namespace ymbb10 {
namespace api {
namespace method {

// TODO(ebrooks): Move me to a more appropriate place
enum HttpVerb {
	HTTP_GET,
	HTTP_POST,
	HTTP_PUT,
	HTTP_DELETE
};

// TODO(ebrooks): Move me to a more appropriate place
enum ApiVersion {
	VERSION_3 = 3,
	VERSION_4 = 4
};

class ApiMethodBase {
public:
	ApiMethodBase(ApiObject* pRequestObject, ApiObject* pResponseObject)
		: pRequestObject_(pRequestObject), pResponseObject_(pResponseObject) {

	}

public:
	virtual ~ApiMethodBase() = 0;
	virtual QString getPath() const = 0;
	virtual ApiVersion getVersion() const = 0;
	virtual HttpVerb getHttpVerb() const = 0;

	virtual void accept(ApiMethodVisitor*) = 0;

	bool hasRequestObject() const { return !!pRequestObject_.data(); }

	const QSharedPointer<object::ApiObject> getRequestObject() const { return pRequestObject_; }
	QSharedPointer<object::ApiObject> getRequestObject() { return pRequestObject_; }

	const QSharedPointer<object::ApiObject> getResponseObject() const { return pResponseObject_; }
	QSharedPointer<object::ApiObject> getResponseObject() { return pResponseObject_; }

protected:
	QSharedPointer<object::ApiObject> pRequestObject_;
	QSharedPointer<object::ApiObject> pResponseObject_;
};

inline ApiMethodBase::~ApiMethodBase() {}

template <typename RequestType, typename ResponseType>
class ApiMethod : public ApiMethodBase {
public:
	//typedef typename RequestType RequestType;  // Are these necessary? Won't compile as is.
	//typedef typename ResponseType ResponseType;

public:
	ApiMethod(RequestType* pRequestObject = NULL)
		: ApiMethodBase(pRequestObject, new ResponseType) {}
};

template <typename RequestType, typename ResponseType>
class BasicApiMethod : public ApiMethod<RequestType, ResponseType> {
public:
	virtual ~BasicApiMethod() {};
	virtual ApiVersion getVersion() const { return VERSION_3; }
};

template <typename ResponseType>
class GetApiMethod : public BasicApiMethod<object::NullApiObject, ResponseType> {
public:
	virtual ~GetApiMethod() {};
	virtual HttpVerb getHttpVerb() const { return HTTP_GET; }
};

template <typename RequestType, typename ResponseType>
class PostApiMethod : public BasicApiMethod<RequestType, ResponseType> {
public:
	virtual ~PostApiMethod() {};
	virtual HttpVerb getHttpVerb() const { return HTTP_POST; }
};

template <typename RequestType, typename ResponseType>
class PutApiMethod : public BasicApiMethod<RequestType, ResponseType> {
public:
	virtual ~PutApiMethod() {};
	virtual HttpVerb getHttpVerb() const { return HTTP_PUT; }
};

template <typename ResponseType>
class DeleteApiMethod : public BasicApiMethod<object::NullApiObject, ResponseType> {
public:
	virtual ~DeleteApiMethod() {};
	virtual HttpVerb getHttpVerb() const { return HTTP_DELETE; }
};


};
};
};

#endif /* APIMETHOD_H_ */
