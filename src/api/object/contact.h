/*
 * contact.h
 *
 *  Created on: Feb 18, 2013
 *      Author: ebrooks
 */

#ifndef CONTACT_H_
#define CONTACT_H_

#include "apiobject.h"
#include "api/object/apiobjectvisitor.h"
#include "constants.h"

#include <QString>

namespace ymbb10 {
namespace api {
namespace object {


class Contact: public ApiObject {
public:
	static const QUuid UUID;

	enum ActionType {
		NORMAL = 0,
		DITCH = 1,
		NUMBER_PROMPT = 2,
		PASSWORD_PROMPT = 3
	};
public:
	// Overrides
	// TODO implementation
	virtual QList<QString> getProjection() const { return QList<QString>(); }

	virtual const QVariantMap& getContentValues() const { return QVariantMap(); }

	virtual void create(const QVariantMap& contentValues) {}

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	virtual QString getContentType() const { return QString("application/xml"); }

public:
	ActionType getActionType() const {
		return actionType_;
	}

	void setActionType(ActionType actionType) {
		actionType_ = actionType;
	}

	QString getCity() const {
		return city_;
	}

	void setCity(QString city) {
		city_ = city;
	}

	QString getCountry() const {
		return country_;
	}

	void setCountry(QString country) {
		country_ = country;
	}

	QString getEmailAddress() const {
		return emailAddress_;
	}

	void setEmailAddress(QString emailAddress) {
		emailAddress_ = emailAddress;
	}

	QString getFirstName() const {
		return firstName_;
	}

	void setFirstName(QString firstName) {
		firstName_ = firstName;
	}

	greetingid_t getGreetingId() const {
		return greetingId_;
	}

	void setGreetingId(greetingid_t greetingId) {
		greetingId_ = greetingId;
	}

	QString getHomeNumber() const {
		return homeNumber_;
	}

	void setHomeNumber(QString homeNumber) {
		homeNumber_ = homeNumber;
	}

	contactid_t getId() const {
		return id_;
	}

	void setId(contactid_t id) {
		id_ = id;
	}

	QString getLastName() const {
		return lastName_;
	}

	void setLastName(QString lastName) {
		lastName_ = lastName;
	}

	QString getMiddleName() const {
		return middleName_;
	}

	void setMiddleName(QString middleName) {
		middleName_ = middleName;
	}

	QString getMobileNumber() const {
		return mobileNumber_;
	}

	void setMobileNumber(QString mobileNumber) {
		mobileNumber_ = mobileNumber;
	}

	QString getNotes() const {
		return notes_;
	}

	void setNotes(QString notes) {
		notes_ = notes;
	}

	QString getOrganization() const {
		return organization_;
	}

	void setOrganization(QString organization) {
		organization_ = organization;
	}

	QString getOtherNumber1() const {
		return otherNumber1_;
	}

	void setOtherNumber1(QString otherNumber1) {
		otherNumber1_ = otherNumber1;
	}

	QString getOtherNumber2() const {
		return otherNumber2_;
	}

	void setOtherNumber2(QString otherNumber2) {
		otherNumber2_ = otherNumber2;
	}

	QString getOtherNumber3() const {
		return otherNumber3_;
	}

	void setOtherNumber3(QString otherNumber3) {
		otherNumber3_ = otherNumber3;
	}

	QString getOtherNumber4() const {
		return otherNumber4_;
	}

	void setOtherNumber4(QString otherNumber4) {
		otherNumber4_ = otherNumber4;
	}

	QString getPagerNumber() const {
		return pagerNumber_;
	}

	void setPagerNumber(QString pagerNumber) {
		pagerNumber_ = pagerNumber;
	}

	QString getState() const {
		return state_;
	}

	void setState(QString state) {
		state_ = state;
	}

	QString getStreet() const {
		return street_;
	}

	void setStreet(QString street) {
		street_ = street;
	}

	QString getTitle() const {
		return title_;
	}

	void setTitle(QString title) {
		title_ = title;
	}

	QString getWorkNumber() const {
		return workNumber_;
	}

	void setWorkNumber(QString workNumber) {
		workNumber_ = workNumber;
	}

	QString getZipCode() const {
		return zipCode_;
	}

	void setZipCode(QString zipCode) {
		zipCode_ = zipCode;
	}

private:
	contactid_t id_;

	QString firstName_;
	QString lastName_;
	QString middleName_;
	QString title_;
	QString organization_;
	QString emailAddress_;
	QString workNumber_;
	QString homeNumber_;
	QString pagerNumber_;
	QString mobileNumber_;
	QString otherNumber1_;
	QString otherNumber2_;
	QString otherNumber3_;
	QString otherNumber4_;

	QString street_;
	QString city_;
	QString state_;
	QString country_;
	QString zipCode_;
	QString notes_;

	ActionType actionType_;
	greetingid_t greetingId_;
};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */
#endif /* CONTACT_H_ */
