/*
 * DialogForm.cpp
 *
 *  Created on: 24.11.2011
 *      Author: Alex
 */

#include "DialogForm.h"
#include "optionView/ZLbadaOptionView.h"
#include <FIo.h>
#include <FMedia.h>
#include <FGrpColor.h>

#include "ZLbadaOptionsDialog.h"
//#include "badaForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Content;
using namespace Tizen::Graphics;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Media;

bool DialogForm::Initialize(const char *title, bool __showApplyButton)
{
	showApplyButton = __showApplyButton;
	AppLog("DialogForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|

	if (showApplyButton) {
//	if (true) {
		AppLog("showApplyButton true");
		Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_0|FORM_STYLE_SOFTKEY_1);
	//	Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_0|FORM_STYLE_SOFTKEY_1|FORM_STYLE_OPTIONKEY);
		AddSoftkeyActionListener(SOFTKEY_0, *this);
		SetSoftkeyActionId(SOFTKEY_0, ID_ACT_UPDATE);
		SetSoftkeyText(SOFTKEY_0, L"Apply");
	}
	else
		Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_1);

	SetTitleText(String(title));

	AddSoftkeyActionListener(SOFTKEY_1, *this);
	SetSoftkeyActionId(SOFTKEY_1, ID_ACT_CLOSE);
	SetSoftkeyText(SOFTKEY_1, L"Back");

	return true;
}

DialogForm::DialogForm() : myMenuView(null),__pOptionMenu(null) {
	// TODO Auto-generated constructor stub
	AppLog("DialogForm::DialogForm()");
}

DialogForm::~DialogForm() {
	// TODO Auto-generated destructor stub
	AppLog("delete __badaOptionsDialog;...");
	__badaOptionsDialog = 0;
	AppLog("delete buttonBmp;...");
	delete buttonBmp;
	delete buttonBmp2;
	delete arrowDownBmp;
	AppLog("delete __pCustomListItemFormat...");
	delete __pComboViewListItemFormat;
	delete __pSpinViewListItemFormat;
	delete __pStringViewListItemFormat;
	delete __pBooleanListItemFormat;
	delete __pCustomListItemFormat2;
	delete __pColorListItemFormat;
	delete __pImageViewListItemFormat;
	delete __pButtonViewListItemFormat;
	delete __pStaticTextListItemFormat;
//	__pCustomList->RemoveGroupedItemEventListener(*this);
	AppLog("delete __pCustomList");
//	delete __pCustomList;
	if (__pOptionMenu) delete __pOptionMenu;
	AppLog("DialogForm::~DialogForm()");
}

void DialogForm::ShowOptionMenu(void) {
    __pOptionMenu->SetShowState(true);
    __pOptionMenu->Show();
}

void DialogForm::HideOptionMenu(void) {
    __pOptionMenu->SetShowState(false);
    Draw();
    Show();
}

void DialogForm::setMenuView(MenuView* view) {
	AppLog("DialogForm::setMenuView");
	myMenuView = view;
	int actionsCount = myMenuView->myActions.size();

	AppLog("DialogForm::setMenuView %d",actionsCount);
	if (actionsCount>2) {
		if (showApplyButton)		{
			this->SetFormStyle(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_0|FORM_STYLE_SOFTKEY_1|FORM_STYLE_OPTIONKEY);
			__pOptionMenu = new OptionMenu();
			__pOptionMenu->Construct();
			SetOptionkeyActionId(ID_OPTIONKEY);
			AddOptionkeyActionListener(*this);
		}

		else
			this->SetFormStyle(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_1);

	}
	updateMenu();

}

