/*
 * TranscriptionSettings.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef TRANSCRIPTIONSETTINGS_H_
#define TRANSCRIPTIONSETTINGS_H_

#include "apiobject.h"

namespace ymbb10 {
namespace api {
namespace object {

class TranscriptionSettings : public ApiObject {
public:
	enum TranscribeFor {
		ALL_CALLERS = 0,
		ONLY_CONTACT = 1,
		ALL_CONTACTS = 2
	};

public:
	TranscriptionSettings();
	virtual ~TranscriptionSettings();

	QString getName() const
	{
		return "transcriptionSettings";
	}

	bool getEnabled() const
	{
		return enabled_;
	}

	void setEnabled(bool enabled)
	{
		enabled_ = enabled;
	}

	bool getActive() const
	{
		return active_;
	}

	void setActive(bool active)
	{
		active_ = active;
	}

	bool getSpeakClearly() const
	{
		return speakClearly_;
	}

	void setSpeakClearly(bool speakClearly)
	{
		speakClearly_ = speakClearly;
	}

	TranscribeFor getTranscribeFor() const
	{
		return transcribeFor_;
	}

	void setTranscribeFor(TranscribeFor transcribeFor)
	{
		transcribeFor_ = transcribeFor;
	}

	long getSmsCount() const
	{
		return smsCount_;
	}

	void setSmsCount(long smsCount)
	{
		smsCount_ = smsCount;
	}


	contactid_t getTranscribeForContact() const
	{
		return transcribeForContact_;
	}

	void setTranscribeForContact(contactid_t transcribeForContact)
	{
		transcribeForContact_ = transcribeForContact;
	}

private:
	bool enabled_;
	bool active_;
	bool speakClearly_;
	long smsCount_;
	contactid_t transcribeForContact_;
	TranscribeFor transcribeFor_;
};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */

#endif /* TRANSCRIPTIONSETTINGS_H_ */
