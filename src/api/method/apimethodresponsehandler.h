/*
 * apimethodresponsehandler.h
 *
 *  Created on: Mar 6, 2013
 *      Author: jpenny
 */

#ifndef APIMETHODRESPONSEHANDLER_H_
#define APIMETHODRESPONSEHANDLER_H_

#include "api/object/apiobject.h"
#include "api/object/authtoken.h"
#include "api/method/apimethod.h"
#include "api/method/apimethodvisitor.h"
#include "api/method/authenticate.h"

#include <QSharedPointer>
#include <QSettings>

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
		ymbb10::api::object::AuthToken* authToken = (ymbb10::api::object::AuthToken*)pMeth->getResponseObject().data();
		// Store the auth token
		QSettings loginSettings;
		loginSettings.setValue("authtoken", authToken->getAuthToken());
		loginSettings.sync();

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
