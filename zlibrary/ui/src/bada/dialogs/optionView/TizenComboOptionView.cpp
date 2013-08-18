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
//	std::string myText = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
//	const char *text = myText.c_str();
//	 myCaption = ZLOptionView::name()+ ": 123";
	 myCaption.Format(30, L"%s", ZLOptionView::name().c_str());
	 comboValue.Format(30, L"%s", ((ZLComboOptionEntry&)*myOption).initialValue().c_str());
	 //= ((ZLComboOptionEntry&)*myOption).initialValue();
}

void TizenComboOptionView::OnStateChanged(TableViewItemStatus status){
	AppLog("OnStateChanged  status %d ", status);
	if (status  == TABLE_VIEW_ITEM_STATUS_MORE ) {
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		TizenComboOptionForm* pComboForm = new TizenComboOptionForm(ZLOptionView::name(), (ZLComboOptionEntry&)*myOption);

		AppLog("pDialogForm->Initialize()");
		pComboForm->Initialize();//(ZLComboOptionEntry&)*__parentComboOptionView->option(););
		pComboForm->pPreviousForm =pFrame->GetCurrentForm();
		pFrame->AddControl(*pComboForm);
		pFrame->SetCurrentForm(*pComboForm);
		AppLog("r = pFrame->SetCurrentForm(*pDialogForm);");
		pComboForm->Invalidate(false);
	}
}


void TizenComboOptionView::_onAccept() const {

}


TableViewItem* TizenComboOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_DETAILED;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, 2*defaultItemHeight), style);

	//String text;
	//text.Format(30, L"t=%s", myCaption.c_str());

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, defaultItemHeight), myCaption);
    pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pItem->AddControl(pLabel);

	Label*	pLabelValue = new (std::nothrow) Label();
	pLabelValue->Construct(Rectangle(0, 80, itemWidth, defaultItemHeight), comboValue);
	pLabelValue->SetTextColor(Tizen::Graphics::Color::GetColor(COLOR_ID_BLUE) );
	pLabelValue->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
	pItem->AddControl(pLabelValue);
//	pItem->AddControl(pLabelMin);
//	pItem->AddControl(pLabelMax);

//	pItem->SetIndividualSelectionEnabled(__pSlider, true);
//	pItem->SetIndividualSelectionEnabled(pLabelMin, true);
//	pItem->SetIndividualSelectionEnabled(pLabelMax, true);


	return pItem;
}
