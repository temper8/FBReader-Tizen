
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


result ComboOptionView::DrawElement(const Tizen::Graphics::Canvas& canvas, const Tizen::Graphics::Rectangle& rect, Tizen::Ui::Controls::CustomListItemStatus itemStatus)
{
	result r = E_SUCCESS;
	AppLog("DrawElement");
	Tizen::Graphics::Canvas* pCanvas = const_cast<Tizen::Graphics::Canvas*>(&canvas);
	AppLog("pCanvas");
	int d=5;
	Rectangle CircleRect(rect.x+d,rect.y+d,rect.width-2*d ,rect.height-2*d);
	pCanvas->SetLineWidth(2);
	pCanvas->SetForegroundColor(Tizen::Graphics::Color::GetColor(COLOR_ID_GREY));
	if (pCanvas->DrawEllipse(CircleRect) != E_SUCCESS)
		return r;
	int cx = rect.x + rect.width /2;
	int cy = rect.y + rect.height /2;
	int wt = rect.width /6;
	Point point1(cx-wt,cy-wt/2);
	Point point2(cx+wt,cy-wt/2);
	Point point3(cx,cy+wt/2);
	pCanvas->FillTriangle (Tizen::Graphics::Color::GetColor(COLOR_ID_GREY), point1, point2, point3);
	/*
	pCanvas->SetForegroundColor(Tizen::Graphics::Color::COLOR_WHITE);
	if (pCanvas->DrawText(Tizen::Graphics::Point(rect.x+20, rect.y+10), *pEnrichedText) != E_SUCCESS)
		return r;
*/
	return r;
}
void ComboOptionView::_createItem() {
	AppLog("ComboOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());

	pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pComboViewListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
    pItem->SetElement(ID_LIST_CHECKBOX, *myTab->form()->arrowDownBmp, myTab->form()->arrowDownBmp);
  //  pItem->SetElement(ID_LIST_CHECKBOX, *this);

	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);
	groupIndex = myTab->form()->GroupCount-1;
	itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
	reset();
}

void ComboOptionView::reset() {

	comboValue = ((ZLComboOptionEntry&)*myOption).initialValue();
	AppLog("ComboOptionView::reset initialValue = %s",comboValue.c_str());
	//const char *text = comboValue.c_str();
	//myEditField->SetText(String(text));
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String(comboValue.c_str()));
/*
	if (myComboBox == 0) {
		return;
	}

	const int count = myComboBox->count();
	for (int i = 0; i < count; ++i) {
		myComboBox->removeItem(0);
	}

	const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*myOption;
	const std::vector<std::string> &values = comboOption.values();
	const std::string &initial = comboOption.initialValue();
	int selectedIndex = -1;
	int index = 0;
	for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it, ++index) {
		myComboBox->insertItem(it - values.begin(), ::qtString(*it));
		if (*it == initial) {
			selectedIndex = index;
		}
	}
	if (selectedIndex >= 0) {
		myComboBox->setCurrentIndex(selectedIndex);
	}
	*/
}
/*
void ComboOptionView::_setActive(bool active) {
//	myComboBox->setEnabled(active);
}
*/

void ComboOptionView::_onAccept() const {
	AppLog("ComboOptionView::_onAccept %s",comboValue.c_str());
	((ZLComboOptionEntry&)*myOption).onAccept(comboValue.c_str());
}

void ComboOptionView::onValueSelected(int index) {
 	AppLog("ComboOptionView::onValueSelected %d", index);
	ZLComboOptionEntry &o = (ZLComboOptionEntry&)*myOption;
	if ((index >= 0) && (index < (int)o.values().size())) {
		o.onValueSelected(index);
	}
}

//void ComboOptionView::onValueEdited(const QString &value) {
//	ZLComboOptionEntry &o = (ZLComboOptionEntry&)*myOption;
//	if (o.useOnValueEdited()) {
//		o.onValueEdited((const char*)value.toUtf8());
//	}
//}

