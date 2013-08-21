/*
 * TestTizenOptionView.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: temper8
 */

#include "TestTizenOptionView.h"


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

void TestTizenOptionView::_createItem() {
	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
}

void TestTizenOptionView::_onAccept() const { }


TableViewItem* TestTizenOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, defaultItemHeight), style);

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, defaultItemHeight), myCaption);

	pItem->AddControl(pLabel);

	return pItem;
}
