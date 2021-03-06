/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <FBase.h>

#include <ZLDialogManager.h>
#include <ZLRunnable.h>
#include <ZLibrary.h>
#include <ZLOptions.h>

#include "ZLApplication.h"

class ConfigSaverRunnable : public ZLRunnable {

public:
	void run() {
		ZLOption::deleteInstance();
	}
};

ZLApplicationBase::ZLApplicationBase(const std::string &name) {
	AppLog("Create ZLApplicationBase");
	ZLibrary::initApplication(name);
	AppLog("ZLibrary::initApplication ");
	ZLOption::createInstance();
	AppLog("ZLOption::createInstance() ");
}

ZLApplicationBase::~ZLApplicationBase() {
	ConfigSaverRunnable configSaver;
	//ZLDialogManager::Instance().wait(ZLResourceKey("savingConfig"), configSaver);
	configSaver.run();
}
