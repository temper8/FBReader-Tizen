/*
 * AuthenticationForm.cpp
 *
 *  Created on: Mar 25, 2014
 *      Author: Alex
 */

#include "AuthenticationForm.h"
#include "ZLTreeNode.h"

using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;
using namespace Tizen::Ui::Scenes;
using namespace Tizen::Base::Collection;

static const int ID_BUTTON_OK = 101;
static const int ID_BUTTON_CANCEL = 102;

AuthenticationForm::AuthenticationForm(): myPreviousForm(0) {
	// TODO Auto-generated constructor stub

}

AuthenticationForm::~AuthenticationForm() {
	// TODO Auto-generated destructor stub
}

bool AuthenticationForm::Initialize(void)
{
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_HEADER );

	return true;
}

result AuthenticationForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	// Set-up header
	Header* pHeader = GetHeader();
	pHeader->SetTitleText(String("Authentication"));

	SetFormBackEventListener(this);
    // Creates an instance of Label
	userNameLabel = new Label();
	userNameLabel->Construct(Rectangle(50, 50, 600, 60), L"Enter user Name");
	userNameLabel->SetTextConfig(42, LABEL_TEXT_STYLE_NORMAL);
	userNameLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT );
//	userNameLabel->SetBackgroundColor(Color::GetColor(COLOR_ID_BLUE));
    AddControl(userNameLabel);

    userNameEditField = new EditField();
    userNameEditField->Construct(Rectangle(50, 114, 600, 90),EDIT_FIELD_STYLE_EMAIL,INPUT_STYLE_OVERLAY);
    userNameEditField->SetText("temper8@ya.ru");
  //  userNameEditField->AddTextEventListener(*this);
    AddControl(userNameEditField);

    passwordLabel = new Label();
    passwordLabel->Construct(Rectangle(50, 262, 600, 60), L"Enter password");
    passwordLabel->SetTextConfig(42, LABEL_TEXT_STYLE_NORMAL);
    passwordLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT );
  //  passwordLabel->SetBackgroundColor(Color::GetColor(COLOR_ID_BLUE));
    AddControl(passwordLabel);

    passwordEditField = new EditField();
    passwordEditField->Construct(Rectangle(50, 324, 600, 90),EDIT_FIELD_STYLE_PASSWORD,INPUT_STYLE_OVERLAY);
    passwordEditField->SetText("726/830");
    //passwordEditField->AddTextEventListener(*this);

    AddControl(passwordEditField);

	Button* pButton_OK = new Button;
	pButton_OK->Construct(Rectangle(50, 524, 270, 90), L"OK");
	pButton_OK->SetActionId(ID_BUTTON_OK);
	pButton_OK->AddActionEventListener(*this);
	AddControl(pButton_OK);

	Button* pButton_Cancel= new Button;
	pButton_Cancel->Construct(Rectangle(390, 524, 270, 90), L"Cancel");
	pButton_Cancel->SetActionId(ID_BUTTON_CANCEL);
	pButton_Cancel->AddActionEventListener(*this);
	AddControl(pButton_Cancel);
	return r;
}


result AuthenticationForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}


void AuthenticationForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
/*	SceneManager* pSceneManager = SceneManager::GetInstance();
	AppAssert(pSceneManager);
*/
	switch (actionId)
	{
	case ID_BUTTON_OK:
		//userName = userNameEditField->GetText();
		ByteBuffer* userName;
		userName = Tizen::Base::Utility::StringUtil:: StringToUtf8N(userNameEditField->GetText());
		//AppLog( "tmpContentPath %s",(char *)userName->GetPointer());
		//password = passwordEditField->GetText();
		ByteBuffer* password;
		password = Tizen::Base::Utility::StringUtil:: StringToUtf8N(passwordEditField->GetText());
		//if (myNode->authorise("temper8@ya.ru","726/830")) {
		if (myNode->authorise((char *)userName->GetPointer(),(char *)password->GetPointer())) {
			myPreviousForm->SendUserEvent(10, null);
		}
		else
			myPreviousForm->SendUserEvent(0, null);
		break;

	case ID_BUTTON_CANCEL:
		myPreviousForm->SendUserEvent(0, null);
		break;

	}
}

void AuthenticationForm::SetPreviousForm(Tizen::Ui::Controls::Form* form){
	myPreviousForm = form;
}

void AuthenticationForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source)
{
	myPreviousForm->SendUserEvent(0, null);
//	SceneManager* pSceneManager = SceneManager::GetInstance();
//	AppAssert(pSceneManager);
//	pSceneManager->GoBackward(BackwardSceneTransition(SCENE_TRANSITION_ANIMATION_TYPE_RIGHT));
}
