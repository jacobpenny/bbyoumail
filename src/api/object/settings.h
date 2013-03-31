/*
 * Settings.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_

#include "api/object/apiobject.h"
#include "api/object/transcriptionsettings.h"
#include "api/object/alertsettings.h"
#include "api/constants.h"

namespace ymbb10 {
namespace api {
namespace object {


class Settings : public ApiObject {
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
	static QString getName() { return "settings"; }

	ymbb10::api::userid_t getUserId() const { return userId_; }
	void setUserId(ymbb10::api::userid_t userId) { userId_ = userId; }

	AlertSettings& getAlertSettings() { return alertSettings_; }
	TranscriptionSettings& getTranscriptionSettings() { return transcriptionSettings_; }

	const AlertSettings& getAlertSettings() const { return alertSettings_; }
	const TranscriptionSettings& getTranscriptionSettings() const { return transcriptionSettings_; }

	void setAlertSettings(const AlertSettings& alertSettings) { alertSettings_ = alertSettings; }
	void setTranscriptionSettings(const TranscriptionSettings& transcriptionSettings) { transcriptionSettings_ = transcriptionSettings; }

private:
	AlertSettings alertSettings_;
	TranscriptionSettings transcriptionSettings_;
	ymbb10::api::userid_t userId_;
};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */

#endif /* SETTINGS_H_ */
