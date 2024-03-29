/*
 * preferences.h
 *
 *  Created on: 2013-02-23
 *      Author: Jacob
 */

#ifndef PREFERENCES_H_
#define PREFERENCES_H_

#include "api/object/apiobject.h"
#include "api/constants.h"

namespace ymbb10 {
namespace api {
namespace object {


class Preferences : public ApiObject {
public:
	static const QUuid UUID;
public:
	//Overrides
	//TODO implementation
	virtual QList<QString> getProjection() const { return QList<QString>(); }

	virtual const QVariantMap& getContentValues() const { return QVariantMap(); }

	virtual void create(const QVariantMap& contentValues) {}

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	virtual QString getContentType() const { return QString("application/xml"); }

public:
	Preferences();
	virtual ~Preferences();

	static QString getName() { return "account"; }

	QString getTitle() const {
		return title_;
	}

	void setTitle(QString title) {
		title_ = title;
	}

	unsigned long getAccessPointId() const {
		return accessPointId_;
	}

	void setAccessPointId(unsigned long accessPointId) {
		accessPointId_ = accessPointId;
	}

	unsigned long getCarrierId() const {
		return carrierId_;
	}

	void setCarrierId(unsigned long carrierId) {
		carrierId_ = carrierId;
	}

	QString getCity() const {
		return city_;
	}

	void setCity(QString city) {
		city_ = city;
	}

	QString getCountryCode() const {
		return countryCode_;
	}

	void setCountryCode(QString countryCode) {
		countryCode_ = countryCode;
	}

	/* I don't think we even need this
	date_t getCreatedTime() const {
		return createdTime_;
	}

	void setCreatedTime(date_t createdTime) {
		createdTime_ = createdTime;
	} */

	QString getEmailAddress() const {
		return emailAddress_;
	}

	void setEmailAddress(QString emailAddress) {
		emailAddress_ = emailAddress;
	}

	QString getEmailAttachment() const {
		return emailAttachment_;
	}

	void setEmailAttachment(QString emailAttachment) {
		emailAttachment_ = emailAttachment;
	}

	QString getEmailFormat() const {
		return emailFormat_;
	}

	void setEmailFormat(QString emailFormat) {
		emailFormat_ = emailFormat;
	}

	QString getFirstName() const {
		return firstName_;
	}

	void setFirstName(QString firstName) {
		firstName_ = firstName;
	}

	unsigned long getLanguageId() const {
		return languageId_;
	}

	void setLanguageId(unsigned long languageId) {
		languageId_ = languageId;
	}

	QString getLastName() const {
		return lastName_;
	}

	void setLastName(QString lastName) {
		lastName_ = lastName;
	}

	QString getOrganization() const {
		return organization_;
	}

	void setOrganization(QString organization) {
		organization_ = organization;
	}

	unsigned long getPhoneModelId() const {
		return phoneModelId_;
	}

	void setPhoneModelId(unsigned long phoneModelId) {
		phoneModelId_ = phoneModelId;
	}

	QString getPrimaryPhoneNumber() const {
		return primaryPhoneNumber_;
	}

	void setPrimaryPhoneNumber(QString primaryPhoneNumber) {
		primaryPhoneNumber_ = primaryPhoneNumber;
	}

	QString getState() const {
		return state_;
	}

	void setState(QString state) {
		state_ = state;
	}

	unsigned long getStatus() const {
		return status_;
	}

	void setStatus(unsigned long status) {
		status_ = status;
	}

	QString getTimeZone() const {
		return timeZone_;
	}

	void setTimeZone(QString timeZone) {
		timeZone_ = timeZone;
	}

	userid_t getUserId() const {
		return userId_;
	}

	void setUserId(userid_t userId) {
		userId_ = userId;
	}


private:
	userid_t userId_;
	QString title_;
	// date_t createdTime_; // api returns something like 2011-08-30T02:46:10-07:00. Unsure on type.
	unsigned long accessPointId_;
	unsigned long carrierId_; // could be an enum but unsure of possible values
	QString city_;
	QString countryCode_;
	QString emailAddress_;
	QString emailAttachment_; // could be an enum but unsure of possible values
	QString emailFormat_; // could be an enum but unsure of possible values
	QString firstName_;
	unsigned long languageId_;
	QString lastName_;
	QString organization_;
	long phoneModelId_;
	QString primaryPhoneNumber_;
	QString state_;
	unsigned long status_;
	QString timeZone_;
};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */

#endif /* PREFERENCES_H_ */


