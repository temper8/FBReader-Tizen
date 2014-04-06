/*
 * TizenDialogForm.cpp
 *
 *  Created on: Jul 23, 2013
 *      Author: Alex
 */

#include "TizenDialogForm.h"
#include "optionView/ZLTizenOptionView.h"


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

TizenDialogForm::TizenDialogForm(): __pTableView(null) {
	// TODO Auto-generated constructor stub

}

TizenDialogForm::~TizenDialogForm() {
	// TODO Auto-generated destructor stub
}

void TizenDialogForm::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	AppLog("DialogForm::OnUserEventReceivedN");
	Form* prevForm = pFrame->GetCurrentForm();
	switch(requestId)
	{
	case 0:
		{

			pFrame->SetCurrentForm(*this);
			__pTableView->UpdateTableView();
			//pFrame->RequestRedraw();
			Draw();
			Show();
			if (prevForm != null)
			{
				AppLog("prevForm != null");
				pFrame->RemoveControl(*prevForm);
				AppLog("RemoveControl(*prevForm);");
					AppLog("deleteTreeDialog");
			}

		}
		break;
	case 1:
		__pTableView->UpdateTableView();
		break;

	default:
		break;
	}

}

bool TizenDialogForm::Initialize(const char *title, bool __showApplyButton)
{
	showApplyButton = __showApplyButton;
	AppLog("DialogForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_HEADER  );

	Header* pHeader = GetHeader();
    pHeader->SetTitleText(String(title));

//	Footer* pFooter = GetFooter();
//	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);
//	pFooter->SetBackButton();
//	pFooter->AddActionEventListener(*this);

	SetFormBackEventListener(this);

    // Creates an instance of TableView
    __pTableView = new GroupedTableView();
    //__pTableView->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height), true, TABLE_VIEW_SCROLL_BAR_STYLE_FADE_OUT);
    __pTableView->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height), true, TABLE_VIEW_SCROLL_BAR_STYLE_FADE_OUT);

    __pTableView->SetItemProvider(this);
    __pTableView->AddGroupedTableViewItemEventListener(*this);

    // Adds the TableView to the form
    AddControl(__pTableView);

	return true;
}
void TizenDialogForm::Update(){

	__pTableView->UpdateTableView();

	int groupIndex=0;
	for (std::vector<shared_ptr<ZLDialogContent> >::const_iterator it = myTabs.begin(); it != myTabs.end(); ++it, groupIndex++)
	   	for (int i=0; i<(*it)->getViewsCount(); i++) {
	   		ZLTizenOptionView* v =  (ZLTizenOptionView*)(*it)->getView(i);
	   		if (v->isBoolOption()) {
	   			__pTableView->SetItemChecked(groupIndex, i, v->boolOptionState());
	   		}
    	}
}

void TizenDialogForm::SetPreviousForm(Tizen::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}


void TizenDialogForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source){
	AppLog("Close button is clicked!");
	__badaOptionsDialog->accept();
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	pPreviousForm->SendUserEvent(0, null);
}



// IGroupedTableViewItemEventListener implementation
void
TizenDialogForm::OnGroupedTableViewGroupItemStateChanged(GroupedTableView& tableView, int groupIndex, TableViewGroupItem* pItem, TableViewItemStatus status)
{
    if (tableView.IsGroupExpanded(groupIndex))
    {
        tableView.CollapseGroup(groupIndex);
    }
    else
    {
        tableView.ExpandGroup(groupIndex);
    }
}

void
TizenDialogForm::OnGroupedTableViewItemStateChanged(GroupedTableView& tableView, int groupIndex, int itemIndex, TableViewItem* pItem, TableViewItemStatus status)
{
    // ....
	AppLog("StateChanged groupIndex %d, itemIndex %d, status %d ", groupIndex, itemIndex, status);
    shared_ptr<ZLDialogContent>  myTab =  myTabs[groupIndex];
    ZLTizenOptionView* v = (ZLTizenOptionView*)myTab->getView(itemIndex);
    v->OnStateChanged(status);
}

void
TizenDialogForm::OnGroupedTableViewContextItemActivationStateChanged(GroupedTableView& tableView, int groupIndex, int itemIndex, TableViewContextItem* pContextItem, bool activated)
{
    // ....
}


// IGroupedTableViewItemProvider implementation
int
TizenDialogForm::GetGroupCount(void)
{
    return myTabs.size();
}

int
TizenDialogForm::GetItemCount(int groupIndex)
{
	shared_ptr<ZLDialogContent>  myTab =  myTabs[groupIndex];
    return myTab->getViewsCount();
}

int
TizenDialogForm::GetDefaultItemHeight(void)
{
    return 100;
}

int
TizenDialogForm::GetDefaultGroupItemHeight(void)
{
    return 80;
}

TableViewGroupItem*
TizenDialogForm::CreateGroupItem(int groupIndex, int itemWidth)
{
    TableViewGroupItem* pItem = new TableViewGroupItem();
    pItem->Construct(Dimension(itemWidth, GetDefaultGroupItemHeight()));

    String text;
    text.Format(40, L"%s", myTabs[groupIndex]->displayName().c_str());
   // text.Format(30, L"Tab Name %s", myTabs[itemIndex]->displayName().c_str());
    Label* pLabel = new Label();
    pLabel->Construct(Rectangle(0, 0, itemWidth, GetDefaultGroupItemHeight()), text);
    pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);
    pItem->AddControl(pLabel);

    return pItem;
}

bool
TizenDialogForm::DeleteGroupItem(int groupIndex, TableViewGroupItem* pItem)
{
    pItem->Destroy();

    return true;
}

void
TizenDialogForm::UpdateGroupItem(int groupIndex, TableViewGroupItem* pItem)
{
    // ....
}

TableViewItem*
TizenDialogForm::CreateItem(int groupIndex, int itemIndex, int itemWidth)
{
    shared_ptr<ZLDialogContent>  myTab =  myTabs[groupIndex];
    ZLTizenOptionView* v = (ZLTizenOptionView*)myTab->getView(itemIndex);
  /*
    TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
    TableViewItem* pItem = new TableViewItem();

    switch (itemIndex % 6)
    {
    case 0:
        style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
        break;
    case 1:
        style = TABLE_VIEW_ANNEX_STYLE_MARK;
        break;
    case 2:
        style = TABLE_VIEW_ANNEX_STYLE_ONOFF_SLIDING;
        break;
    case 3:
        style = TABLE_VIEW_ANNEX_STYLE_DETAILED;
        break;
    case 4:
        style = TABLE_VIEW_ANNEX_STYLE_RADIO;
        break;
    case 5:
        style = TABLE_VIEW_ANNEX_STYLE_ONOFF_SLIDING_WITH_DIVIDER;
        break;
    default:
        break;
    }
*/
  //  pItem->Construct(Dimension(itemWidth, GetDefaultItemHeight()), style);

    //String text;
    //text.Format(30, L"TableViewItem %d", itemIndex);


 //   pItem->SetContextItem(__pContextItem);

    return v->createTableViewItem(itemWidth, GetDefaultItemHeight());
}

bool
TizenDialogForm::DeleteItem(int groupIndex, int itemIndex, TableViewItem* pItem)
{
    pItem->Destroy();

    return true;
}

void
TizenDialogForm::UpdateItem(int groupIndex, int itemIndex, TableViewItem* pItem)
{
    // ....
}


