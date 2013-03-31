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
#include <FBaseSys.h>



#include <locale>
//#include <dlfcn.h>
//#include <dirent.h>
//#include <sys/stat.h>

#include <algorithm>

#include <ZLibrary.h>
#include <ZLStringUtil.h>
#include <ZLLogger.h>

#include "ZLibraryImplementation.h"
//#include "ZLbadaLibraryImplementation.h"

const std::string ZLibrary::FileNameDelimiter("/");
const std::string ZLibrary::PathDelimiter(":");
const std::string ZLibrary::EndOfLine("\n");

#include <FBase.h>
#include <FLocales.h>

using namespace Tizen::Base;
using namespace Tizen::Locales;


void ZLibrary::initLocale() {
	LocaleManager localeManager;
	localeManager.Construct();

	// Gets the system locale information.
	Locale  systemLocale = localeManager.GetSystemLocale();
	LanguageCode langCode = systemLocale.GetLanguageCode();
	switch (langCode) {
			case LANGUAGE_ENG :
				ourLanguage = "en";
				break;
			case LANGUAGE_FIN :
				ourLanguage = "fi";
				break;
			case LANGUAGE_RUS :
				ourLanguage = "ru";
				break;
	}
}

ZLibraryImplementation *ZLibraryImplementation::Instance = 0;

ZLibraryImplementation::ZLibraryImplementation() {
	Instance = this;
}

ZLibraryImplementation::~ZLibraryImplementation() {
}

static void *loadPlugin(const std::string &path) {
	AppLog("loadPlugin =%s",path.c_str());
	ZLLogger::Instance().println(ZLLogger::DEFAULT_CLASS, "loading " + path);
	void *handle = 0;//dlopen(path.c_str(), RTLD_NOW);
	if (handle == 0) {
		ZLLogger::Instance().println(ZLLogger::DEFAULT_CLASS, 0);//dlerror());
	}
	return handle;
}

bool ZLibrary::init(int &argc, char **&argv) {
	AppLog("Start initLibrary");
	ZLibraryImplementation::initLibrary();
	//initLibrary();
	if (ZLibraryImplementation::Instance == 0) {
		return false;
	}
	AppLog("ZLibraryImplementation::Instance !=0");
	ZLibraryImplementation::Instance->init(argc, argv);
	return true;
}

ZLPaintContext *ZLibrary::createContext() {
	AppLog("*ZLibrary::createContext()");
	return ZLibraryImplementation::Instance->createContext();
}

void ZLibrary::run(ZLApplication *application) {
	ZLibraryImplementation::Instance->run(application);
}
