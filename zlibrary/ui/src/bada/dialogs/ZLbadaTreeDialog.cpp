/*
 * Copyright (C) 2004-2011 Geometer Plus <contact@geometerplus.com>
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

#include <ZLTreeActionNode.h>
#include <ZLTreePageNode.h>
#include <ZLTimeManager.h>
#include "ZLbadaTreeDialog.h"


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;



ZLbadaTreeDialog::ZLbadaTreeDialog(const ZLResource &resource) : ZLTreeDialog(resource), __pThread(null)
{
	AppLog("ZLbadaTreeDialog::ZLbadaTreeDialog()");

	result r = E_SUCCESS;
	AppLog("new TreeViewForm");
   	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	myForm = new TreeViewForm;
	AppLog("new ZLbadaTreeModel");
	//myRootNode = ;
	myCurrentNode = &rootNode();
	myForm->SetPreviousForm(pFrame->GetCurrentForm());
	//myForm->Initialize(resource["title"].value().c_str());
	myForm->Initialize(this);
	AppLog("ZLbadaTreeDialog->Initialize()");
	r = pFrame->AddControl(*myForm);
	r = pFrame->SetCurrentForm(*myForm);
	//myForm->SetPreviousForm(PreviousForm);
     //   myView->setItemDelegate(new SubtitleDelegate);
}

ZLbadaTreeDialog::~ZLbadaTreeDialog() {
	AppLog("ZLbadaTreeDialog::~ZLbadaTreeDialog()");
//	delete myForm;
//	aliveTrees()->remove(this);
}

void ZLbadaTreeDialog::setShowIcons(bool value){
	showIcons =  value;
	if (myForm) myForm->showIcons =  value;
}

Object* ZLbadaTreeDialog::Run(void){
	AppLog("__pThread Run");
	myForm->requestUpdateHeader();

	myCurrentNode->setChildrenUpdateListner(new ZLTreeDialogUpdater(this));

	myCurrentNode->requestChildren(0);

	 AppLog("enter node 2");
	 myForm->requestUpdateContent();
	// myForm->SendUserEvent(999,null);
	 AppLog("UpdateContent finish enter");
	 if (showIcons&&!__terminateThread){
		 AppLog("start loadCovers");
		 __pThread->Sleep(1000);
		 AppLog("after Sleep");
		 loadCovers();
	 }
	 myForm->GetHeader()->StopWaitingAnimation(HEADER_ANIMATION_POSITION_TITLE);
	 myForm->Invalidate(true);
//	 myForm->RequestRedraw(true);
	AppLog("__pThread Run end");
	return null;
}

bool ZLbadaTreeDialog::exitThread(){
	//int exitCode = 0;
	//__pThread->GetExitCode(exitCode);
	//bool exit;
	//AppLog("exitCode %d",exitCode );
	//__pMonitor->Enter();
	//__pMonitor->Wait();
	//__pMonitor->Exit();
	return __terminateThread;
}

bool ZLbadaTreeDialog::back() {
	AppLog("ZLbadaTreeDialog::back()");
	if (__pThread) {
		AppLog("wait terminateThread ");
		__terminateThread = true;
		//__pThread->Exit(1);
		__pThread->Join();
		AppLog("Join");
		delete __pThread;
		__pThread = null;
	}
	if (myCurrentNode == &rootNode()) {
		return false;
	}
	myCurrentNode = myCurrentNode->parent();
	myForm->updateHeader();
	myForm->updateContent();
	 AppLog("UpdateContent finish back");
	 if (showIcons){
		 __pThread = new Thread();
		 __pThread->Construct(*this,THREAD_PRIORITY_LOW);
		 //pHeader->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_TITLE);
		 //__pListView->SetTextOfEmptyList(L"Loading...");
		 __terminateThread = false;
		 __pThread->Start();
	 }
	return true;
}

void ZLbadaTreeDialog::treadTerminator(){
	if (__pThread) {
		__terminateThread = true;
		//__pThread->Exit(1);
		__pThread->Join();
		 AppLog("Join");
		delete __pThread;
		__pThread = null;
	}
}

void ZLbadaTreeDialog::onUpdated(){
	 AppLog("###### onUpdated");
	 myForm->SendUserEvent(997,null);
	//myForm->requestUpdateContent();
	// myForm->updateContent();
}

bool ZLbadaTreeDialog::enter(ZLTreeNode* node) {
	 AppLog("enter node");
	if (__pThread) {
		 AppLog("wait terminateThread ");
		__terminateThread = true;
		//__pThread->Exit(1);
		__pThread->Join();
		 AppLog("Join");
		delete __pThread;
		__pThread = null;
	}
	 AppLog("__pThread kill????");
	 myCurrentNode = node;
	 AppLog("enter node 1");
//	 myCurrentNode->requestChildren(0);
	 AppLog("enter node 2");
//	 myForm->UpdateContent();

	 AppLog("UpdateContent finish enter");
	// if (showIcons)
	 {
		// loadCovers();
		 __pThread = new Thread();
		 __pThread->Construct(*this,THREAD_PRIORITY_LOW);
		__terminateThread = false;
		myForm->GetHeader()->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_TITLE  );
		__pThread->Start();
	 }
	/* result r;
		AppLog("GetFrame");
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		r = pFrame->Draw();
		AppLog("pFrame->Draw();");
		r = pFrame->Show();
		AppLog("pFrame->Show()");*/
	return true;
}

