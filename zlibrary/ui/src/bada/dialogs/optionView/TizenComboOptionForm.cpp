/*
 * TizenComboOptionForm.cpp
 *
 *  Created on: Aug 17, 2013
 *      Author: Alex
 */

#include "TizenComboOptionForm.h"
#include "TizenComboOptionView.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

//TizenComboOptionForm::TizenComboOptionForm(const std::string &name, ZLComboOptionEntry& comboOption): myName(name), myComboOption(comboOption) {
TizenComboOptionForm::TizenComboOptionForm(): myView(NULL) {
// TODO Auto-generated constructor stub
	//myView->

}

TizenComboOptionForm::~TizenComboOptionForm() {
	// TODO Auto-generated destructor stub
}

void TizenComboOptionForm::Initialize(TizenComboOptionView* view){
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_HEADER |FORM_STYLE_FOOTER );
	myView = view;
	selectedIndex = myView->getIndexSelected();
	Header* pHeader = GetHeader();
    pHeader->SetTitleText(String(myView->getName()));

	Footer* pFooter = GetFooter();
	pFooter->SetBackButton();
	SetFormBackEventListener(this);

    // Creates an instance of ListView
    pListView = new ListView();
    pListView->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height), true, false);
    pListView->SetItemProvider(*this);
    pListView->AddListViewItemEventListener(*this);


    // Adds the list view to the form
    AddControl(pListView);

    pListView->UpdateList();
    pListView->SetItemChecked(selectedIndex, true);

}

result TizenComboOptionForm::OnInitializing(void){
 //   pListView->SetItemChecked(selectedItem, true);
 //   pListView->UpdateList();
    return E_SUCCESS;
}

void TizenComboOptionForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source) {
	AppLog("Close button is clicked!");
//	__badaOptionsDialog->accept();
//	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	myView->setIndexSelected(selectedIndex);
	pPreviousForm->SendUserEvent(0, null);
}

// IListViewItemEventListener implementation
void TizenComboOptionForm::OnListViewItemStateChanged(ListView &listView, int index, int elementId, ListItemStatus status) {
    pListView->SetItemChecked(selectedIndex, false);
    pListView->SetItemChecked(index, true);
    selectedIndex = index;
    pListView->UpdateList();
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
    String text(myView->getValue(index));
    pItem->SetElement(text);
    pItem->SetDescriptionText("descr");
    return pItem;
}

bool TizenComboOptionForm::DeleteItem(int index, ListItemBase* pItem, int itemWidth) {
    delete pItem;
    pItem = null;
    return true;
}

int TizenComboOptionForm::GetItemCount(void)
{
    return myView->getValuesCount();
}


