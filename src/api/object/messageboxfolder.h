/*
 * MessageBoxFolder.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef MESSAGEBOXFOLDER_H_
#define MESSAGEBOXFOLDER_H_

#include "api/object/apiobject.h"
#include "api/constants.h"

namespace ymbb10 {
namespace api {
namespace object {

class MessageBoxFolder : public ApiObject {
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
	MessageBoxFolder();
	~MessageBoxFolder();

	static QString getName() { return "folder"; }

	QString getDescription() const { return description_; }
	void setDescription(QString description) { description_ = description; }

	folderid_t getId() const { return id_; }
	void setId(folderid_t id) { id_ = id; }

	millisecond_t getLastEntryUpdated() const {	return lastEntryUpdated_; }
	void setLastEntryUpdated(millisecond_t lastEntryUpdated) { lastEntryUpdated_ = lastEntryUpdated; }

	QString getFolderName() const {	return folderName_;	}
	void setFolderName(QString folderName) { folderName_ = folderName; }

	unsigned long getNewEntryCount() const { return newEntryCount_;	}
	void setNewEntryCount(unsigned long newEntryCount) { newEntryCount_ = newEntryCount; }

	bool getSysType() const { return sysType_; }
	void setSysType(bool sysType) {	sysType_ = sysType;	}

	unsigned long getVisibleEntryCount() const { return visibleEntryCount_;	}
	void setVisibleEntryCount(unsigned long visibleEntryCount) { visibleEntryCount_ = visibleEntryCount; }

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
