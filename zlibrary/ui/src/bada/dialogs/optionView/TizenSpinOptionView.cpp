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
	 myCaption.Format(40, L"%s", ZLOptionView::name().c_str());
}

void TizenSpinOptionView::_onAccept() const {

}


TableViewItem* TizenSpinOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, 150), style);

	Slider* pSlider = new (std::nothrow) Slider();

	pSlider->Construct(Rectangle(5, 00, itemWidth-10, 150), BACKGROUND_STYLE_NONE, true, 0, 15);
	pSlider->SetValue(5);
	pSlider->SetTitleText(myCaption);

	pItem->AddControl(pSlider);

	pItem->SetIndividualSelectionEnabled(pSlider, true);

	return pItem;
}