void DialogForm::updateMenu(){
	int actionsCount = myMenuView->myActions.size();
	AppLog("actionsCount %d", actionsCount);
	actionsCount =0;
	if (__pOptionMenu != null) {
		int itemsCount = __pOptionMenu->GetItemCount();
		for (int i= 0; i<itemsCount; i++) __pOptionMenu->RemoveItemAt(0);
	}

	for (int i = 1; i<myMenuView->myActions.size();i++){
		shared_ptr<ZLRunnableWithKey> a = myMenuView->myActions[i];
		if (a->makesSense()) { AppLog("makesSense true %d",actionsCount);
			std::string text = a->text(ZLResource::resource("networkView")["bookNode"]);
			if (actionsCount == 0) SetSoftkeyText(SOFTKEY_0, text.c_str());
			else
				if (__pOptionMenu != null) __pOptionMenu->AddItem(text.c_str(),ID_OPTIONMENU_ITEM0+i);
			actionsCount++;
		}

	}
}

result DialogForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppLog("DialogForm::OnInitializing");

	   // Creates CustomList
	Rectangle formRect = GetClientAreaBounds();
	Image img;
	// = new Tizen::Media::Image();
    r = img.Construct();
	buttonBmp = img.DecodeN("/Res/icons/button-220x50.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	buttonBmp2 = img.DecodeN("/Res/icons/button-220x50s.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	arrowDownBmp = img.DecodeN("/Res/icons/arrow_down.png", BITMAP_PIXEL_FORMAT_ARGB8888);
	AppLog("pImage->DecodeN");
    __pCustomList = new GroupedList();

	GroupCount = 0;
	//__pCustomList->Construct(Rectangle(0, 0, 480, 800), CUSTOM_LIST_STYLE_NORMAL);
	__pCustomList->Construct(Rectangle(0, 0, formRect.width, formRect.height), CUSTOM_LIST_STYLE_MARK, false);
//	__pCustomList->Construct(Rectangle(0, 0, formRect.width, formRect.height), CUSTOM_LIST_STYLE_MARK_WITH_DIVIDER);
	//__pCustomList->AddCustomItemEventListener(*this);
    __pCustomList->SetBackgroundColor(Color(41,41,41));
	__pCustomList->AddGroupedItemEventListener(*this);
	  AddControl(*__pCustomList);

// ----------------   Creates an item format of the CustomList -------------------

//---------------------- __pSpinViewListItemFormat -------------------------------
	  __pSpinViewListItemFormat = new CustomListItemFormat();
	  __pSpinViewListItemFormat->Construct();

	  __pSpinViewListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(15, 25, 400, 80), 30,Color::GetColor(COLOR_ID_GREY), Color::GetColor(COLOR_ID_GREY));
	  __pSpinViewListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(415, 25, 400, 80), 30);
	  __pSpinViewListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(10, 5, 70, 90));
	  __pSpinViewListItemFormat->AddElement(ID_LIST_CHECKBOX, Tizen::Graphics::Rectangle(420, 15, 50, 50));

//---------------------- __pComboViewListItemFormat --------------------------------

	  __pComboViewListItemFormat = new CustomListItemFormat();
	  __pComboViewListItemFormat->Construct();

	  __pComboViewListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(10, 10, 400, 80), 25, Color::GetColor(COLOR_ID_GREY), Color::GetColor(COLOR_ID_GREY));
	  __pComboViewListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(10, 50, 400, 80), 28);
	  __pComboViewListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(10, 5, 70, 90));
	  __pComboViewListItemFormat->AddElement(ID_LIST_CHECKBOX, Tizen::Graphics::Rectangle(420, 25, 36, 36));

//---------------------- __pStringViewListItemFormat --------------------------------

	  __pStringViewListItemFormat = new CustomListItemFormat();
	  __pStringViewListItemFormat->Construct();

	  __pStringViewListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(15, 10, 400, 80), 25, Color::GetColor(COLOR_ID_GREY), Color::GetColor(COLOR_ID_GREY));
	  __pStringViewListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(30, 45, 400, 78), 25);
	  __pStringViewListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(10, 5, 70, 90));
	  __pStringViewListItemFormat->AddElement(ID_LIST_CHECKBOX, Tizen::Graphics::Rectangle(420, 15, 50, 50));



