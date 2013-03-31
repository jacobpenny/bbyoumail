/*
 * transcriptionsettings.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: jpenny
 */

#include "transcriptionsettings.h"

#include <QUuid>

using ymbb10::api::object::TranscriptionSettings;

const QUuid TranscriptionSettings::UUID = QUuid::createUuid();

TranscriptionSettings::TranscriptionSettings() {}
TranscriptionSettings::~TranscriptionSettings() {}

