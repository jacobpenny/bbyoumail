/*
 * apimethodresponsehandler.h
 *
 *  Created on: Mar 6, 2013
 *      Author: jpenny
 */

#ifndef APIMETHODRESPONSEHANDLER_H_
#define APIMETHODRESPONSEHANDLER_H_

#include <QSharedPointer>
#include <QtDebug>

#include "api/method/apimethod.h"
#include "api/method/apimethodvisitor.h"

namespace ymbb10 {
namespace api {
namespace method {


class ApiMethodResponseHandler : public ApiMethodVisitor {
Q_OBJECT

signals:
	void responseProcessed(QString message);

public slots:
	void testSlot(ApiMethodBase*);

	void handleResponse(ApiMethodBase*);
public:
	ApiMethodResponseHandler() {}
	virtual ~ApiMethodResponseHandler() {}

	virtual void visit(AddFolder* pMeth) {}
	virtual void visit(Authenticate* pMeth);
	virtual void visit(DeleteFolder* pMeth) {}
	virtual void visit(GetAccessPoint* pMeth) {}
	virtual void visit(GetFolders* pMeth) {}
	virtual void visit(GetMessages* pMeth) {}
	virtual void visit(GetPreferences* pMeth) {}
	virtual void visit(GetSettings* pMeth) {}

};



/*
inline void ApiMethodResponseHandler::handleResponse(ApiMethodBase* pMethod) {
	qDebug() << "METHOD HANDLER SLOT CALLED";
	emit responseProcessed(QString("AUTH_SUCCESS"));
}
*/
}
}
}



#endif /* APIMETHODRESPONSEHANDLER_H_ */
