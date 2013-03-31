/*
 * apiobject.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: jpenny
 */

#include "apiobject.h"

#include <QUuid>

using ymbb10::api::object::ListApiObject;
using ymbb10::api::object::Visitable;
using ymbb10::api::object::Transient;

template <typename T>
const QUuid ListApiObject<T>::UUID = QUuid::createUuid();

Visitable::~Visitable() {}
Transient::~Transient() {}
