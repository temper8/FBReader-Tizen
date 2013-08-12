/*
 * TizenBooleanOptionView.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: temper8
 */

#include "TizenBooleanOptionView.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

void TizenBooleanOptionView::_createItem() {
//	std::string myText = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
//	const char *text = myText.c_str();
	//myCaption = ZLOptionView::name();
	 myCaption.Format(40, L"%s", ZLOptionView::name().c_str());
}

void TizenBooleanOptionView::_onAccept() const {

}


TableViewItem* TizenBooleanOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_ONOFF_SLIDING;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, defaultItemHeight), style);

	//String text;// = L"TizenBooleanOptionView";
	//text.Format(30, L"%s", myCaption.c_str());

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, defaultItemHeight), myCaption);
	pLabel->SetTextConfig(30.0f, LABEL_TEXT_STYLE_NORMAL);
	pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	pItem->AddControl(pLabel);

	return pItem;
}
