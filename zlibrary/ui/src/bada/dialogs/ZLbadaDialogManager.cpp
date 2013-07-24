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



//#include "ZLQtDialogContent.h"
#include "ZLbadaProgressDialog.h"
//#include "ZLQtUtil.h"

//#include "../image/ZLQtImageManager.h"

#include <FBase.h>
#include <FContent.h>
#include "../application/ZLbadaApplicationWindow.h"
#include "../view/badaForm.h"
#include "../view/ZLbadaViewWidget.h"
#include "ZLbadaDialog.h"
#include "ZLbadaDialogManager.h"
#include "ZLbadaOpenFileDialog.h"
#include "ZLTizenOptionsDialog.h"
#include "ZLbadaTreeDialog.h"
#include "ZLTypeId.h"

using namespace Tizen::App;
using namespace Tizen::Ui::Controls;

void ZLbadaDialogManager::createApplicationWindow(ZLApplication *application) const {
	myApplicationWindow = new ZLbadaApplicationWindow(application);
}


shared_ptr<ZLDialog> ZLbadaDialogManager::createDialog(const ZLResourceKey &key) const {
	AppLog("ZLbadaDialogManager::createDialog");
	return new ZLbadaDialog(resource()[key]);
}


shared_ptr<ZLOptionsDialog> ZLbadaDialogManager::createOptionsDialog(const ZLResourceKey &key, shared_ptr<ZLRunnable> applyAction, bool showApplyButton) const {
	AppLog("ZLbadaDialogManager::createOptionsDialog");
	//ZLbadaOptionsDialog* b= new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
	//mybadaOptionsDialog =new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
	shared_ptr<ZLOptionsDialog> b = new ZLTizenOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	TizenDialogForm* d = (TizenDialogForm*)pFrame->GetCurrentForm();
	d->__badaOptionsDialog = b;
	//b->myDialogForm = myApplicationWindow->viewWidget().mybadaForm->CreateDalogForm();
	return b;//new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
}

/*
shared_ptr<ZLOptionsDialog> ZLbadaDialogManager::createOptionsDialog(const ZLResourceKey &key, shared_ptr<ZLRunnable> applyAction, bool showApplyButton) const {
	AppLog("ZLbadaDialogManager::createOptionsDialog");
	//ZLbadaOptionsDialog* b= new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
	//mybadaOptionsDialog =new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
	shared_ptr<ZLOptionsDialog> b = new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	DialogForm* d = (DialogForm*)pFrame->GetCurrentForm();
	d->__badaOptionsDialog = b;
	//b->myDialogForm = myApplicationWindow->viewWidget().mybadaForm->CreateDalogForm();
	return b;//new ZLbadaOptionsDialog(myApplicationWindow->viewWidget().mybadaForm,resource()[key], applyAction, showApplyButton);
}

*/

shared_ptr<ZLOpenFileDialog> ZLbadaDialogManager::createOpenFileDialog(const ZLResourceKey &key, const std::string &directoryPath, const std::string &filePath, const ZLOpenFileDialog::Filter &filter) const {
//TODO корректно ли без shared_pt<>?
	ZLbadaOpenFileDialog *b= new ZLbadaOpenFileDialog(dialogTitle(key), directoryPath, filePath, filter);
	AppLog("ZLbadaDialogManager::createOpenFileDialog");
	b->pSearchResultInfo = myApplicationWindow->viewWidget().mybadaForm->pSearchResultInfo;
	return b;
}

void ZLbadaDialogManager::startOpenFileDialog() const{
	myApplicationWindow->viewWidget().mybadaForm->goOpenFileForm();
}

void ZLbadaDialogManager::informationBox(const std::string &title, const std::string &message) const {
	MessageBox messageBox;
	messageBox.Construct(title.c_str(), message.c_str(), MSGBOX_STYLE_NONE , 2000);

	// Calls ShowAndWait - draw, show itself and process events
	int modalResult = 0;
	messageBox.ShowAndWait(modalResult);

}

void ZLbadaDialogManager::errorBox(const ZLResourceKey &key, const std::string &message) const {
/*	QMessageBox::critical(
		qApp->mainWidget(),
		::qtString(dialogTitle(key)),
		::qtString(message),
		::qtButtonName(OK_BUTTON)
	);*/
}

int ZLbadaDialogManager::questionBox(const ZLResourceKey &key, const std::string &message, const ZLResourceKey &button0, const ZLResourceKey &button1, const ZLResourceKey &button2) const {
	AppLog("ZLbadaDialogManager::questionBox");

	MessageBox messageBox;
	messageBox.Construct(dialogTitle(key).c_str(), message.c_str(), MSGBOX_STYLE_YESNO, 0);

	// Calls ShowAndWait - draw, show itself and process events
	int modalResult = 0;
	messageBox.ShowAndWait(modalResult);
    AppLog("modalResult %d", modalResult);
    int r;
	switch(modalResult)
	   {
	    case MSGBOX_RESULT_YES:
	    	AppLog("modalResult Yes");
	    	r = 0;
	        break;

	    case MSGBOX_RESULT_CANCEL:
		   	AppLog("modalResult Cancel");
		    r = 1;
		    break;

	    default:
	    	r = 1;
	        break;
	    }
	AppLog("r %d", r);

	return r;
			/*
			QMessageBox::question(
		qApp->mainWidget(),
		::qtString(dialogTitle(key)),
		::qtString(message),
		::qtButtonName(button0),
		::qtButtonName(button1),
		::qtButtonName(button2)
	);*/
}

shared_ptr<ZLProgressDialog> ZLbadaDialogManager::createProgressDialog(const ZLResourceKey &key) const {
	return new ZLbadaProgressDialog(key);
}

/*
bool ZLQtDialogManager::isClipboardSupported(ClipboardType type) const {
	return true;
}

void ZLQtDialogManager::setClipboardText(const std::string &text, ClipboardType type) const {
	if (!text.empty()) {
		qApp->clipboard()->setText(
			::qtString(text),
			(type == CLIPBOARD_MAIN) ? QClipboard::Clipboard : QClipboard::Selection
		);
	}
}

void ZLQtDialogManager::setClipboardImage(const ZLImageData &imageData, ClipboardType type) const {
	qApp->clipboard()->setImage(
		(ZLQtImageData&)imageData,
		(type == CLIPBOARD_MAIN) ? QClipboard::Clipboard : QClipboard::Selection
	);
}
*/


shared_ptr<ZLTreeDialog> ZLbadaDialogManager::createTreeDialog(const ZLResourceKey &key) const {
	AppLog("ZLbadaDialogManager::createTreeDialog");

	//myTreeDialog = new ZLbadaTreeDialog(resource()[key]);
	//return myTreeDialog;

	shared_ptr<ZLTreeDialog> b = new ZLbadaTreeDialog(resource()[key]);
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	TreeViewForm* d = (TreeViewForm*)pFrame->GetCurrentForm();
	d->__myTreeDialog = b;
   return b;

}

shared_ptr<ZLTreeDialog> ZLbadaDialogManager::myTreeDialog = 0;

void 	ZLbadaDialogManager::deleteTreeDialog(){
	//delete myTreeDialog;
	myTreeDialog = 0;
}

shared_ptr<ZLDialogContent> ZLbadaDialogManager::createContent(const ZLResourceKey &key) const {
	AppLog("ZLbadaDialogManager::createTreeDialog");
	//return new ZLbadaDialogContent(resource()[key]);
}

