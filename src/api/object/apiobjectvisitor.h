/*
 * apiobjectvisitor.h
 *
 *  Created on: Feb 10, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECTVISITOR_H_
#define APIOBJECTVISITOR_H_

class AuthToken;
class MessageBoxEntry;
class MessageBoxFolder;
class PushRegistration;
class TranscriptionSettings;
class AlertSettings;
class Settings;

namespace ymbb10 {
namespace api {
namespace object {

class ApiObjectVisitor {
	virtual ~ApiObjectVisitor() = 0;
	virtual void visit(AuthToken*) = 0;
	virtual void visit(MessageBoxEntry*) = 0;
	virtual void visit(MessageBoxFolder*) = 0;
	virtual void visit(TranscriptionSettings*) = 0;
	virtual void visit(AlertSettings*) = 0;
	virtual void visit(Settings*) = 0;
	virtual void visit(PushRegistration*) = 0;
};

}
}
}

#endif /* APIOBJECTVISITOR_H_ */