void ZLbadaTreeDialog::updateNode(ZLTreeTitledNode &node, int index){
	AppLog("updateNode %d", index);
	//myForm->updateItem(node, index);
	myForm->SendUserEvent(1000+index,null);
}
/*
bool ZLbadaTreeDialog::isAlive(ZLbadaTreeDialog *dialog) {
	return true;//aliveTrees()->contains(dialog);
}
*/
void ZLbadaTreeDialog::run() {
	AppLog("ZLbadaTreeDialog::run");
//	Tizen::Base::Runtime::Monitor* pMonitor = new Tizen::Base::Runtime::Monitor;
//	pMonitor->Construct();
//	myForm->myMonitor = pMonitor;

	result r = E_SUCCESS;
	//myForm->UpdateContent();
/*
	if (__pThread) {
		__terminateThread = true;
		__pThread->Exit(1);
		__pThread->Join();
		 AppLog("Join");
		delete __pThread;
		__pThread = null;
	}
	*/
	 //myCurrentNode = node;
	// myCurrentNode->requestChildren(myWaitWidgetListener);

//	myForm->updateHeader();
//	myForm->updateContent();

	 AppLog("UpdateContent finish run");
//	 if (showIcons)
	 {
			__pThread = new Thread();
			__pThread->Construct(*this,THREAD_PRIORITY_LOW);
				//pHeader->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_TITLE);
				//__pListView->SetTextOfEmptyList(L"Loading...");
			__terminateThread = false;
			__pThread->Start();
		 }
	AppLog("GetFrame");
	//Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	//r = pFrame->Draw();
	AppLog("pFrame->Draw();");
	//r = pFrame->Show();
	AppLog("pFrame->Show()");
	//myForm->Start();
	//pMonitor->Enter();
	//AppLog("Enter");
	//pMonitor->Wait();
	//AppLog("doAfter");
	//pMonitor->Exit();

}


void ZLbadaTreeDialog::onNodeBeginInsert(ZLTreeNode *parent, size_t index) {
	AppLog("ZLbadaTreeDialog::onNodeBeginInsert");
     //   myModel->onNodeBeginInsert(parent,index);
}

void ZLbadaTreeDialog::onNodeEndInsert() {
	AppLog("ZLbadaTreeDialog::onNodeEndInsert");
    //    myModel->onNodeEndInsert();
	// myForm->requestUpdateContent();
}

void ZLbadaTreeDialog::onNodeBeginRemove(ZLTreeNode *parent, size_t index) {
	AppLog("ZLbadaTreeDialog::onNodeBeginRemove");
     //   myModel->onNodeBeginRemove(parent,index);
}
void ZLbadaTreeDialog::onNodeEndRemove() {
	AppLog("ZLbadaTreeDialog::onNodeEndRemove");
    //    myModel->onNodeEndRemove();
}


void ZLbadaTreeDialog::onNodeUpdated(ZLTreeNode *node) {
	AppLog("ZLbadaTreeDialog::onNodeUpdated");
   // myModel->onNodeUpdated(node);
}


TreeActionListener::TreeActionListener() : myIsFinished(false) {

}

bool TreeActionListener::isFinished() const {
    return myIsFinished;
}


void TreeActionListener::showPercent(int ready, int full) {
  //  emit percentChanged(ready,full);
}


