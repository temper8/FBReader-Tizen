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


#ifndef ZLBADALIBRARYIMPLEMENTATION_H_
#define ZLBADALIBRARYIMPLEMENTATION_H_

#include "../view/badaApp.h"

using namespace Tizen::Base;
using namespace Tizen::Base::Collection;

#include <ZLApplication.h>
#include <ZLibrary.h>
//#include <ZLLanguageUtil.h>

#include "../../../../core/src/unix/library/ZLibraryImplementation.h"
//#include "ZLibraryImplementation.h"


#include "../filesystem/ZLbadaFSManager.h"

#include "../time/ZLbadaTime.h"
#include "../dialogs/ZLbadaDialogManager.h"
//#include "../image/ZLQtImageManager.h"
//#include "../view/ZLQtPaintContext.h"

#include "../../unix/message/ZLUnixMessage.h"

#include "../../../../core/src/util/ZLKeyUtil.h"


//#include "../../../../core/src/unix/iconv/IConvEncodingConverter.h"
//#include "../../../../core/src/unix/curl/ZLCurlNetworkManager.h"

class ZLbadaLibraryImplementation : public ZLibraryImplementation {

private:
	ArrayList* pArgs;
	//static Tizen::App::Application* Bada2App;
	void init(int &argc, char **&argv);
	ZLPaintContext *createContext();
	void run(ZLApplication *application);

public:

	static badaApp*  myBadaApp;
    static ZLApplication* myZLApplication;
	static void createApplicationWindow();
	static void SetZLApplication(ZLApplication* a) { myZLApplication = a; };
	static void SetBada2App(badaApp* b);
	ZLbadaLibraryImplementation();
	~ZLbadaLibraryImplementation();
};


#endif /* ZLBADALIBRARYIMPLEMENTATION_H_ */
