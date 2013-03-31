/*
 * AlertSettings.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef ALERTSETTINGS_H_
#define ALERTSETTINGS_H_

#include "apiobject.h"
#include "apiobjectvisitor.h"
#include "pushregistration.h"
#include <bitset>

namespace ymbb10 {
namespace api {
namespace object {

class AlertSettings : public ApiObject {
public:
	static const QUuid UUID;

	enum EmailAttachment {
		ATTACHFMT_NO_ATTACHMENT = 0,
		ATTACHFMT_WAV_FILE = 1,
		ATTACHFMT_MP3_FILE = 2
	};

	enum EmailFormat {
		EMAILFMT_PLAINTEXT = 1,
		EMAILFMT_HTML = 2,
		EMAILFMT_CUSTOM = 3
	};

	enum EmailFormatCustom {
		CEMAILFMT_BLACKBERRY = 1,
		CEMAILFMT_IPHONE = 2,
		CEMAILFMT_WINDOWSMOBILE = 3,
		CEMAILFMT_ANDROID = 4,
		CEMAILFMT_PALM = 5,
		CEMAILFMT_WEBOS = 6
	};

	static const unsigned int BIT_SEND_EMAIL = 0;
	static const unsigned int BIT_SEND_TXT = 1;
	static const unsigned int BIT_WMI_ON = 2;
	static const unsigned int BIT_PUSH_NOTIFICATIONS = 3;

	static const unsigned int BIT_PUSH_INBOX = 0; /* Send PUSH when message first arrives in Inbox */
	static const unsigned int BIT_PUSH_TRANSCRIPTION = 1; /* Send PUSH only after transcription has completed. If no transcription plan, this bit behaves identically to bit 0 */

public:
	//Overrides
	//TODO implementation
	virtual QList<QString> getProjection() const { return QList<QString>(); }

	virtual const QVariantMap& getContentValues() const { return QVariantMap(); }

	virtual void create(const QVariantMap& contentValues) {}

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	virtual QString getContentType() const { return QString("application/xml"); }

