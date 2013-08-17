/*
 * TizenComboOptionForm.cpp
 *
 *  Created on: Aug 17, 2013
 *      Author: Alex
 */

#include "TizenComboOptionForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

TizenComboOptionForm::TizenComboOptionForm() {
	// TODO Auto-generated constructor stub

}

TizenComboOptionForm::~TizenComboOptionForm() {
	// TODO Auto-generated destructor stub
}

void TizenComboOptionForm::Initialize(){
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_HEADER |FORM_STYLE_FOOTER );

	Header* pHeader = GetHeader();
    pHeader->SetTitleText(String("title"));

	Footer* pFooter = GetFooter();
//	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);
	pFooter->SetBackButton();
//	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);
}

void TizenComboOptionForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source){
	AppLog("Close button is clicked!");
//	__badaOptionsDialog->accept();
//	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	pPreviousForm->SendUserEvent(0, null);
}
