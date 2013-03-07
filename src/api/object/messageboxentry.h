/*
 * MessageBoxEntry.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef MESSAGEBOXENTRY_H_
#define MESSAGEBOXENTRY_H_


#include "api/object/apiobject.h"
#include "api/object/apiobjectvisitor.h"
#include "api/constants.h"

namespace ymbb10 {
namespace api {
namespace object {

class MessageBoxEntry : public ApiObject {
public:
	/*
	enum EntryStatus {
		STATUS_NEW = 1,
		STATUS_ACK = 2
	};
	*/
public:
	MessageBoxEntry();
	virtual ~MessageBoxEntry();

	static QString getName() { return "entry"; }

	virtual void accept(ApiObjectVisitor* pVisitor) { pVisitor->visit(this); }

	millisecond_t getCreated() const { return created_;	}
	void setCreated(millisecond_t created) { created_ = created; }

	messageid_t getId() const {	return id_;	}
	void setId(messageid_t id) { id_ = id; }

	folderid_t getFolderId() const { return folderid_; }
	void setFolderId(folderid_t fid) { folderid_ = fid; }

	millisecond_t getLength() const { return length_; }
	void setLength(millisecond_t length) { length_ = length; }

	QString getMessageDataUrl() const { return messageDataUrl_;	}
	void setMessageDataUrl(QString messageDataUrl) { messageDataUrl_ = messageDataUrl; }

	QString getSource() const {	return source_; }
	void setSource(QString source) { source_ = source; }

	unsigned long getStatus() const { return status_; }
	void setStatus(unsigned long status) { status_ = status; } // getting a compile error without this awkwardness

private:
	messageid_t id_;
	folderid_t folderid_;
	millisecond_t created_;
	millisecond_t length_;
	QString source_;
	unsigned long status_;
	QString messageDataUrl_;

};

} /* namespace object */
} /* namespace api */
} /* namespace ymbb10 */

#endif /* MESSAGEBOXENTRY_H_ */

