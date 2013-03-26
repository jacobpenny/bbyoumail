/*
 * sqlcontentprovider.h
 *
 *  Created on: Mar 21, 2013
 *      Author: ebrooks
 */

#include "contentprovider.h"
#include "sqlstorage.h"

#include <QRegExp>
#include <bb/data/SqlDataAccess>


#ifndef SQLCONTENTPROVIDER_H_
#define SQLCONTENTPROVIDER_H_

class SqlContentProvider : public ContentProvider {
public:
	SqlContentProvider(SqlStorage& storage) : sqlStorage_(storage) {

	}

	QVariant query(QUrl url, const QString& whereClause, const QVariantList& whereArgs) {

		QUuid type = getType(url);
		QString tableName = getTableName(type);

		bb::data::SqlDataAccess* pDataAccess = sqlStorage_.getDataAccess();

		switch(hash(type)) {
		case MESSAGES:
			QString q = "SELECT * from " + tableName;
			if (whereClause) {
				q += "WHERE " + parameterize(whereClause, whereArgs);
			}
			return pDataAccess->execute(q);
			break;

		}
	}

	void insert(QUrl url, const QVariantList& values) {
		//sqlStorage_.execute("INSERT INTO " + tableName + " " + getProjectionAsString() + " VALUES " + getValuesAsString(values));
	}

	void update(QUrl url, const QVariantList& values, const QString& where, const QVariantList& values) {

	}

	void remove(QUrl url, const QString& where, const QVariantList& values) {

	}

	QUuid getType(QUrl url) {
		QString urlStr = url.toString();
		QRegExp regexp;

		regexp.setPattern("messages/\d+$"); // or  db://messages/\d+$     ?
		Q_ASSERT(regexp.isValid());
		if (regexp.indexIn(urlStr) > 0) { return MessageBoxEntry::UUID; }

		regexp.setPattern("messages/?$");
		Q_ASSERT(regexp.isValid());
		if (regexp.indexIn(urlStr) > 0) { return ListApiObject<MessageBoxEntry>::UUID; }

		regexp.setPattern("folders/\d+$");
		Q_ASSERT(regexp.isValid());
		if (regexp.indexIn(urlStr) > 0) { return MessageBoxFolder::UUID; }

		regexp.setPattern("folders/?$");
		Q_ASSERT(regexp.isValid());
		if (regexp.indexIn(urlStr) > 0) { return ListApiObject<MessageBoxFolder>::UUID; }
	}

	QString parameterize(const QString& whereClause, const QVariantList& whereArgs) {
		Q_ASSERT(whereClause.count('?') == whereArgs.size());

		QString result = whereClause;
		for (int i = 0; i < whereArgs.size(); i++) {
			result.replace(result.indexOf('?'), 0, whereArgs.at(i).toString());
		}
		return result;
	}

	~ContentProvider() {

	}

private:
	QString getTableName(QUuid type) {
		long hashCode = hash(type);
		return typeToTableName_[hashCode];
	}

	long hash(QUuid uuid) const {

	}

private:
	static QHash<long, String> typeToTableName_;
	SqlStorage& sqlStorage_;
};

#endif /* SQLCONTENTPROVIDER_H_ */
