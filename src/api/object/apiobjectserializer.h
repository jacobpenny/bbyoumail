/*
 * apiobjectserializer.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECTSERIALIZER_H_
#define APIOBJECTSERIALIZER_H_

#include "apiobject.h"
#include "response.h"
#include "apiobjectvisitor.h"
#include "authtoken.h"
#include "transcriptionsettings.h"
#include "alertsettings.h"
#include "settings.h"
#include "contact.h"
#include "messageboxfolder.h"
#include "messageboxentry.h"
#include "preferences.h"

namespace ymbb10 {
namespace api {
namespace object {

class ApiObjectSerializer : public ApiObjectVisitor {
private:
	QByteArray* outBuffer_;
	QXmlStreamWriter writer_;

public:
	ApiObjectSerializer(QByteArray* outBuffer) : outBuffer_(outBuffer), writer_(outBuffer_) {};

public:
	virtual ~ApiObjectSerializer() {

	}

	virtual void visit(ApiResponse* pObj) {
		// stub
	}

	void visit(ListApiObjectBase* pType) {
		writer_.writeStartElement(pType->getName());
		for (int i = 0; i < pType->size(); i++) {
			pType->at(i)->accept(this);
		}
		writer_.writeEndElement();
	}

	virtual void visit(NullApiObject* pObj) {
		// stub
	}

	virtual void visit(AuthToken* pObj) {
		writeMember(pObj->getName(), pObj->getAuthToken());
	}

	virtual void visit(MessageBoxEntry* pObj) {
		writer_.writeStartElement(pObj->getName());
		writeMember("id", pObj->getId());
		writeMember("folderId", pObj->getFolderId());
		writeMember("created", pObj->getCreated());
		writeMember("length", pObj->getLength());
		writeMember("source", pObj->getSource());
		writeMember("status", (long)pObj->getStatus());
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
		writer_.writeStartElement(pObj->getName());
		writeMember("clientType", (long)pObj->getClientType());
		writeMember("deviceId", pObj->getDeviceId());
		writeMember("id", pObj->getId());
		writeMember("pushType", pObj->getPushType());
		writeMember("status", (long)pObj->getStatus());
		writeMember("validUntil", pObj->getValidUntil());
		writeMember("version", pObj->getVersion());
		writer_.writeEndElement();
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
		writeMember("attachmentFormat", (long)pObj->getEmailAttachment());
		writeMember("newMessage", pObj->getNewMessage());
		writeMember("missedCall", pObj->getMissedCall());
		writeMember("ditchedCall", pObj->getDitchedCall());
		writeMember("pushConditions", pObj->getPushConditions());

		ListApiObject<PushRegistration>& pushRegistrations = pObj->getPushRegistrations();
		writer_.writeStartElement("pushRegistrations");
		for (int i = 0; i < pushRegistrations.size(); i++) {
			pushRegistrations.at(i)->accept(this);
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

	virtual void visit(Preferences* pObj) {
		writer_.writeStartElement(pObj->getName());
		writeMember("id", pObj->getUserId());
		writeMember("title", pObj->getTitle());
		writeMember("accessPointId", pObj->getAccessPointId());
		writeMember("carrierId", pObj->getCarrierId());
		writeMember("city", pObj->getCity());
		writeMember("countryCode", pObj->getCountryCode());
		writeMember("emailAddress", pObj->getEmailAddress());
		writeMember("emailAttachmentType", pObj->getEmailAttachment());
		writeMember("firstName", pObj->getFirstName());
		writeMember("languageId", pObj->getLanguageId());
		writeMember("lastName", pObj->getLastName());
		writeMember("organization", pObj->getOrganization());
		writeMember("phoneModelId", pObj->getPhoneModelId());
		writeMember("primaryPhoneNumber", pObj->getPrimaryPhoneNumber());
		writeMember("state", pObj->getState());
		writeMember("status", pObj->getStatus());
		writeMember("timeZone", pObj->getTimeZone());
		writer_.writeEndElement();
	}

	virtual void visit(Error* pObj) {
		writer_.writeStartElement(pObj->getName());
		writeMember("errorCode", pObj->getErrorCode());
		writeMember("shortMessage", pObj->getShortMessage());
		writeMember("longMessage", pObj->getLongMessage());
		writer_.writeEndElement();
	}

	virtual void visit(Contact* pObj) {

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

	void writeMember(const QString& memberName, unsigned long num) {
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
