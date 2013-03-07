/*
 * apimethodresponsehandler.cpp
 *
 *  Created on: Mar 7, 2013
 *      Author: jpenny
 */
#include "apimethodresponsehandler.h"

using ymbb10::api::method::ApiMethodBase;

namespace ymbb10 {
namespace api {
namespace method {

void ApiMethodResponseHandler::testSlot(ApiMethodBase*)
{
	qDebug() << "apimeth testSlot";
}

void ApiMethodResponseHandler::handleResponse(ApiMethodBase* pMethod)
{
	// assumes no error (errors will be sent to handleError(ApiMethodBase*)
	qDebug() << "handleResponse slot called";
	pMethod->accept(this);
}

void ApiMethodResponseHandler::visit(Authenticate* pMeth) {
	emit responseProcessed(QString("AUTH_SUCCESS"));
}

}
}
}

