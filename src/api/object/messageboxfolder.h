/*
 * MessageBoxFolder.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef MESSAGEBOXFOLDER_H_
#define MESSAGEBOXFOLDER_H_

#include "apiobject.h"
#include "constants.h"

namespace ymbb10 {
namespace api {
namespace object {

class MessageBoxFolder : public ApiObject {
public:
	MessageBoxFolder();
	~MessageBoxFolder();

	QString getDescription() const
	{
		return description_;
	}

	void setDescription(QString description)
	{
		description_ = description;
	}

	folderid_t getId() const
	{
		return id_;
	}

	void setId(folderid_t id)
	{
		id_ = id;
	}

	millisecond_t getLastEntryUpdated() const
	{
		return lastEntryUpdated_;
	}

	void setLastEntryUpdated(millisecond_t lastEntryUpdated)
	{
		lastEntryUpdated_ = lastEntryUpdated;
	}

	virtual QString getName() const
	{
		return "folder";
	}

	QString getFolderName() const
	{
		return folderName_;
	}

	void setFolderName(QString folderName)
	{
		folderName_ = folderName;
	}

	unsigned long getNewEntryCount() const
	{
		return newEntryCount_;
	}

	void setNewEntryCount(unsigned long newEntryCount)
	{
		newEntryCount_ = newEntryCount;
	}

	bool isSysType() const
	{
		return sysType_;
	}

	void setSysType(bool sysType)
	{
		sysType_ = sysType;
	}

	unsigned long getVisibleEntryCount() const
	{
		return visibleEntryCount_;
	}

	void setVisibleEntryCount(unsigned long visibleEntryCount)
	{
		visibleEntryCount_ = visibleEntryCount;
	}

private:
	folderid_t id_;
	QString folderName_;
	QString description_;
	bool sysType_;
	millisecond_t lastEntryUpdated_;
	unsigned long visibleEntryCount_;
	unsigned long newEntryCount_;
};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */
#endif /* MESSAGEBOXFOLDER_H_ */
