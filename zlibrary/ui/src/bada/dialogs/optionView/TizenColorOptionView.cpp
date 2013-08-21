/*
 * TizenColorOptionView.cpp
 *
 *  Created on: Aug 21, 2013
 *      Author: temper8
 */

#include "TizenColorOptionView.h"

#include <FApp.h>
#include <FIo.h>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Content;
using namespace Tizen::Graphics;
using namespace Tizen::Base::Runtime;


void TizenColorOptionView::OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment){
	//tmpValue = adjustment;
	tmpColor = ZLColor(sliderR->GetValue(),sliderG->GetValue(),sliderB->GetValue());
	panelColor->SetBackgroundColor(Tizen::Graphics::Color(tmpColor.Red,tmpColor.Green, tmpColor.Blue));
	panelColor->Invalidate(false);

}


void TizenColorOptionView::CreateColorPopup(void){
	  int PopupHeight = 560;
	  int sliderWidth = 350;
	  int sliderHeight = 100;
	  int dx = 150;

	  pPopup = new Popup();
	  pPopup->Construct(true, Dimension(540,PopupHeight));
	  pPopup->SetTitleText(L"Select color");

	Button* pCreateButton = new Button();
		pCreateButton->Construct(Rectangle(20, PopupHeight - 180, 200, 70), L"OK");
		pPopup->AddControl(*pCreateButton);
		pCreateButton->SetActionId(ID_BUTTON_OK);
		pCreateButton->AddActionEventListener(*this);


		Button* pCancelButton = new Button();
		pCancelButton->Construct(Rectangle(230, PopupHeight - 180, 200, 70), L"Cancel");
		pPopup->AddControl(*pCancelButton);
		pCancelButton->SetActionId(ID_BUTTON_CANCEL);
		pCancelButton->AddActionEventListener(*this);

		panelColor = new Panel();
		panelColor->Construct(Rectangle(10, 15, dx-10, 3*sliderHeight-20));
		panelColor->SetBackgroundColor(Tizen::Graphics::Color(tmpColor.Red,tmpColor.Green, tmpColor.Blue));
		//panelColor->SetCompositeEnabled(false);
	    //Adds a Panel to the Form
		pPopup->AddControl(*panelColor);



		   // Creates a ColorPicker.
	    // Creates a Slider.
		sliderR = new Slider();
		sliderR->Construct(Rectangle(dx, 05, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
		sliderR->SetValue(tmpColor.Red);
		sliderR->AddAdjustmentEventListener(*this);
		pPopup->AddControl(*sliderR);

		sliderG = new Slider();
		sliderG->Construct(Rectangle(dx, 05+sliderHeight, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
		sliderG->SetValue(tmpColor.Green);
		sliderG->AddAdjustmentEventListener(*this);
		pPopup->AddControl(*sliderG);

		sliderB = new Slider();
		sliderB->Construct(Rectangle(dx, 05+2*sliderHeight, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
		sliderB->SetValue(tmpColor.Blue);
		sliderB->AddAdjustmentEventListener(*this);
		pPopup->AddControl(*sliderB);


	    pPopup->SetShowState(true);
	    pPopup->Show();


}

void TizenColorOptionView::OnStateChanged(Tizen::Ui::Controls::TableViewItemStatus status){
	CreateColorPopup();
}

void TizenColorOptionView::OnActionPerformed(const Control& source, int actionId)
{
	switch(actionId){
		case ID_BUTTON_OK :
			_onAccept();
			pPopup->SetShowState(false);
			myForm->SendUserEvent( 1,NULL);

			break;
		case ID_BUTTON_CANCEL :
			pPopup->SetShowState(false);
			break;
	}

}

void TizenColorOptionView::_createItem() {
	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());

}

void TizenColorOptionView::_onAccept() const {
	//myColor = tmpColor;
	((ZLColorOptionEntry&)*myOption).onAccept(tmpColor);
}


TableViewItem* TizenColorOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {


	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	AppLog("DialogForm::OnUserEventReceivedN");
	myForm = pFrame->GetCurrentForm();

	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, defaultItemHeight), style);

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, defaultItemHeight), myCaption);
	pLabel->SetTextConfig(30.0f, LABEL_TEXT_STYLE_NORMAL);
	pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	pItem->AddControl(pLabel);

	myColor = ((ZLColorOptionEntry&)*myOption).color();
	Label* pColorLabel = new Label();
	pColorLabel->Construct(Rectangle(420, 40, 120, 50), L"");
	pColorLabel->SetTextConfig(30.0f, LABEL_TEXT_STYLE_NORMAL);
	pColorLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pColorLabel->SetBackgroundColor(Color(myColor.Red,myColor.Green,myColor.Blue));

	pItem->AddControl(pColorLabel);

	return pItem;
}
