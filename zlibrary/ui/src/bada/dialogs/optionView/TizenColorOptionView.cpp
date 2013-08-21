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
	myColor = ZLColor(redSlider->GetValue(),greenSlider->GetValue(),blueSlider->GetValue());
	colorPanel->SetBackgroundColor(Tizen::Graphics::Color(myColor.Red,myColor.Green, myColor.Blue));
	colorPanel->Invalidate(false);

}


void TizenColorOptionView::CreateColorPopup(void){
	int PopupHeight = 760;
	int sliderWidth = 410;
	int sliderHeight = 150;
	int dx = 180;

	pPopup = new Popup();
	pPopup->Construct(true, Dimension(600,PopupHeight));
	pPopup->SetTitleText(L"Select color");

	Button* pCreateButton = new Button();
	pCreateButton->Construct(Rectangle(50, PopupHeight - 180, 200, 70), L"OK");
	pPopup->AddControl(*pCreateButton);
	pCreateButton->SetActionId(ID_BUTTON_OK);
	pCreateButton->AddActionEventListener(*this);


	Button* pCancelButton = new Button();
	pCancelButton->Construct(Rectangle(300, PopupHeight - 180, 200, 70), L"Cancel");
	pPopup->AddControl(*pCancelButton);
	pCancelButton->SetActionId(ID_BUTTON_CANCEL);
	pCancelButton->AddActionEventListener(*this);

	colorPanel = new Panel();
	colorPanel->Construct(Rectangle(10, 15, dx-10, 3*sliderHeight-20));
	colorPanel->SetBackgroundColor(Tizen::Graphics::Color(myColor.Red,myColor.Green, myColor.Blue));
	//panelColor->SetCompositeEnabled(false);
    //Adds a Panel to the Form
	pPopup->AddControl(*colorPanel);


	redSlider = new Slider();
	redSlider->Construct(Rectangle(dx, 05, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
	redSlider->SetValue(myColor.Red);
	redSlider->AddAdjustmentEventListener(*this);
	pPopup->AddControl(*redSlider);

	greenSlider = new Slider();
	greenSlider->Construct(Rectangle(dx, 05+sliderHeight, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
	greenSlider->SetValue(myColor.Green);
	greenSlider->AddAdjustmentEventListener(*this);
	pPopup->AddControl(*greenSlider);

	blueSlider = new Slider();
	blueSlider->Construct(Rectangle(dx, 05+2*sliderHeight, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
	blueSlider->SetValue(myColor.Blue);
	blueSlider->AddAdjustmentEventListener(*this);
	pPopup->AddControl(*blueSlider);


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
			myColor = ((ZLColorOptionEntry&)*myOption).color();
			pPopup->SetShowState(false);
			break;
	}

}

void TizenColorOptionView::_createItem() {
	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());

}

void TizenColorOptionView::_onAccept() const {
	((ZLColorOptionEntry&)*myOption).onAccept(myColor);
}


TableViewItem* TizenColorOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {


	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	myForm = pFrame->GetCurrentForm();

	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, defaultItemHeight), style);

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, defaultItemHeight), myCaption);
	pLabel->SetTextConfig(35.0f, LABEL_TEXT_STYLE_NORMAL);
	pLabel->SetTextColor(Color::GetColor(COLOR_ID_GREY));
	pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	pItem->AddControl(pLabel);

	myColor = ((ZLColorOptionEntry&)*myOption).color();
	Label* pColorLabel = new Label();
	pColorLabel->Construct(Rectangle(520, 20, 120, 50), L"");
	pColorLabel->SetTextConfig(30.0f, LABEL_TEXT_STYLE_NORMAL);
	pColorLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pColorLabel->SetBackgroundColor(Color(myColor.Red,myColor.Green,myColor.Blue));

	pItem->AddControl(pColorLabel);

	return pItem;
}