//---------------------- __pStaticTextListItemFormat --------------------------------

    __pStaticTextListItemFormat = new CustomListItemFormat();
    __pStaticTextListItemFormat->Construct();

    __pStaticTextListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(90, 25, 300, 52));
    __pStaticTextListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(90, 15, 400, 80), 55, Color::GetColor(COLOR_ID_BLUE), Color::GetColor(COLOR_ID_BLUE));
    __pStaticTextListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(90, 30, 400, 80), 30, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLACK));
    __pStaticTextListItemFormat->AddElement(ID_LIST_CUSTOM, Tizen::Graphics::Rectangle(0, 0, 480, 1300));


//---------------------- __pBooleanListItemFormat --------------------------------

		// Creates an item format of the CustomList
	__pBooleanListItemFormat = new CustomListItemFormat();
	__pBooleanListItemFormat->Construct();

	__pBooleanListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(15, 25, 400, 80), 28);//, Color::COLOR_GREY, Color::COLOR_GREY);
	__pBooleanListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(20, 55, 400, 80), 20);
	__pBooleanListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(10, 5, 70, 90));
	__pBooleanListItemFormat->AddElement(ID_LIST_CHECKBOX, Tizen::Graphics::Rectangle(420, 20, 50, 50));
	__pBooleanListItemFormat->SetElementEventEnabled(ID_LIST_CHECKBOX, true);


//---------------------- __pCustomListItemFormat2 --------------------------------

	__pCustomListItemFormat2 = new CustomListItemFormat();
	__pCustomListItemFormat2->Construct();

	__pCustomListItemFormat2->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(90, 10, 300, 80), 25, Color::GetColor(COLOR_ID_GREY), Color::GetColor(COLOR_ID_GREY));
	__pCustomListItemFormat2->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(90, 55, 300, 80), 20);
	__pCustomListItemFormat2->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(10, 5, 70, 90));
	__pCustomListItemFormat2->AddElement(ID_LIST_CHECKBOX, Tizen::Graphics::Rectangle(420, 15, 50, 50));
//	__pCustomListItemFormat2->SetElementEventEnabled(ID_LIST_CHECKBOX, true);


//---------------------- __pColorListItemFormat --------------------------------

	__pColorListItemFormat = new CustomListItemFormat();
	__pColorListItemFormat->Construct();

	__pColorListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(15, 25, 300, 80), 30, Color::GetColor(COLOR_ID_GREY), Color::GetColor(COLOR_ID_GREY));
	__pColorListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(105, 55, 300, 80), 30);
	__pColorListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(15, 45, 80, 40));
	__pColorListItemFormat->AddElement(ID_LIST_COLOR, Tizen::Graphics::Rectangle(370, 20, 100, 45));
//	__pColorListItemFormat->SetElementEventEnabled(ID_LIST_TEXT_TITLE, true);
//	__pColorListItemFormat->SetElementEventEnabled(ID_LIST_TEXT_SUBTITLE, true);
//  __pColorListItemFormat->SetElementEventEnabled(ID_LIST_CHECKBOX, true);


//---------------------- __pImageViewListItemFormat --------------------------------

	__pImageViewListItemFormat = new CustomListItemFormat();
	__pImageViewListItemFormat->Construct();

	__pImageViewListItemFormat->AddElement(ID_LIST_BACKGROUND, Tizen::Graphics::Rectangle(0, 0, 480, 330));
//	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(10, 15, 200, 300));
	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(120, 15, 200, 300));
//	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP1, Tizen::Graphics::Rectangle(240, 25, 220, 52));
//	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP2, Tizen::Graphics::Rectangle(240, 100, 220, 52));
//	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP3, Tizen::Graphics::Rectangle(240, 175, 220, 52));
//	__pImageViewListItemFormat->AddElement(ID_LIST_BITMAP4, Tizen::Graphics::Rectangle(240, 250, 220, 52));

	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BACKGROUND, true);
	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP, true);
