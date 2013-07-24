/*
 * TizenDialogForm.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: Alex
 */

#include "TizenDialogForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;

TizenDialogForm::TizenDialogForm() {
	// TODO Auto-generated constructor stub

}

TizenDialogForm::~TizenDialogForm() {
	// TODO Auto-generated destructor stub
}

bool TizenDialogForm::Initialize(const char *title, bool __showApplyButton)
{
	showApplyButton = __showApplyButton;
	AppLog("DialogForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_HEADER |FORM_STYLE_FOOTER );

	Header* pHeader = GetHeader();
    pHeader->SetTitleText(String(title));

	Footer* pFooter = GetFooter();
//	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);
	pFooter->SetBackButton();
//	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);
	return true;
}


void TizenDialogForm::SetPreviousForm(Tizen::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}


void TizenDialogForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source){
	AppLog("Close button is clicked!");
//	__badaOptionsDialog->accept();
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	pPreviousForm->SendUserEvent(0, null);
}