void ComboOptionView::OnItemStateChanged(const Tizen::Ui::Control &source, int index, int itemId, Tizen::Ui::ItemStatus status){
	onValueSelected(index);
	const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*this->option();
	const std::vector<std::string> &values = comboOption.values();
	comboValue = values[index];
	const char *text = (values[index].c_str());
//	myEditField->SetText(String(text));
	AppLog("pItem->SetElement(ID_LIST_TEXT_SUBTITLE %s", text);
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String(text));
	AppLog("myTab->form()->SendUserEvent");
	myTab->form()->SendUserEvent(0, null);
}


//void ComboOptionView::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs){
	//DeleteComboOptionPopup();
//}

void ComboOptionView::OnActionPerformed( int actionId)
{
	AppLog("ComboOptionView::OnActionPerformed %d",actionId);
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("ComboOptionView::ID_BUTTON_CHECKED");
	    	myTab->form()->ShowComboOptionPopup(this);
	    	//onStateChanged(true);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("ComboOptionView::ID_BUTTON_UNCHECKED");
	    	//onStateChanged(false);
	        // Todo:
	        break;
    default:
        break;
    }
}

void ComboOptionView::OnActionPerformed(const Control& source, int actionId)
{
	AppLog("ComboOptionView::OnActionPerformed %d",actionId);
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("ComboOptionView::ID_BUTTON_CHECKED");
	    	myTab->form()->ShowComboOptionPopup(this);
	    	//onStateChanged(true);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("ComboOptionView::ID_BUTTON_UNCHECKED");
	    	//onStateChanged(false);
	        // Todo:
	        break;
    default:
        break;
    }
}


ComboOptionPopup::ComboOptionPopup(void):__parentComboOptionView(null),__parentSpinOptionView(null){}

ComboOptionPopup::~ComboOptionPopup(void){}

result ComboOptionPopup::Construct(const Tizen::Ui::Controls::Form* pParentForm, ComboOptionView* parentComboOptionView) {
	result r = Popup::Construct(true, Dimension(465,750));
	if(IsFailed(r))
		return r;
	__parentComboOptionView = parentComboOptionView;

	SetTitleText(String(parentComboOptionView->title().c_str()));
	__pParentForm = const_cast<Form*>(pParentForm);

	if(__pParentForm == null)
		return E_FAILURE;

	Button* pCancelButton = new Button();
	pCancelButton->Construct(Rectangle(125, 570, 200, 70), L"Cancel");
	AddControl(*pCancelButton);
	pCancelButton->SetActionId(ID_BUTTON_CANCEL);
	pCancelButton->AddActionEventListener(*this);
	__pComboList = new List();
	Tizen::Graphics::Rectangle rect = GetBounds();
	__pComboList->Construct(Rectangle(20, 10, 480, 520), LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_TEXT, 90, 0, 400, 0);
		//pList->Construct(rect, LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_TEXT, 100, 0, rect.width, 0);
	const ZLComboOptionEntry &comboOption = (ZLComboOptionEntry&)*__parentComboOptionView->option();
	const std::vector<std::string> &values = comboOption.values();
	const std::string &initial = comboOption.initialValue();
	int selectedIndex = -1;
	int index = 0;

	for (std::vector<std::string>::const_iterator it = values.begin(); it != values.end(); ++it, ++index) {
		String itemText((*it).c_str());
		__pComboList->AddItem(&itemText, null, null, null );
		if (*it == initial) {
			selectedIndex = index;
		}
	}
	if (selectedIndex >= 0) {
		//myComboBox->setCurrentIndex(selectedIndex);
	}
	__pComboList->AddItemEventListener(*__parentComboOptionView);
    AddControl(*__pComboList);

	return E_SUCCESS;
}

void ComboOptionPopup::OnActionPerformed(const Control& source, int actionId)
{
	switch(actionId)
	{
		case ID_BUTTON_CREATE:
			//if(CreateCategory() == true)
			__pParentForm->SendUserEvent(0, null);
			break;
		case ID_BUTTON_CANCEL:
			__pParentForm->SendUserEvent(0, null);
			break;
		default:
			break;
	}
}

