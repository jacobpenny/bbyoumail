/*
 * sqlcontentprovider.h
 *
 *  Created on: Mar 21, 2013
 *      Author: ebrooks
 */

#include "contentprovider.h"
#include "sqlstorage.h"

#ifndef SQLCONTENTPROVIDER_H_
#define SQLCONTENTPROVIDER_H_

class SqlContentProvider : public ContentProvider {
public:
	SqlContentProvider(SqlStorage& storage) : sqlStorage_(storage) {


	}

	QVariant query(QUrl url, const QString& where, const QVariantList& values) {

		QUuid type = getType(url);
		QString tableName = getTableName(type);


	}

	void insert(QUrl url, const QVariantList& values) {
		//sqlStorage_.execute("INSERT INTO " + tableName + " " + getProjectionAsString() + " VALUES " + getValuesAsString(values));
	}

	void update(QUrl url, const QVariantList& values, const QString& where, const QVariantList& values) {

	}

	void remove(QUrl url, const QString& where, const QVariantList& values) {

	}

	QUuid getType(QUrl url) {

	}

	~ContentProvider() {

	}

private:
	QString getTableName(QUuid type) {
		long hashCode = hash(type);
		return typeToTableName_[hashCode];
	}

	long hash(Uuid uuid) const {

	}

private:
	static QHash<long, String> typeToTableName_;
	SqlStorage& sqlStorage_;
};

#endif /* SQLCONTENTPROVIDER_H_ */