public:
	AlertSettings();
	virtual ~AlertSettings();

	static QString getName()
    {
        return "alertSettings";
    }

    unsigned long getDitchedCall() const
    {
        return ditchedCall_.to_ulong();
    }

    void setDitchedCall(unsigned long ditchedCall)
    {
        ditchedCall_ = ditchedCall;
    }

    unsigned long getMissedCall() const
    {
        return missedCall_.to_ulong();
    }

    void setMissedCall(unsigned long missedCall)
    {
        missedCall_ = missedCall;
    }

    unsigned long getNewMessage() const
    {
        return newMessage_.to_ulong();
    }

    void setNewMessage(unsigned long newMessage)
    {
        newMessage_ = newMessage;
    }

    unsigned long getPushConditions() const
    {
        return pushConditions_.to_ulong();
    }

    void setPushConditions(unsigned long pushConditions)
    {
        pushConditions_ = pushConditions;
    }

    const ListApiObject<PushRegistration>& getPushRegistrations() const
    {
        return pushRegistrations_;
    }

    ListApiObject<PushRegistration>& getPushRegistrations()
    {
        return pushRegistrations_;
    }

    void setPushRegistrations(const ListApiObject<PushRegistration>& pushRegistrations)
    {
        pushRegistrations_ = pushRegistrations;
    }

    unsigned long getDitchedCallMask() const
    {
        return ditchedCallMask_;
    }

    void setDitchedCallMask(unsigned long  ditchedCallMask)
    {
        ditchedCallMask_ = ditchedCallMask;
    }

    unsigned long getMissedCallMask() const
    {
        return missedCallMask_;
    }

    void setMissedCallMask(unsigned long  missedCallMask)
    {
        missedCallMask_ = missedCallMask;
    }

    unsigned long getNewMessageMask() const
    {
        return newMessageMask_;
    }

    void setNewMessageMask(unsigned long  newMessageMask)
    {
        newMessageMask_ = newMessageMask;
    }

    EmailAttachment getEmailAttachment() const
    {
        return emailAttachment;
    }

    void setEmailAttachment(EmailAttachment emailAttachment)
    {
        this->emailAttachment = emailAttachment;
    }

    EmailFormat getEmailFormat() const
    {
        return emailFormat;
    }

    void setEmailFormat(EmailFormat emailFormat)
    {
        this->emailFormat = emailFormat;
    }

    EmailFormatCustom getEmailFormatCustom() const
    {
        return emailFormatCustom;
    }

    void setEmailFormatCustom(EmailFormatCustom emailFormatCustom)
    {
        this->emailFormatCustom = emailFormatCustom;
    }

    void setSendEmailOnNewMessage(bool sendEmail)
    {
        newMessage_[BIT_SEND_EMAIL] = sendEmail;
    }

    void setSendTxtOnNewMessage(bool sendTxt)
    {
        newMessage_[BIT_SEND_TXT] = sendTxt;
    }

    void setWMIOnNewMessage(bool wmi)
    {
        newMessage_[BIT_WMI_ON] = wmi;
    }

    void setPushNotificationsOnNewMessage(bool push)
    {
        newMessage_[BIT_PUSH_NOTIFICATIONS] = push;
    }

    void setSendEmailOnMissedCall(bool sendEmail)
    {
        missedCall_[BIT_SEND_EMAIL] = sendEmail;
    }

    void setSendTxtOnMissedCall(bool sendTxt)
    {
        missedCall_[BIT_SEND_TXT] = sendTxt;
    }

    void setSendEmailOnDitchedCall(bool sendEmail)
    {
        ditchedCall_[BIT_SEND_EMAIL] = sendEmail;
    }

    void setSendTextOnDitchedCall(bool sendTxt)
    {
        ditchedCall_[BIT_SEND_TXT] = sendTxt;
    }

    void setSendPushOnNewMessage(bool sendPush)
    {
        pushConditions_[BIT_PUSH_INBOX] = sendPush;
    }

    void setSendPushOnNewTranscription(bool sendPush)
    {
        pushConditions_[BIT_PUSH_TRANSCRIPTION] = sendPush;
    }

    bool getSendEmailOnNewMessage() const
    {
        return newMessage_[BIT_SEND_EMAIL];
    }

    bool getSendTxtOnNewMessage() const
    {
        return newMessage_[BIT_SEND_TXT];
    }

    bool getWMIOnNewMessage() const
    {
        return newMessage_[BIT_WMI_ON];
    }

    bool getPushNotificationsOnNewMessage() const
    {
        return newMessage_[BIT_PUSH_NOTIFICATIONS];
    }

    bool getSendEmailOnMissedCall() const
    {
        return missedCall_[BIT_SEND_EMAIL];
    }

    bool getSendTxtOnMissedCall() const
    {
        return missedCall_[BIT_SEND_TXT];
    }

    bool getSendEmailOnDitchedCall() const
    {
        return ditchedCall_[BIT_SEND_EMAIL];
    }

    bool getSendTextOnDitchedCall() const
    {
        return ditchedCall_[BIT_SEND_TXT];
    }

    bool getSendPushOnNewMessage() const
    {
        return pushConditions_[BIT_PUSH_INBOX];
    }

    bool getSendPushOnNewTranscription() const
    {
        return pushConditions_[BIT_PUSH_TRANSCRIPTION];
    }

private:
    EmailAttachment emailAttachment;
    EmailFormat emailFormat;
    EmailFormatCustom emailFormatCustom;
    std::bitset<4> newMessage_;
    std::bitset<2> missedCall_;
    std::bitset<2> ditchedCall_;
    std::bitset<2> pushConditions_;
    unsigned long newMessageMask_;
    unsigned long missedCallMask_;
    unsigned long ditchedCallMask_;
    ListApiObject<PushRegistration> pushRegistrations_;
};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */
#endif /* ALERTSETTINGS_H_ */
