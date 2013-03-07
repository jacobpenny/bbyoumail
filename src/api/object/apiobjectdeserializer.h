/*
 * apiobjectdeserializer.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef APIOBJECTDESERIALIZER_H_
#define APIOBJECTDESERIALIZER_H_

#include "api/object/apiobject.h"
#include "api/object/apiobjectvisitor.h"
#include "api/object/authtoken.h"
#include "api/object/transcriptionsettings.h"
#include "api/object/alertsettings.h"
#include "api/object/pushregistration.h"
#include "api/object/settings.h"
#include "api/object/messageboxfolder.h"
#include "api/object/messageboxentry.h"
#include "api/object/preferences.h"
#include "api/object/response.h"
#include "api/util/util.h"
#include "api/constants.h"

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
	ApiObjectDeserializer(QByteArray* inBuffer) : inBuffer_(inBuffer), reader_(*inBuffer_) {};

public:
	virtual ~ApiObjectDeserializer() { delete inBuffer_; }

	virtual void visit(ApiResponse* pObj) {
		// stub
	}

	virtual void visit(ListApiObjectBase* pBase) {
		Q_ASSERT(NULL != pBase);
		validateInput(pBase->getName());

		reader_.readNext();
		while (!reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pBase->getName()) {
			if (reader_.tokenType() == QXmlStreamReader::StartElement) {
				ApiObject* pBaseElement = pBase->createElement();
				pBaseElement->accept(this);
				pBase->push_back(pBaseElement);
			}
			reader_.readNext();
		}
	}

	virtual void visit(NullApiObject* pObj) {
		Q_ASSERT(NULL != pObj);
		validateInput(pObj->getName());
	}

	virtual void visit(AuthToken* pObj) {
		Q_ASSERT(NULL != pObj);

		reader_.readNext();
		reader_.readNext();
		validateInput(pObj->getName());
		reader_.readNext();
		pObj->setAuthToken(reader_.text().toString());
		qDebug() << pObj->getAuthToken();
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
					pObj->setCreated(reader_.text().toString().toULong());
				} else if (reader_.name() == "length") {
					pObj->setLength(reader_.text().toString().toULong());
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
	        		pObj->setSysType(ymbb10::util::toBooleanJacob(reader_.text().toString()));
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
	        		pObj->setEnabled(ymbb10::util::toBooleanJacob(reader_.text().toString()));
	            } else if (reader_.name() == "active") {
	                pObj->setActive(ymbb10::util::toBooleanJacob(reader_.text().toString()));
	            } else if (reader_.name() == "speakClearly") {
	            	pObj->setSpeakClearly(ymbb10::util::toBooleanJacob(reader_.text().toString()));
	            } else if (reader_.name() == "smsCount") {
	            	pObj->setSmsCount(reader_.text().toString().toULong());
	            } else if (reader_.name() == "transcribeFor") {
	            	pObj->setTranscribeFor((TranscriptionSettings::TranscribeFor)reader_.text().toString().toULong());
	            } else if (reader_.name() == "transcribeForContact") {
	            	pObj->setTranscribeForContact(reader_.text().toString().toULong());
	            } else {
	            	qWarning() << "skipping unmapped element " << reader_.name() << " for " << pObj->getName();
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
	        		pObj->setEmailAttachment((AlertSettings::EmailAttachment)reader_.text().toString().toULong());
	            } else if (reader_.name() == "emailFormat") {
	        		pObj->setEmailFormat((AlertSettings::EmailFormat)reader_.text().toString().toULong());
	            } else if (reader_.name() == "emailFormatCustom") {
	        		pObj->setEmailFormatCustom((AlertSettings::EmailFormatCustom)reader_.text().toString().toULong());
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
	        	        	pObj->getPushRegistrations().push_back(&reg);
	        	        }
	        	        reader_.readNext();
	        	    }
	            } else {
	            	qWarning() << "skipping unmapped element " << reader_.name() << " for " << pObj->getName();
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
	            	qWarning() << "skipping unmapped element " << reader_.name() << " for " << pObj->getName();
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

	virtual void visit(Error* pObj) {
			Q_ASSERT(NULL != pObj);
			validateInput(pObj->getName());

			reader_.readNext();
		    while (!(reader_.tokenType() == QXmlStreamReader::EndElement && reader_.name() == pObj->getName())) {
		        if (reader_.tokenType() == QXmlStreamReader::StartElement) {
		        	if (reader_.name() == "errorCode") {
		        		pObj->setErrorCode(reader_.text().toString());
		        	} else if (reader_.name() == "shortMessage") {
		        		pObj->setShortMessage(reader_.text().toString());
		        	} else if (reader_.name() == "longMessage") {
		        		pObj->setLongMessage(reader_.text().toString());
		        	}
		        }
		        reader_.readNext();
		    }
		}

private:
	void validateInput(QString expectedTag) {
		if (reader_.tokenType() != QXmlStreamReader::StartElement || reader_.name() != expectedTag) {
			QString exception = QString("expected tag %1 but got %2").arg(expectedTag).arg(reader_.name().toString());
			//throw QXmlParseException(exception); // SLOTS are not allowed to throw, just going to print the exception for now.
			qDebug() << exception;
		}
	}
};

}
}
}


#endif /* APIOBJECTDESERIALIZER_H_ */
