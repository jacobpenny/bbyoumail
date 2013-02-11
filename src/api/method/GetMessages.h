/*
 * GetMessages.h
 *
 *  Created on: 2013-02-11
 *      Author: jpenny
 */

#ifndef GETMESSAGES_H_
#define GETMESSAGES_H_

namespace ymbb10 {
namespace api {
namespace method {

class GetMessages : GetApiMethod<ListApiObject<Message> > {
public:
	GetMessages();
	virtual ~GetMessages();

	virtual ApiVersion getVersion() const { return VERSION_4; }
	virtual QString getPath() const {
		QString path = "messagebox/entry/query";
		path.append("?includeList=messageDataUrl");
		return path;
	}
};

};
};
};

#endif /* GETMESSAGES_H_ */