//	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP1, true);
//	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP2, true);
//	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP3, true);
//	__pImageViewListItemFormat->SetElementEventEnabled(ID_LIST_BITMAP4, true);


//---------------------- __pButtonViewListItemFormat --------------------------------

	  __pButtonViewListItemFormat = new CustomListItemFormat();
	  __pButtonViewListItemFormat->Construct();

	//  __pButtonViewListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(90, 5, 300, 52));
	  __pButtonViewListItemFormat->AddElement(ID_LIST_BITMAP, Tizen::Graphics::Rectangle(290, 5, 150, 52));
	  __pButtonViewListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(10, 12, 250, 80), 30, Color::GetColor(COLOR_ID_WHITE), Color::GetColor(COLOR_ID_BLUE));
	  __pButtonViewListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(300, 12, 180, 50), 30, Color::GetColor(COLOR_ID_BLACK), Color::GetColor(COLOR_ID_BLUE));
	  __pButtonViewListItemFormat->AddElement(ID_LIST_CHECKBOX, Tizen::Graphics::Rectangle(420, 15, 50, 50));


	return r;
}


result  DialogForm::AddTab(const char *title){
	AppLog("DialogForm::AddTab %s", title);
	result r = E_SUCCESS;

    __pCustomList->AddGroup(String(""), null);
    GroupCount++;

}

result DialogForm::OnTerminating(void)
{
	result r = E_SUCCESS;
	return r;
}



void DialogForm::SetPreviousForm(Tizen::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}


void DialogForm::OnActionPerformed(const Tizen::Ui::Control & source, int actionId)
{
	AppLog("DialogForm::OnActionPerformed id=%d",actionId);
	switch(actionId)
	{
    case ID_OPTIONKEY:
    	AppLog("ShowOptionMenu()");
        ShowOptionMenu();
        break;

	case ID_ACT_CLOSE:
		{
			AppLog("Close button is clicked!");
			__badaOptionsDialog->accept();
			Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

			pPreviousForm->SendUserEvent(0, null);
		}
		break;

	case ID_ACT_UPDATE:
		{
			AppLog("UpdateContent");
			//((shared_ptr<ZLbadaOptionsDialog>)__badaOptionsDialog)->apply();
			/*if (showApplyButton) {
				__badaOptionsDialog->accept();
				pPreviousForm->SendUserEvent(2, null);
			}
			else
				*/
			{
				for (int i = 1; i<myMenuView->myActions.size();i++){
					shared_ptr<ZLRunnableWithKey> a = myMenuView->myActions[i];
					if (a->makesSense()) {
							runAction(a);
							break;
						}
					}
			}
		//	UpdateContent();

		}
		break;
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("BooleanOptionView::ID_BUTTON_CHECKED");
	    	//onStateChanged(true);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("BooleanOptionView::ID_BUTTON_UNCHECKED");
	    	//onStateChanged(false);
	        // Todo:
	        break;

	/*case ID_ACT_DELETE:
		{
			DeleteContent();
			break;
		}*/
	default:
		AppLog("default");
		int menuActionId = actionId - ID_OPTIONMENU_ITEM0;
		if ((menuActionId>=0)&&(menuActionId<12)) {
			shared_ptr<ZLRunnableWithKey> a = myMenuView->myActions[menuActionId];
			runAction(a);
		}
		break;
	}
}

void DialogForm::runAction(shared_ptr<ZLRunnableWithKey> action){
	std::string text = action->key().Name;
	AppLog("OnActionPerformed= %s", text.c_str());
	action->run();
	if ((text=="readDemo")||(text=="read"))
		{
			 pPreviousForm->SendUserEvent(2, null);
		}
	else
		updateMenu();
}

