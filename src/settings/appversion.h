/*
 * appversion.h
 *
 *  Created on: 2013-03-20
 *      Author: jpenny
 */

#ifndef APPVERSION_H_
#define APPVERSION_H_

#include <QString>
#include <QStringList>

namespace ymbb10 {
namespace settings {

/* Usage example:
 *
 * AppVersion currentVersion(app->getApplicationVersion);
 * AppVersion prevVersion AppVersion(settings_.value(PREV_APP_VERSION));
 * if (currentVersion > prevVersion) { ... }
 */

class AppVersion {

public:
	AppVersion(const QString appver) : appVersionString_(appver) {
		QStringList li = appVersionString_.split(".");
		Q_ASSERT(li.size() == 4);
		major = li[0].toUInt();
		minor = li[1].toUInt();
		revision = li[2].toUInt();
		build = li[3].toUInt();
	}

	bool operator==(const AppVersion& other) {
		return (this->major == other.major &&
				this->minor == other.minor &&
				this->revision == other.revision &&
				this->build == other.build);
	}

	bool operator!=(const AppVersion& other) {
		return !this->operator ==(other);
	}

	bool operator<(const AppVersion& other) {
		if (this->major < other.major) {
			return true;
		} else if (this->major > other.major) {
			return false;
		}

		if (this->minor < other.minor) {
			return true;
		} else if (this->minor > other.minor) {
			return false;
		}

		if (this->revision < other.revision) {
			return true;
		} else if (this->revision > other.revision) {
			return false;
		}

		if (this->build < other.build) {
			return true;
		} else if (this->build > other.build) {
			return false;
		}
		return false;
	}

public:
	unsigned int major;
	unsigned int minor;
	unsigned int revision;
	unsigned int build;

private:
	const QString appVersionString_;

};

}
}

#endif /* APPVERSION_H_ */
