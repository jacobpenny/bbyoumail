/*
 * ContentProvider.h
 *
 *  Created on: Mar 20, 2013
 *      Author: ebrooks
 */

#ifndef CONTENTPROVIDER_H_
#define CONTENTPROVIDER_H_

#include <QUrl>
#include <QList>
#include <QString>
#include <QVariant>
#include <QUuid>

namespace ymbb10 {
namespace api {
namespace storage {

class ContentProvider {
public:
	QVariant query(QUrl url, const QString& where, const QVariantList& values) = 0;
	void insert(QUrl url, const QVariantList& values) = 0;
	void update(QUrl url, const QVariantList& values, const QString& where, const QVariantList& values) = 0;
	void remove(QUrl url, const QString& where, const QVariantList& values) = 0;
	QUuid getType(QUrl url) = 0;

	virtual ~ContentProvider() = 0;
};

} /* namespace storage */
} /* namespace api */
} /* namespace ymbb10 */
#endif /* CONTENTPROVIDER_H_ */
