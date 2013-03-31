#include <cctype>


#include <ZLStringUtil.h>
#include <ZLDialogManager.h>
//#include "../util/ZLQtKeyUtil.h"

#include "ZLbadaOptionView.h"
#include "ZLOptionEntry.h"
#include "../ZLbadaDialogContent.h"
#include "../DialogForm.h"
#include "../../image/ZLbadaImageManager.h"

#include <FIo.h>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Content;
using namespace Tizen::Graphics;
using namespace Tizen::Base::Runtime;



void StringOptionView::_createItem() {
	AppLog("StringOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());

	pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pStringViewListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));

    myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);

	groupIndex = myTab->form()->GroupCount-1;
	itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
	AppLog("groupIndex =%d itemIndex=%d",groupIndex,itemIndex);
	reset();
}


void StringOptionView::_onAccept() const {
	AppLog("StringOptionView::_onAccept");
	((ZLStringOptionEntry&)*myOption).onAccept(myValue);
}

void StringOptionView::reset() {
	myValue = ((ZLStringOptionEntry&)*myOption).initialValue();
	AppLog("StringOptionView::reset initialValue = %s",myValue.c_str());
	//const char *text = (((ZLStringOptionEntry&)*myOption).initialValue()).c_str();

	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String(myValue.c_str()));
}

void StringOptionView::OnActionPerformed( int actionId)
{
	AppLog("StringOptionView::OnActionPerformed %d",actionId);
	ShowKeypad();
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("StringOptionView::ID_BUTTON_CHECKED");
	    	//myTab->form()->ShowComboOptionPopup(this);
	    	//onStateChanged(true);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("StringOptionView::ID_BUTTON_UNCHECKED");
	    	//onStateChanged(false);
	        // Todo:
	        break;
    default:
        break;
    }
}
//void StringOptionView::onValueEdited(const QString &value) {
//	ZLStringOptionEntry &o = (ZLStringOptionEntry&)*myOption;
//	if (o.useOnValueEdited()) {
//		o.onValueEdited((const char*)value.toUtf8());
//	}
//}

// Implements an ITextEventListener
void StringOptionView::OnTextValueChanged(const Control& source)
{
    // Todo:
	AppLog("OnTextValueChanged");
	CustomListItem* pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pStringViewListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, __pKeypad->GetText());


	myTab->form()->__pCustomList->SetItemAt(groupIndex,itemIndex, *pItem, ID_LIST_ITEM);

	 ByteBuffer* bb = Tizen::Base::Utility::StringUtil:: StringToUtf8N(__pKeypad->GetText());
	 myValue = std::string((char *)bb->GetPointer());
	 AppLog( "pKeypad->GetText %s",myValue.c_str());


}

void StringOptionView::OnTextValueChangeCanceled(const Control& source)
{
    // Todo:
	AppLog("OnTextValueChangeCanceled");
}

void StringOptionView::ShowKeypad()
{
	if (!__pKeypad)
	{
		AppLog("new Keypad()");
    __pKeypad = new Keypad();
    __pKeypad->Construct(KEYPAD_STYLE_NORMAL, KEYPAD_MODE_ALPHA);
    __pKeypad->AddTextEventListener(*this);
	}
	__pKeypad->SetText(String(myValue.c_str()));
  //  __pKeypad->SetShowState(true);
    __pKeypad->Show();
}


