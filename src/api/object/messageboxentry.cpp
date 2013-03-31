/*
 * messageboxentry.cpp
 *
 *  Created on: Mar 31, 2013
 *      Author: jpenny
 */

#include "messageboxentry.h"

#include <QUuid>

using ymbb10::api::object::MessageBoxEntry;

const QUuid MessageBoxEntry::UUID = QUuid::createUuid();

MessageBoxEntry::MessageBoxEntry() {}
MessageBoxEntry::~MessageBoxEntry() {}

