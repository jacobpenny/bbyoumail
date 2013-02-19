/*
 * apiobjectserializer.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECTSERIALIZER_H_
#define APIOBJECTSERIALIZER_H_

#include "apiobject.h"
#include "apiobjectvisitor.h"
#include "authtoken.h"
#include "transcriptionsettings.h"
#include "alertsettings.h"
#include "settings.h"
#include "messageboxfolder.h"
#include "messageboxentry.h"

namespace ymbb10 {
namespace api {
namespace object {

class ApiObjectSerializer : public ApiObjectVisitor {
private:
	QByteArray outBuffer_;
	QXmlStreamWriter writer_;

public:
	ApiObjectSerializer() : writer_(&outBuffer_) {};

public:
	template <typename T>
	void visit(ListApiObject<T>* pType) {
		writer_.writeStartElement(pType->getName());
		for (ListApiObject<T>::iterator i = pType->begin(); i != pType->end(); i++) {
			visit(*i);
		}
		writer_.writeEndElement();
	}

	virtual void visit(AuthToken* pObj) {
		writeMember(pObj->getName(), pObj->getAuthToken());
	}

	virtual void visit(MessageBoxEntry* pObj) {
		writer_.writeStartElement(pObj->getName());
		writeMember("id", pObj->getId());
		writeMember("created", pObj->getCreated());
		writeMember("length", pObj->getLength());
		writeMember("source", pObj->getSource());
		writeMember("status", pObj->getStatus());
		writeMember("messageDataUrl", pObj->getMessageDataUrl());
		writer_.writeEndElement();
	}

	virtual void visit(MessageBoxFolder* pObj) {
		writer_.writeStartElement(pObj->getName());
		writeMember("id", pObj->getId());
		writeMember("name", pObj->getFolderName());
		writeMember("sysType", pObj->getSysType());
		writeMember("description", pObj->getDescription());
		writeMember("lastEntryUpdated", pObj->getLastEntryUpdated());
		writeMember("visibleEntryCount", pObj->getVisibleEntryCount());
		writeMember("newEntryCount", pObj->getNewEntryCount());
		writer_.writeEndElement();
	}

	virtual void visit(PushRegistration* pObj) {
		// TODO: Implement me
	}

	virtual void visit(TranscriptionSettings* pObj) {
		writer_.writeStartElement(pObj->getName());
		writeMember("smsCount", pObj->getSmsCount());
		writeMember("enabled", pObj->getEnabled());
		writeMember("active", pObj->getActive());
		writeMember("speakClearly", pObj->getSpeakClearly());
		writeMember("transcribeFor", (long)pObj->getTranscribeFor());
		writeMember("transcribeForContact", pObj->getTranscribeForContact());
		writer_.writeEndElement();
	}

	virtual void visit(AlertSettings* pObj) {
		writer_.writeStartElement(pObj->getName());
		writeMember("emailFormat", (long)pObj->getEmailFormat());
		writeMember("emailFormatCustom", (long)pObj->getEmailFormatCustom());
		writeMember("attachmentFormat", (long)pObj->getAttachmentFormat());
		writeMember("newMessage", pObj->getNewMessage());
		writeMember("missedCall", pObj->getMissedCall());
		writeMember("ditchedCall", pObj->getDitchedCall());
		writeMember("pushConditions", pObj->getPushConditions());

		ListApiObject<PushRegistration>& pushRegistrations = pObj->getPushRegistrations();
		writer_.writeStartElement("pushRegistrations");
		for (ListApiObject<PushRegistration>::iterator i = pushRegistrations.begin(); i != pushRegistrations.end(); ++i) {
			visit(*i);
		}
		writer_.writeEndElement();

		writer_.writeEndElement();
	}


	virtual void visit(Settings* pObj) {
		writer_.writeStartElement(pObj->getName());
		visit(&pObj->getTranscriptionSettings());
		visit(&pObj->getAlertSettings());
		writeMember("userId", pObj->getUserId());
		writer_.writeEndElement();
	}

private:
	void writeMember(const QString& memberName, const QString& text) {
		writer_.writeStartElement(memberName);
		writer_.writeCharacters(text);
		writer_.writeEndElement();
	}

	void writeMember(const QString& memberName, long num) {
		writer_.writeStartElement(memberName);
		writer_.writeCharacters(QString::number(num));
		writer_.writeEndElement();
	}

	void writeMember(const QString& memberName, bool b) {
		writer_.writeStartElement(memberName);
		writer_.writeCharacters(b ? "true" : "false");
		writer_.writeEndElement();
	}
};

}
}
}

#endif /* APIOBJECTSERIALIZER_H_ */
