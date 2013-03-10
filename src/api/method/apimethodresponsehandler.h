/*
 * apimethodresponsehandler.h
 *
 *  Created on: Mar 6, 2013
 *      Author: jpenny
 */

#ifndef APIMETHODRESPONSEHANDLER_H_
#define APIMETHODRESPONSEHANDLER_H_

#include "api/method/apimethod.h"
#include "api/method/apimethodvisitor.h"



namespace ymbb10 {
namespace api {
namespace method {

class ApiMethodBase;

enum ResponseMessage {
	AUTH_SUCCESS = 0,
	AUTH_FAILURE = 1
};


class ApiMethodResponseHandler : public ApiMethodVisitor {
	Q_OBJECT
public slots:
	void handleResponse(ymbb10::api::method::ApiMethodBase* pMeth) {
		pMeth->accept(this);
	}

signals:
	void responseProcessed(ymbb10::api::method::ResponseMessage message);

public:
	ApiMethodResponseHandler() {}
	virtual ~ApiMethodResponseHandler() {}

	virtual void visit(AddFolder* pMeth) {}
	virtual void visit(Authenticate* pMeth) {
		// Store the auth token


		// Emit an auth success signal (to alert the login screen)
		emit responseProcessed(AUTH_SUCCESS);
	}
	virtual void visit(DeleteFolder* pMeth) {}
	virtual void visit(GetAccessPoint* pMeth) {}
	virtual void visit(GetFolders* pMeth) {}
	virtual void visit(GetMessages* pMeth) {}
	virtual void visit(GetPreferences* pMeth) {}
	virtual void visit(GetSettings* pMeth) {}



};



}
}
}



#endif /* APIMETHODRESPONSEHANDLER_H_ */
