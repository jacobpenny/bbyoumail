/*
 * sqlstorage.h
 *
 *  Created on: Feb 19, 2013
 *      Author: ebrooks
 */

#ifndef SQLSTORAGE_H_
#define SQLSTORAGE_H_

#include "storagemanager.h"
#include "settings/appsettings.h"

#include <bb/data/SqlDataAccess>
#include <exception>
#include <QString>


namespace ymbb10 {
namespace storage {

class SqlException : public std::runtime_error {
public:
	SqlException(const bb::data::DataAccessError& error) : runtime_error(error.errorMessage().toStdString()), error_(error) {};
	// TODO(ebrooks): Implementation

	const bb::data::DataAccessError& getDataAccessError() const { return error_; }

private:
	bb::data::DataAccessError error_;
};

class SqlStorage : public StorageManager {
public:
	SqlStorage(const QString& dbPath) : dbPath_(dbPath) {};

	virtual ~SqlStorage() {};

protected:
	virtual void onCreate() {

		dataAccess_->execute(QString("CREATE TABLE users(" \
						"id INT PRIMARY KEY NOT NULL," \
						"created INT NOT NULL," \
						"updated INT NOT NULL" \
						"phoneNumber VARCHAR(64) NOT NULL);"));


		dataAccess_->execute("CREATE TABLE folders(" \
						"id INT PRIMARY KEY NOT NULL," \
						"userId INT NOT NULL," \
						"created INT NOT NULL," \
						"updated INT NOT NULL," \
						"sysType INT NOT NULL," \
						"lastEntryUpdated INT NOT NULL," \
						"visibleEntryCount INT NOT NULL," \
						"newEntryCount INT NOT NULL," \
						"localVisibleEntryCount INT NOT NULL," \
						"name VARCHAR(64) NOT NULL," \
						"description VARCHAR(64) NULL," \
						"FOREIGN KEY(userId) REFERENCES users(id));");

		dataAccess_->execute("CREATE TABLE messages(" \
				"id INT PRIMARY KEY NOT NULL," \
				"userId INT NOT NULL," \
				"created INT NOT NULL," \
				"updated INT NOT NULL," \
				"createSource INT NOT NULL," \
				"deleted INT NOT NULL DEFAULT 0," \
				"callerName VARCHAR(128)," \
				"firstName VARCHAR(64)," \
				"lastName VARCHAR(64)," \
				"flagged INT NOT NULL," \
				"spamRating INT NOT NULL," \
				"priority INT NOT NULL," \
				"imageUrl VARCHAR(128) NULL,"
				"messageDataUrl VARCHAR(128) NOT NULL," \
				"status INT NOT NULL," \
				"targetUserId INT NOT NULL," \
				"type INT NOT NULL," \
				"contactType INT NOT NULL," \
				"contactWildMatched INT NOT NULL," \
				"folderId INT NOT NULL DEFAULT 0," \
				"length INT NOT NULL DEFAULT 0," \
				"source VARCHAR(64) NOT NULL," \
				"transcriptionStatus INT NOT NULL DEFAULT 0," \
				"transcriptionText VARCHAR(65535) NULL" \
				"destination VARCHAR(64) NOT NULL," \
				"silentMode INT NOT NULL," \
				"phonebookSourceType VARCHAR(16) NOT NULL," \
				"phonebookSourceId INT NOT NULL DEFAULT 0," \
				"FOREIGN KEY(folderId) REFERENCES folders(id)," \
				"FOREIGN KEY(userId) REFERENCES users(id));");

		dataAccess_->execute("CREATE TABLE images(" \
				"id INT PRIMARY KEY NOT NULL," \
				"userId INT NOT NULL," \
				"imageUrl VARCHAR(64) NOT NULL," \
				"created INT NOT NULL," \
				"updated INT NOT NULL," \
				"downloadStatus INT NOT NULL," \
				"imageType INT NOT NULL," \
				"localPath VARCHAR(64) NOT NULL," \
				"FOREIGN KEY(userId) REFERENCES users(id));");
	}

	virtual void onUpgrade(int oldVersion, int newVersion) {
		if (oldVersion < newVersion) {
			// Do upgrade
			switch (newVersion) {
			default:
				// Noop
				break;
			}
		}
	}

	virtual void onOpen(bool readOnly) {
		// TODO(ebrooks): logging
		int newVersion = settings_.value(ymbb10::settings::APP_VERSION).toInt();
		int prevVersion = settings_.value(ymbb10::settings::PREV_APP_VERSION).toInt();

		dataAccess_ = new bb::data::SqlDataAccess(dbPath_, "SqlStorageManager");
		if (dataAccess_->hasError()) {
			throw SqlException(dataAccess_->error());
		}

		if (0 == prevVersion) {
			onCreate();
		} else if (prevVersion < newVersion) {
			onUpgrade(prevVersion, newVersion);
		} else {
			// Already created/up to date
		}
	}

	virtual void onDestroy() {
		dataAccess_->execute("DROP TABLE messages;");
		dataAccess_->execute("DROP TABLE folders;");
		dataAccess_->execute("DROP TABLE users;");
		dataAccess_->execute("DROP TABLE images;");
	}

	virtual void onExport(QByteArray* pOut) {
		Q_ASSERT(false && "Not implemented");
	}

private:
	bb::data::SqlDataAccess* dataAccess_; // make into scoped pointer, use reset()
	QSettings settings_;
	QString dbPath_;
};

} /* namespace storage */
} /* namespace ymbb10 */
#endif /* SQLSTORAGE_H_ */
