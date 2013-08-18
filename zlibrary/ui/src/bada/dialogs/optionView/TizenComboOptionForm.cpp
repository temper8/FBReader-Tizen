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

TizenComboOptionForm::TizenComboOptionForm(const std::string &name, ZLComboOptionEntry& comboOption): myName(name), myComboOption(comboOption) {
	// TODO Auto-generated constructor stub
	const std::vector<std::string> &values = myComboOption.values();
	const std::string &initial = myComboOption.initialValue();
	selectedIndex = -1;
	int index = 0;

	for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it, ++index) {
		if (*it == initial) {
			selectedIndex = index;
		}
	}
}

TizenComboOptionForm::~TizenComboOptionForm() {
	// TODO Auto-generated destructor stub
}

void TizenComboOptionForm::Initialize(){
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_HEADER |FORM_STYLE_FOOTER );

	Header* pHeader = GetHeader();
    pHeader->SetTitleText(String(myName.c_str()));

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
	const std::vector<std::string> &values = myComboOption.values();
	SimpleItem * pItem = new SimpleItem();
    pItem->Construct(Dimension(itemWidth,112), LIST_ANNEX_STYLE_RADIO);
    String text((values[index]).c_str());
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
    return myComboOption.values().size();
}