void DialogForm::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	AppLog("DialogForm::OnUserEventReceivedN");
	//Form* prevForm = pFrame->GetCurrentForm();
	switch(requestId)
	{
	case 0:
		{

			pFrame->SetCurrentForm(*this);
			DeleteOptionPopup();
			//pFrame->RequestRedraw();
			Draw();
			Show();
		//	if (prevForm != null)		{
		//		pFrame->RemoveControl(*prevForm);
		//		}

		}
		break;
	case 1:
		{
			AppLog("badaForm::а теперь Акшен открываем файл");
			pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
			//myHolder.doAction(ActionIdList[2]);

		}
		break;
	default:
		break;
	}

}

void DialogForm::DeleteOptionPopup(){
	//DeleteCreateCategoryPopup();
	if(__pSpinOptionPopup)
	{
		delete __pSpinOptionPopup;
		__pSpinOptionPopup = null;
	}

	if(__pComboOptionPopup)
	{
		delete __pComboOptionPopup;
		__pComboOptionPopup = null;
	}

	if(__pColorComboOptionPopup)
	{
		delete __pColorComboOptionPopup;
		__pColorComboOptionPopup = null;
	}
}

void DialogForm::ShowColorComboOptionPopup(ColorOptionView* pColorOptionView){
	//DeleteCreateCategoryPopup();

	__pColorComboOptionPopup = new ColorComboOptionPopup();
	//AddControl(*__pComboOptionPopup);
	__pColorComboOptionPopup->Construct(this, pColorOptionView);
	__pColorComboOptionPopup->Show();
}

void DialogForm::ShowSpinOptionPopup(SpinOptionView* pSpinOptionView){


	__pComboOptionPopup = new ComboOptionPopup();
	__pComboOptionPopup->Construct(this, pSpinOptionView);
	__pComboOptionPopup->Show();

}


void DialogForm::ShowComboOptionPopup(ComboOptionView* pComboOptionView){
	//DeleteCreateCategoryPopup();

	__pComboOptionPopup = new ComboOptionPopup();
	//AddControl(*__pComboOptionPopup);
	__pComboOptionPopup->Construct(this, pComboOptionView);
	__pComboOptionPopup->Show();
}

//void DialogForm::OnItemStateChanged (const Tizen::Ui::Control &source, int index, int itemId, Tizen::Ui::ItemStatus status)
void  DialogForm::OnItemStateChanged (const Tizen::Ui::Control &source, int groupIndex, int itemIndex, int itemId, Tizen::Ui::ItemStatus status)
{
	AppLog("DialogForm::OnItemStateChanged 1");
	//OptionListItem* pItem = (OptionListItem*)__pCustomList->GetItemAt(index);
	OptionListItem* pItem = (OptionListItem*)__pCustomList->GetItemAt(groupIndex, itemIndex);
	pItem->OnActionPerformed(ID_BUTTON_CHECKED);
}

//void DialogForm::OnItemStateChanged(const Tizen::Ui::Control& source, int index, int itemId, int elementId, Tizen::Ui::ItemStatus status)
void  DialogForm::OnItemStateChanged (const Tizen::Ui::Control &source, int groupIndex, int itemIndex, int itemId, int elementId, Tizen::Ui::ItemStatus status)
{
	AppLog("DialogForm::OnItemStateChanged 2");
	AppLog("groupIndex=%d, itemIndex=%d", groupIndex, itemIndex);
	OptionListItem* pItem = (OptionListItem*)__pCustomList->GetItemAt(groupIndex, itemIndex);
	pItem->OnActionPerformed(elementId);

}


OptionListItem::OptionListItem(ZLbadaOptionView* badaOptionView) : CustomListItem(), mybadaOptionView(badaOptionView) {

	}

void OptionListItem::OnActionPerformed(int actionId){
	AppLog(" OptionListItem::OnActionPerformed");
	mybadaOptionView->OnActionPerformed(actionId);
	}

