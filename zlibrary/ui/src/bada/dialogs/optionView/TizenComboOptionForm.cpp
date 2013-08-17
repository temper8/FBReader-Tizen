/*
 * TizenComboOptionForm.cpp
 *
 *  Created on: Aug 17, 2013
 *      Author: Alex
 */

#include "TizenComboOptionForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

TizenComboOptionForm::TizenComboOptionForm() {
	// TODO Auto-generated constructor stub

}

TizenComboOptionForm::~TizenComboOptionForm() {
	// TODO Auto-generated destructor stub
}

void TizenComboOptionForm::Initialize(){
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_HEADER |FORM_STYLE_FOOTER );

	Header* pHeader = GetHeader();
    pHeader->SetTitleText(String("title"));

	Footer* pFooter = GetFooter();
//	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);
	pFooter->SetBackButton();
//	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);

    // Creates an instance of ListView
    pListView = new ListView();
    pListView->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height), true, false);
    pListView->SetItemProvider(*this);
    pListView->AddListViewItemEventListener(*this);

    // Adds the list view to the form
    AddControl(pListView);



}

void TizenComboOptionForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source) {
	AppLog("Close button is clicked!");
//	__badaOptionsDialog->accept();
//	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	pPreviousForm->SendUserEvent(0, null);
}

// IListViewItemEventListener implementation
void TizenComboOptionForm::OnListViewItemStateChanged(ListView &listView, int index, int elementId, ListItemStatus status) {

}

void TizenComboOptionForm::OnListViewContextItemStateChanged(ListView &listView, int index, int elementId, ListContextItemStatus state) {

}

void TizenComboOptionForm::OnListViewItemSwept(ListView &listView, int index, SweepDirection direction) {
    // ....
}

// IListViewItemProvider implementation
ListItemBase* TizenComboOptionForm::CreateItem(int index, int itemWidth) {

	SimpleItem * pItem = new SimpleItem();
    pItem->Construct(Dimension(itemWidth,112), LIST_ANNEX_STYLE_RADIO);
    pItem->SetElement("testtt");

    return pItem;
}

bool TizenComboOptionForm::DeleteItem(int index, ListItemBase* pItem, int itemWidth) {
    delete pItem;
    pItem = null;
    return true;
}

int TizenComboOptionForm::GetItemCount(void)
{
    return 15;
}


