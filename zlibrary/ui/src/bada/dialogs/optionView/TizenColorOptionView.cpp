/*
 * TizenColorOptionView.cpp
 *
 *  Created on: Aug 21, 2013
 *      Author: temper8
 */

#include "TizenColorOptionView.h"


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
	  int PopupHeight = 460;
	  int sliderWidth = 310;
	  int sliderHeight = 90;
	  int dx = 150;

	  __pPopup = new Popup();
	  __pPopup->Construct(true, Dimension(465,PopupHeight));
	  __pPopup->SetTitleText(L"Select color");

		Button* pCreateButton = new Button();
		pCreateButton->Construct(Rectangle(20, PopupHeight - 180, 200, 70), L"OK");
		__pPopup->AddControl(*pCreateButton);
		//pCreateButton->SetActionId(ID_BUTTON_CREATE);
		pCreateButton->AddActionEventListener(*this);


		Button* pCancelButton = new Button();
		pCancelButton->Construct(Rectangle(230, PopupHeight - 180, 200, 70), L"Cancel");
		__pPopup->AddControl(*pCancelButton);
		//pCancelButton->SetActionId(ID_BUTTON_CANCEL);
		pCancelButton->AddActionEventListener(*this);

		panelColor = new Panel();
		panelColor->Construct(Rectangle(10, 15, dx-10, 3*sliderHeight-20));
		panelColor->SetBackgroundColor(Tizen::Graphics::Color(tmpColor.Red,tmpColor.Green, tmpColor.Blue));
		//panelColor->SetCompositeEnabled(false);
	    //Adds a Panel to the Form
		__pPopup->AddControl(*panelColor);



		   // Creates a ColorPicker.
	    // Creates a Slider.
		sliderR = new Slider();
		sliderR->Construct(Rectangle(dx, 05, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
		sliderR->SetValue(tmpColor.Red);
		sliderR->AddAdjustmentEventListener(*this);
		__pPopup->AddControl(*sliderR);

		sliderG = new Slider();
		sliderG->Construct(Rectangle(dx, 05+sliderHeight, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
		sliderG->SetValue(tmpColor.Green);
		sliderG->AddAdjustmentEventListener(*this);
		__pPopup->AddControl(*sliderG);

		sliderB = new Slider();
		sliderB->Construct(Rectangle(dx, 05+2*sliderHeight, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
		sliderB->SetValue(tmpColor.Blue);
		sliderB->AddAdjustmentEventListener(*this);
		__pPopup->AddControl(*sliderB);


	    __pPopup->SetShowState(true);
	    __pPopup->Show();


}

void TizenColorOptionView::OnStateChanged(Tizen::Ui::Controls::TableViewItemStatus status){
	CreateColorPopup();
	/*   __pPopup = new Popup();
	    __pPopup->Construct(true, Dimension(600,800));
	    __pPopup->SetTitleText(L"Popup Sample");
	    // Creates an instance of Button to close the popup.
	     Button* pCloseButton = new Button();
	     pCloseButton->Construct(Rectangle(10, 10, 250, 80), L"Close Popup");
	   //  pCloseButton->SetActionId(ID_BUTTON_CLOSE_POPUP);
	     pCloseButton->AddActionEventListener(*this);

	     // Adds the button to the popup
	     __pPopup->AddControl(pCloseButton);

	     // Creates an instance of Button to open the popup.
	  //   Button* pOpenButton = new Button();
	  //   pOpenButton->Construct(Rectangle(10, 10, 250, 60), L"Open Popup");
	   //  pOpenButton->SetActionId(ID_BUTTON_OPEN_POPUP);
	   //  pOpenButton->AddActionEventListener(*this);

	     // Adds the button to the form
	    // AddControl(pOpenButton);

	     __pPopup->SetShowState(true);
	     __pPopup->Show();
	     */
}

void TizenColorOptionView::OnActionPerformed(const Control& source, int actionId)
{
	__pPopup->SetShowState(false);
}

void TizenColorOptionView::_createItem() {
	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());

}

void TizenColorOptionView::_onAccept() const { }


TableViewItem* TizenColorOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {

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
