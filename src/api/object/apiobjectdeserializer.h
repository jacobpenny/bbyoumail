/*
 * apiobjectdeserializer.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECTDESERIALIZER_H_
#define APIOBJECTDESERIALIZER_H_

#include "apiobject.h"
#include "apiobjectvisitor.h"
#include "authtoken.h"
#include "transcriptionsettings.h"
#include "alertsettings.h"
#include "settings.h"
#include "messageboxfolder.h"
#include "messageboxentry.h"
#include "util/util.h"

#include <QXmlParseException>
#include <QXmlStreamReader>
#include <QByteArray>
#include <QtDebug>
#include <QScopedPointer>

namespace ymbb10 {
namespace api {
namespace object {

class ApiObjectDeserializer : public ApiObjectVisitor {
private:
	QByteArray* inBuffer_;
	QXmlStreamReader reader_;

public:
	ApiObjectDeserializer(QByteArray* inBuffer) : inBuffer_(inBuffer), reader_(inBuffer_) {};

public:
	virtual void visit(ListApiObjectBase* pObj) {
		Q_ASSERT(NULL != pObj);
		validateInput(pObj->getName());

		reader_.readNext();
		while (!reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pObj->getName()) {
			if (reader_.tokenType() == QXmlStreamReader::StartElement) {
				QScopedPointer<ApiObject> pBaseElement = pBase->createElement();
				visit(pBaseElement);
				pObj->push_back(pBaseElement);
			}
			reader_.readNext();
		}
	}

	template <typename T>
	virtual void visit(ListApiObject<T>* pObj) {
		Q_ASSERT(NULL != pObj);
		validateInput(pObj->getName());

		reader_.readNext();
		while (!reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pObj->getName()) {
			if (reader_.tokenType() == QXmlStreamReader::StartElement) {
				ListApiObject<T>::value_type o;
				visit(&o);
				pObj->push_back(o);
			}
			reader_.readNext();
		}
	}

	virtual void visit(AuthToken* pObj) {
		Q_ASSERT(NULL != pObj);
		validateInput(pObj->getName());
		pObj->setAuthToken(reader_.text().toString());
	}

	virtual void visit(MessageBoxEntry* pObj) {
		Q_ASSERT(NULL != pObj);
		validateInput(pObj->getName());

		reader_.readNext();
		while (!(reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pObj->getName())) {
			if (reader_.tokenType() == QXmlStreamReader::StartElement) {
				if (reader_.name() == "id") {
					pObj->setId(reader_.text().toString().toULong());
				} else if (reader_.name() == "created") {
					pObj->setCreated(reader_.text().toString().toULong);
				} else if (reader_.name() == "length") {
					pObj->setLength(reader_.text().toString().toULong);
				} else if (reader_.name() == "source") {
					pObj->setSource(reader_.text().toString());
				} else if (reader_.name() == "status") {
					pObj->setStatus(reader_.text().toString().toULong());
				} else if (reader_.name() == "messageDataUrl") {
					pObj->setMessageDataUrl(reader_.text().toString());
				} else if (reader_.name() == "folderid") {
					pObj->setFolderId(reader_.text().toString().toULong());
				}
			}
			reader_.readNext();
		}
	}

	virtual void visit(MessageBoxFolder* pObj) {
		Q_ASSERT(NULL != pObj);
		validateInput(pObj->getName());

		reader_.readNext();
	    while (!(reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pObj->getName())) {
	        if (reader_.tokenType() == QXmlStreamReader::StartElement) {
	        	if (reader_.name() == "id") {
	        		pObj->setId(reader_.text().toString().toULong());
	        	} else if (reader_.name() == "name") {
	        		pObj->setFolderName(reader_.text().toString());
	        	} else if (reader_.name() == "sysType") {
	        		pObj->setSysType(yymbb10::util::toBoolean(reader_.text().toString()));
	        	} else if (reader_.name() == "description") {
	        		pObj->setDescription(reader_.text().toString());
	        	} else if (reader_.name() == "lastEntryUpdated") {
	        		pObj->setLastEntryUpdated(reader_.text().toString().toULong());
	        	} else if (reader_.name() == "visibleEntryCount") {
	        		pObj->setVisibleEntryCount(reader_.text().toString().toULong());
	        	} else if (reader_.name() == "newEntryCount") {
	        		pObj->setNewEntryCount(reader_.text().toString().toULong());
	        	}
	        }
	        reader_.readNext();
	    }
	}

	virtual void visit(PushRegistration* pObj) {
		Q_ASSERT(NULL != pObj);
		// TODO: Implement me
	}

	virtual void visit(TranscriptionSettings* pObj) {
		Q_ASSERT(NULL != pObj);
		validateInput(pObj->getName());

	    reader_.readNext();
	    while (!(reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pObj->getName())) {
	        if (reader_.tokenType() == QXmlStreamReader::StartElement) {
	        	//
	        	// TODO(ebrooks): This will be super slow. Use a hash of the string and a switch statement.
	            //
	        	if (reader_.name() == "enabled") {
	        		pObj->setEnabled(ymbb10::util::toBoolean(reader_.text().toString()));
	            } else if (reader_.name() == "active") {
	                pObj->setActive(ymbb10::util::toBoolean(reader_.text().toString()));
	            } else if (reader_.name() == "speakClearly") {
	            	pObj->setSpeakClearly(ymbb10::util::toBoolean(reader_.text().toString()));
	            } else if (reader_.name() == "smsCount") {
	            	pObj->setSmsCount(reader_.text().toString().toULong());
	            } else if (reader_.name() == "transcribeFor") {
	            	pObj->setTranscribeFor((TranscriptionSettings::TranscribeFor)reader_.text().toString().toULong());
	            } else if (reader_.name() == "transcribeForContact") {
	            	pObj->setTranscribeForContact(reader_.text().toString().toULong());
	            } else {
	            	qWarn() << "skipping unmapped element " + reader_.name() + " for " + pObj->getName();
	            }
	        }
	        reader_.readNext();
	    }
	}

	virtual void visit(AlertSettings* pObj) {
		Q_ASSERT(NULL != pObj);
		validateInput(pObj->getName());

	    reader_.readNext();
	    while (!(reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pObj->getName())) {
	        if (reader_.tokenType() == QXmlStreamReader::StartElement) {
	        	//
	        	// TODO(ebrooks): This will be super slow. Use a hash of the string and a switch statement.
	            //
	        	if (reader_.name() == "emailAttachment") {
	        		pObj->setEmailAttachment((TranscriptionSettings::EmailAttachment)reader_.text().toString().toULong());
	            } else if (reader_.name() == "emailFormat") {
	        		pObj->setEmailFormat((TranscriptionSettings::EmailFormat)reader_.text().toString().toULong());
	            } else if (reader_.name() == "emailFormatCustom") {
	        		pObj->setEmailFormatCustom((TranscriptionSettings::EmailFormatCustom)reader_.text().toString().toULong());
	            } else if (reader_.name() == "newMessage") {
	        		pObj->setNewMessage(reader_.text().toString().toULong());
	            } else if (reader_.name() == "missedCall") {
	            	pObj->setMissedCall(reader_.text().toString().toULong());
	            } else if (reader_.name() == "ditchedCall") {
	            	pObj->setDitchedCall(reader_.text().toString().toULong());
	            } else if (reader_.name() == "pushConditions") {
	            	pObj->setPushConditions(reader_.text().toString().toULong());
	            } else if (reader_.name() == "newMessageMask") {
	            	pObj->setNewMessageMask(reader_.text().toString().toULong());
	            } else if (reader_.name() == "missedCallMask") {
	            	pObj->setMissedCallMask(reader_.text().toString().toULong());
	            } else if (reader_.name() == "ditchedCallMask") {
	            	pObj->setDitchedCallMask(reader_.text().toString().toULong());
	            } else if (reader_.name() == "pushRegistrations") {
	            	reader_.readNext();
	        	    while (!reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == "pushRegistrations") {
	        	        if (reader_.tokenType() == QXmlStreamReader::StartElement) {
	        	        	PushRegistration reg;
	        	        	visit(&reg);
	        	        	pObj->getPushRegistrations().push_back(reg);
	        	        }
	        	        reader_.readNext();
	        	    }
	            } else {
	            	qWarn() << "skipping unmapped element " + reader_.name() + " for " + pObj->getName();
	            }
	        }
	        reader_.readNext();
	    }
	}

	virtual void visit(Settings* pObj) {
		Q_ASSERT(NULL != pObj);
		validateInput(pObj->getName());

	    reader_.readNext();
	    while (!(reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pObj->getName())) {
	        if (reader_.tokenType() == QXmlStreamReader::StartElement) {
	        	//
	        	// TODO(ebrooks): This will be super slow. Use a hash of the string and a switch statement.
	            //
	        	if (reader_.name() == "userId") {
	                pObj->setUserId(reader_.text().toString().toULong());
	            } else if (reader_.name() == "alertSettings") {
	                visit(&pObj->getAlertSettings());
	            } else if (reader_.name() == "transcriptionSettings") {
	                visit(&pObj->getTranscriptionSettings());
	            } else {
	            	qWarn() << "skipping unmapped element " + reader_.name() + " for " + pObj->getName();
	            }
	        }
	        reader_.readNext();
	    }
	}

	virtual void visit(Preferences* pObj) {
			Q_ASSERT(NULL != pObj);
			validateInput(pObj->getName());

			reader_.readNext();
		    while (!(reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pObj->getName())) {
		        if (reader_.tokenType() == QXmlStreamReader::StartElement) {
		        	if (reader_.name() == "id") {
		        		pObj->setUserId(reader_.text().toString().toULong());
		        	} else if (reader_.name() == "title") {
		        		pObj->setTitle(reader_.text().toString());
		        	} else if (reader_.name() == "accessPointId") {
		        		pObj->setAccessPointId(reader_.text().toString().toULong());
		        	} else if (reader_.name() == "carrierId") {
		        		pObj->setCarrierId(reader_.text().toString().toULong());
		        	} else if (reader_.name() == "city") {
		        		pObj->setCity(reader_.text().toString());
		        	} else if (reader_.name() == "countryCode") {
		        		pObj->setCountryCode(reader_.text().toString());
		        	} else if (reader_.name() == "emailAddress") {
		        		pObj->setEmailAddress(reader_.text().toString());
		        	} else if (reader_.name() == "emailAttachmentType") {
		        		pObj->setEmailAttachment(reader_.text().toString());
		        	} else if (reader_.name() == "emailFormat") {
		        		pObj->setEmailFormat(reader_.text().toString());
		        	} else if (reader_.name() == "firstName") {
		        		pObj->setFirstName(reader_.text().toString());
		        	} else if (reader_.name() == "languageId") {
		        		pObj->setLanguageId(reader_.text().toString().toULong());
		        	} else if (reader_.name() == "lastName") {
		        		pObj->setLastName(reader_.text().toString());
		        	} else if (reader_.name() == "organization") {
		        		pObj->setOrganization(reader_.text().toString());
		        	} else if (reader_.name() == "phoneModelId") {
		        		pObj->setPhoneModelId(reader_.text().toString().toLong());
		        	} else if (reader_.name() == "phoneModelId") {
		        		pObj->setState(reader_.text().toString());
		        	} else if (reader_.name() == "status") {
		        		pObj->setStatus(reader_.text().toString().toULong());
		        	} else if (reader_.name() == "timeZone") {
		        		pObj->setTimeZone(reader_.text().toString());
		        	}
		        }
		        reader_.readNext();
		    }
		}

private:
	void validateInput(QString expectedTag) {
		if (reader_.tokenType() != QXmlStreamReader::StartElement || reader_.name() != expectedTag) {
			throw QXmlParseException("expected tag " + expectedTag + " but got " + reader_.name());
		}
	}
};

}
}
}


#endif /* APIOBJECTDESERIALIZER_H_ */
