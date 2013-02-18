/*
 * apimethod.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APIMETHOD_H_
#define APIMETHOD_H_

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
	ApiMethodBase(ApiObject::Pointer pApiObject = NULL) : pRequestObject(pApiObject) {};
	virtual ~ApiMethod() = 0;
	virtual QString getPath() const = 0;
	virtual ApiVersion getVersion() const = 0;
	virtual HttpVerb getHttpVerb() const = 0;

	bool hasRequestObject() const { return !!pRequestObject_; }

	const ApiObject& getRequestObject() const { return pRequestObject_.data(); }
	ApiObject& getRequestObject() { return pRequestObject_.data(); }

protected:
	ApiObject::Pointer pRequestObject_;
};

template <typename RequestType, typename ResponseType>
class ApiMethod : public ApiMethodBase {
public:
	typedef typename RequestType RequestType;
	typedef typename ResponseType ResponseType;

public:
	ApiMethod(RequestType::Pointer pRequestObject = NULL) : ApiMethodBase(pRequestObject) {};
};

template <typename RequestType, typename ResponseType>
class BasicApiMethod : public ApiMethod<RequestType, ResponseType> {
	virtual ~BasicApiMethod() {};
	virtual ApiVersion getVersion() const { return VERSION_3; }
};

template <typename ResponseType>
class GetApiMethod : public BasicApiMethod<NullApiObject, ResponseType> {
	virtual ~GetApiMethod() {};
	virtual HttpVerb getHttpVerb() const { return HTTP_GET; }
};

template <typename RequestType, typename ResponseType>
class PostApiMethod : public BasicApiMethod<RequestType, ResponseType> {
	virtual ~PostApiMethod() {};
	virtual HttpVerb getHttpVerb() const { return HTTP_POST; }
};

template <typename RequestType, typename ResponseType>
class PutApiMethod : public BasicApiMethod<RequestType, ResponseType> {
	virtual ~PutApiMethod() {};
	virtual HttpVerb getHttpVerb() const { return HTTP_PUT; }
};

template <typename ResponseType>
class DeleteApiMethod : public BasicApiMethod<NullApiObject, ResponseType> {
	virtual ~PutApiMethod() {};
	virtual HttpVerb getHttpVerb() const { return HTTP_DELETE; }
};


};
};
};

#endif /* APIMETHOD_H_ */
