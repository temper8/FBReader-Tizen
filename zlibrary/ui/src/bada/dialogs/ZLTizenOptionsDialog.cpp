/*
 * ZLTizenOptionsDialog.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: Alex
 */

#include "ZLTizenOptionsDialog.h"
#include "ZLTizenDialogContent.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

ZLTizenOptionsDialog::ZLTizenOptionsDialog(Form   *PreviousForm, const ZLResource &resource, shared_ptr<ZLRunnable> applyAction, bool showApplyButton) :  ZLOptionsDialog(resource, applyAction){//,myMenuView(0){
	AppLog("ZLbadaOptionsDialog resource name = %s",resource.name().c_str());
	result r = E_SUCCESS;
	AppLog("ZLbadaOptionsDialog caption() = %s",caption().c_str());

	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	myDialogForm = new TizenDialogForm;

	//myDialogForm->showApplyButton = true;
	//myDialogForm->__badaOptionsDialog = this;
	myDialogForm->Initialize(caption().c_str(),showApplyButton);

	myDialogForm->SetPreviousForm(pFrame->GetCurrentForm());
	r = pFrame->AddControl(*myDialogForm);
	r = pFrame->SetCurrentForm(*myDialogForm);
	AppLog("pFrame->SetCurrentForm(*myDialogForm);");

}


ZLTizenOptionsDialog::~ZLTizenOptionsDialog() {
	// TODO Auto-generated destructor stub
}

ZLDialogContent &ZLTizenOptionsDialog::createTab(const ZLResourceKey &key){
  AppLog("ZLbadaOptionsDialog::createTab = %s",key.Name.c_str());
 ZLTizenDialogContent *tab = new ZLTizenDialogContent(myDialogForm, tabResource(key));
//  myDialogForm->AddTab(key.Name.c_str());
  //ZLQtDialogContent *tab = new ZLQtDialogContent(new QWidget(myTabWidget), tabResource(key));
  //myTabWidget->addTab(tab->widget(), ::qtString(tab->displayName()));
 //TODO проследить за уничторежнием TABов... чувствую тут проблема возможна
  myTabs.push_back(tab);
  return *tab;
}

bool ZLTizenOptionsDialog::run(){
  AppLog("ZLbadaOptionsDialog::run()");
	result r = E_SUCCESS;
	//AppLog("CreateDalogForm %s",name);

	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	r = pFrame->Draw();
	AppLog("pFrame->Draw();");
	r = pFrame->Show();
	AppLog("pFrame->Show()");
  return true;
}

const std::string &ZLTizenOptionsDialog::selectedTabKey() const {
	 AppLog("&ZLbadaOptionsDialog::selectedTabKey()");
	 return std::string();
}

void ZLTizenOptionsDialog::selectTab(const ZLResourceKey &key){
	 AppLog("&ZLbadaOptionsDialog::selectTab()= %s",key.Name.c_str());
}


void ZLTizenOptionsDialog::apply() {
	ZLOptionsDialog::accept();
}

void ZLTizenOptionsDialog::setMenuEntry(ZLMenuOptionEntry* option){
	AppLog("&ZLbadaOptionsDialog::setMenuEntry()");
//	myMenuView = new MenuView(std::string(), std::string(), (ZLMenuOptionEntry*)option, null, 0, 0, 0);
//	myDialogForm->setMenuView(myMenuView);
}


