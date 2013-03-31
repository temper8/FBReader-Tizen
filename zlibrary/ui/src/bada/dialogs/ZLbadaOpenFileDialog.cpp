/*
 * Copyright (C) 2010 Geometer Plus <contact@geometerplus.com>
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
#include "ZLbadaOpenFileDialog.h"
#include <FUi.h>


using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Content;


ZLbadaOpenFileDialog::ZLbadaOpenFileDialog(const std::string &title, const std::string &directoryPath, const std::string &filePath, const Filter &filter) {
//	myDialog = new QFileDialog();
//	myDialog->setCaption(QString::fromUtf8(title.c_str()));
//	myDialog->setDir(QString::fromUtf8(directoryPath.c_str()));
//	myDialog->setSelection(QString::fromUtf8(filePath.c_str()));
	AppLog(" ZLbadaOpenFileDialog title=%s, directoryPath=%s",title.c_str(),directoryPath.c_str());
}

ZLbadaOpenFileDialog::~ZLbadaOpenFileDialog() {
//	delete myDialog;
}


bool ZLbadaOpenFileDialog::run(){
	String tmpContentPath;
	ByteBuffer* bb;
	if (pSearchResultInfo) {
		tmpContentPath = ((ContentInfo*)pSearchResultInfo->GetContentInfo())->GetContentPath();
		bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(tmpContentPath);
		AppLog("tmpContentPath %s",(char*)bb->GetPointer());
		selectedFile =   std::string((const char*)bb->GetPointer());

		//pMessageBox->Construct(L"Открыть файл?", tmpContentPath , MSGBOX_STYLE_OKCANCEL ,3000);
	}
	else
	{
		MessageBox *pMessageBox = new MessageBox();
		pMessageBox->Construct(L"Открыть файл?", L"А нечего открывать :)" , MSGBOX_STYLE_OKCANCEL ,3000);
		int ModalResult;
		pMessageBox->ShowAndWait(ModalResult);
		delete pMessageBox;
		}


/*	AppLog("ZLbadaOpenFileDialog::run()");

	ArrayList* pArgs = new ArrayList();
	pArgs->Construct();
	String str1(L"osp.operation.MAIN");
	pArgs->Add(str1);
	result r = E_SUCCESS;
	AppLog("Tizen::App::Application::Execute");
    r = Tizen::App::Application::Execute(DialogApp::CreateInstance, pArgs);

	if (IsFailed(r))
			{
				AppLog("Application execution failed-[%s].", GetErrorMessage(r));
	 			r &= 0x0000FFFF;
	 		}
	AppLog("Tizen::App::Application::Execute OK");*/
	if (pSearchResultInfo) return true; else return false;
}

bool ZLbadaOpenFileDialog::runInternal() {
//	return myDialog->exec();
}

std::string ZLbadaOpenFileDialog::filePath() const {
	if (pSearchResultInfo) return selectedFile; else return std::string();
//	QString path = myDialog->selectedFile();
	//return "path";// ? std::string() : (const char*)path.utf8();
}

std::string ZLbadaOpenFileDialog::directoryPath() const {
 return "directoryPath";//(const char*)myDialog->dir()->absPath().utf8();
}


