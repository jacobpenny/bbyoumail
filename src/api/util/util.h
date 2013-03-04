/*
 * util.h
 *
 *  Created on: Feb 17, 2013
 *      Author: ebrooks
 */

#ifndef UTIL_H_
#define UTIL_H_

namespace ymbb10 {
namespace util {

inline bool toBooleanJacob(const QString& s) {
	return s == "true" || s.toLong() > 0;
}

}
}

#endif /* UTIL_H_ */
