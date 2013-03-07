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
	static QString getName() { return "settings"; }

	userid_t getUserId() const { return userId_; }
	void setUserId(userid_t userId) { userId_ = userId; }

	AlertSettings& getAlertSettings() { return alertSettings_; }
	TranscriptionSettings& getTranscriptionSettings() { return transcriptionSettings_; }

	const AlertSettings& getAlertSettings() const { return alertSettings_; }
	const TranscriptionSettings& getTranscriptionSettings() const { return transcriptionSettings_; }

	void setAlertSettings(const AlertSettings& alertSettings) { alertSettings_ = alertSettings; }
	void setTranscriptionSettings(const TranscriptionSettings& transcriptionSettings) { transcriptionSettings_ = transcriptionSettings; }

private:
	AlertSettings alertSettings_;
	TranscriptionSettings transcriptionSettings_;
	userid_t userId_;
};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */

#endif /* SETTINGS_H_ */
