/*
 * TizenSpinOptionView.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: temper8
 */

#include "TizenSpinOptionView.h"


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

void TizenSpinOptionView::_createItem() {
//	std::string myText = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
//	const char *text = myText.c_str();
//	 myCaption = ZLOptionView::name()+ ": 123";
	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
}

void TizenSpinOptionView::_onAccept() const {

}


TableViewItem* TizenSpinOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, 2*defaultItemHeight), style);

	//String text;
	//text.Format(30, L"t=%s", myCaption.c_str());

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, defaultItemHeight), myCaption);
    pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pItem->AddControl(pLabel);

	Slider* __pSlider = new (std::nothrow) Slider();
	Label*	pLabelMin = new (std::nothrow) Label();
	pLabelMin->Construct(FloatRectangle(20.0f, 80.0f, 45.0f, 45.0f), L"12");

	Label*	pLabelMax = new (std::nothrow) Label();
	pLabelMax->Construct(FloatRectangle(650.0f, 80.0f, 45.0f, 45.0f), L"123");

	__pSlider->Construct(Rectangle(0, 50, itemWidth-110, 150), BACKGROUND_STYLE_NONE, true, 0, 15);
	__pSlider->SetValue(5);
	__pSlider->SetName(L"slasdfsd");
	pItem->AddControl(__pSlider);
//	pItem->AddControl(pLabelMin);
//	pItem->AddControl(pLabelMax);

	pItem->SetIndividualSelectionEnabled(__pSlider, true);
//	pItem->SetIndividualSelectionEnabled(pLabelMin, true);
//	pItem->SetIndividualSelectionEnabled(pLabelMax, true);


	return pItem;
}
