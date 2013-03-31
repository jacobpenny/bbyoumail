/*
 * preferences.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: jpenny
 */

#include "preferences.h"

#include <QUuid>

using ymbb10::api::object::Preferences;

const QUuid Preferences::UUID = QUuid::createUuid();

Preferences::Preferences() {}
Preferences::~Preferences() {}

