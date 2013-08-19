/*
 * TizenComboOptionView.cpp
 *
 *  Created on: Aug 16, 2013
 *      Author: temper8
 */

#include "TizenComboOptionView.h"
#include "TizenComboOptionForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

void TizenComboOptionView::_createItem() {
	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 comboValue.Format(30, L"%s", ((ZLComboOptionEntry&)*myOption).initialValue().c_str());
}

void TizenComboOptionView::OnStateChanged(TableViewItemStatus status){
	AppLog("OnStateChanged  status %d ", status);
	if (status  == TABLE_VIEW_ITEM_STATUS_MORE ) {
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		TizenComboOptionForm* pComboForm = new TizenComboOptionForm();

		pComboForm->Initialize(this);
		pComboForm->pPreviousForm =pFrame->GetCurrentForm();
		pFrame->AddControl(*pComboForm);
		pFrame->SetCurrentForm(*pComboForm);
		pComboForm->Invalidate(false);
	}
}

int TizenComboOptionView::getValuesCount(){
	return ((ZLComboOptionEntry&)*myOption).values().size();
}

const char* TizenComboOptionView::getName(){
	return ZLOptionView::name().c_str();
}

const char* TizenComboOptionView::getValue(int index){
	const std::vector<std::string> &values = ((ZLComboOptionEntry&)*myOption).values();
	return values[index].c_str();
}

void TizenComboOptionView::setIndexSelected(int index){
	const std::vector<std::string> &values = ((ZLComboOptionEntry&)*myOption).values();
	std::string v = values[index];
	((ZLComboOptionEntry&)*myOption).onAccept(v.c_str());
	comboValue.Format(30, L"%s", v.c_str());
}

int TizenComboOptionView::getIndexSelected(){
	const std::vector<std::string> &values = ((ZLComboOptionEntry&)*myOption).values();
	const std::string &initial = ((ZLComboOptionEntry&)*myOption).initialValue();
	int selectedIndex = -1;
	int index = 0;

	for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it, ++index) {
		if (*it == initial) {
			selectedIndex = index;
		}
	}
	return selectedIndex;
}
void TizenComboOptionView::_onAccept() const {

}


TableViewItem* TizenComboOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_DETAILED;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, 2*defaultItemHeight), style);

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, defaultItemHeight), myCaption);
    pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pItem->AddControl(pLabel);

	Label*	pLabelValue = new (std::nothrow) Label();
	pLabelValue->Construct(Rectangle(0, 80, itemWidth, defaultItemHeight), comboValue);
	pLabelValue->SetTextColor(Tizen::Graphics::Color::GetColor(COLOR_ID_BLUE) );
	pLabelValue->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pItem->AddControl(pLabelValue);

//	pItem->SetIndividualSelectionEnabled(pLabelValue, true);


	return pItem;
}
