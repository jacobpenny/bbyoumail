/*
 * apimethodvisitor.h
 *
 *  Created on: Mar 6, 2013
 *      Author: jpenny
 */

#ifndef APIMETHODVISITOR_H_
#define APIMETHODVISITOR_H_

#include <QObject>

namespace ymbb10 {
namespace api {
namespace method {

class AddFolder;
class Authenticate;
class DeleteFolder;
class GetAccessPoint;
class GetFolders;
class GetMessages;
class GetPreferences;
class GetSettings;

class ApiMethodVisitor : public QObject {
public:
	virtual ~ApiMethodVisitor() = 0;
	virtual void visit(AddFolder*) = 0;
	virtual void visit(Authenticate*) = 0;
	virtual void visit(DeleteFolder*) = 0;
	virtual void visit(GetAccessPoint*) = 0;
	virtual void visit(GetFolders*) = 0;
	virtual void visit(GetMessages*) = 0;
	virtual void visit(GetPreferences*) = 0;
	virtual void visit(GetSettings*) = 0;

};

inline ApiMethodVisitor::~ApiMethodVisitor() {}

}
}
}

#endif /* APIMETHODVISITOR_H_ */
