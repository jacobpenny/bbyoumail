/*
 * apiobjectvisitor.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECTVISITOR_H_
#define APIOBJECTVISITOR_H_

namespace ymbb10 {
namespace api {
namespace object {

#include "apiobject.h"


class AuthToken;
class MessageBoxEntry;
class MessageBoxFolder;
class TranscriptionSettings;
class AlertSettings;
class Settings;
class Error;
class ListApiObjectBase;
class Preferences;
class NullApiObject;
class ApiResponse;
class Contact;
class PushRegistration;

class ApiObjectVisitor {
public:
	virtual ~ApiObjectVisitor() = 0;
	virtual void visit(NullApiObject*) = 0;
	virtual void visit(AuthToken*) = 0;
	virtual void visit(MessageBoxEntry*) = 0;
	virtual void visit(MessageBoxFolder*) = 0;
	virtual void visit(TranscriptionSettings*) = 0;
	virtual void visit(AlertSettings*) = 0;
	virtual void visit(Settings*) = 0;
	virtual void visit(PushRegistration*) = 0;
	virtual void visit(Preferences*) = 0;
	virtual void visit(Error*) = 0;
	virtual void visit(ListApiObjectBase*) = 0;
	virtual void visit(ApiResponse*) = 0;
	virtual void visit(Contact*) = 0;
};

inline ApiObjectVisitor::~ApiObjectVisitor() {}

}
}
}

#endif /* APIOBJECTVISITOR_H_ */
