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

#include "ZLbadaLibraryImplementation.h"
#include "../view/ZLbadaPaintContext.h"
#include "../image/ZLbadaImageManager.h"
#include "../../../../core/src/unix/iconv/IConvEncodingConverter.h"
#include "../../../../core/src/unix/xmlconfig/XMLConfig.h"
//#include "../../../../core/src/unix/curl/ZLCurlNetworkManager.h"
#include "../network/ZLbadaNetworkManager.h"
//#include "IConvEncodingConverter.h"

void ZLibraryImplementation::initLibrary() {
	AppLog("initLibrary()");
	new ZLbadaLibraryImplementation();
}

ZLbadaLibraryImplementation::ZLbadaLibraryImplementation():ZLibraryImplementation() {

	AppLog("ZLBadaLibraryImplementation()");
}

ZLbadaLibraryImplementation::~ZLbadaLibraryImplementation() {
	 pArgs->RemoveAll(true);
	 delete pArgs;
	AppLog("~ZLBadaLibraryImplementation()");
}


void ZLbadaLibraryImplementation::init(int &argc, char **&argv) {
	//new QApplication(argc, argv);
	AppLog("ZLBadaLibraryImplementation::init");
	ZLibrary::parseArguments(argc, argv);
	AppLog("ZLibrary::parseArguments");
	pArgs = new ArrayList();
	pArgs->Construct();
	for (int i = 0; i < argc; i++)
	{
		pArgs->Add(*(new String(argv[i])));
		AppLog("pArgs %d - %s",i, argv[i]);
	}

	XMLConfigManager::createInstance();
	ZLbadaTimeManager::createInstance();
	AppLog("ZLbadaTimeManager::createInstance();");
	ZLbadaFSManager::createInstance();
	AppLog("ZLbadaFSManager::createInstance();");
	ZLbadaDialogManager::createInstance();
	AppLog("ZLbadaDialogManager::createInstance();");
	ZLUnixCommunicationManager::createInstance();
	AppLog("ZLUnixCommunicationManager::createInstance();");
	ZLbadaImageManager::createInstance();
	AppLog("ZLbadaImageManager::createInstance();");
	ZLEncodingCollection::Instance().registerProvider(new IConvEncodingConverterProvider());
	AppLog("ZLEncodingCollection::Instance().registerProvider");
	ZLbadaNetworkManager::createInstance();
	AppLog("ZLbadaNetworkManager::Instance()");
	ZLKeyUtil::setKeyNamesFileName("keynames.xml");
}

ZLPaintContext *ZLbadaLibraryImplementation::createContext() {
	AppLog("ZLBadaLibraryImplementation::createContext()");
	return new ZLbadaPaintContext();
}

badaApp*  ZLbadaLibraryImplementation::myBadaApp;
ZLApplication* ZLbadaLibraryImplementation::myZLApplication;

void ZLbadaLibraryImplementation::SetBada2App(badaApp* b) {
	myBadaApp = b;
}

void  ZLbadaLibraryImplementation::createApplicationWindow() {

	AppLog("createApplicationWindow(ZLApp)");
	ZLDialogManager::Instance().createApplicationWindow(myZLApplication);
	//ZLBadaApplicationWindow *b = ZLApp->myApp
//	myZLApplication->initWindow();
}

void ZLbadaLibraryImplementation::run(ZLApplication *application) {
//	if (ZLLanguageUtil::isRTLLanguage(ZLibrary::Language())) {
//		qApp->setLayoutDirection(Qt::RightToLeft);
//	}

	//ZLDialogManager::Instance().createApplicationWindow(application);
	//application->initWindow();
	SetZLApplication(application);
	result r = E_SUCCESS;
	//B2App::SetZLApplication(application);
	AppLog("ZLBadaLibraryImplementation::run");
	r = Tizen::App::Application::Execute(badaApp::CreateInstance, pArgs);

	if (IsFailed(r))
		{
			AppLog("Application execution failed-[%s].", GetErrorMessage(r));
			r &= 0x0000FFFF;
		}
	delete application;
}
