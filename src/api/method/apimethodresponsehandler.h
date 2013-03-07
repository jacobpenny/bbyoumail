/*
 * apimethodresponsehandler.h
 *
 *  Created on: Mar 6, 2013
 *      Author: jpenny
 */

#ifndef APIMETHODRESPONSEHANDLER_H_
#define APIMETHODRESPONSEHANDLER_H_


#include "apimethodvisitor.h"

namespace ymbb10 {
namespace api {
namespace method {


class ApiMethodResponseHandler : public ApiMethodVisitor {
	Q_OBJECT

signals:
	void responseProcessed(QString message);

public:
	ApiMethodResponseHandler();
	virtual ~ApiMethodResponseHandler();

	virtual void visit(AddFolder* pMeth) {}
	virtual void visit(Authenticate* pMeth) {
		// Store the auth token


		// Emit an auth success signal (to alert the login screen)
		emit responseProcessed(QString("AUTH_SUCCESS"));
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
