/*
 * alertsettings.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: jpenny
 */

#include "alertsettings.h"

#include <QUuid>

using ymbb10::api::object::AlertSettings;

const QUuid AlertSettings::UUID = QUuid::createUuid();

AlertSettings::AlertSettings() {}
AlertSettings::~AlertSettings() {}

