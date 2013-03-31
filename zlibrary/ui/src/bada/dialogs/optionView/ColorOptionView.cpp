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


void ColorOptionView::addColor(const std::string &name, ZLColor color) {
//	ZLUnicodeUtil::Ucs2String txt;
//	::createNTWCHARString(txt, name);
	AppLog("ComboOptionView::addColor() name = %s",name.c_str());
	ourStrings.push_back(name);
	ourColors.push_back(color);
}
std::vector<std::string> ColorOptionView::ourStrings;
std::vector<ZLColor> ColorOptionView::ourColors;

void ColorOptionView::initVectors() {
	if (ourStrings.empty()) {
		const ZLResource &resource = ZLResource::resource(ZLDialogManager::COLOR_KEY);
		addColor(resource["black"].value(), ZLColor(0, 0, 0));
		addColor(resource["white"].value(), ZLColor(255, 255, 255));
		addColor(resource["maroon"].value(), ZLColor(128, 0, 0));
		addColor(resource["green"].value(), ZLColor(0, 128, 0));
		addColor(resource["olive"].value(), ZLColor(128, 128, 0));
		addColor(resource["navy"].value(), ZLColor(0, 0, 128));
		addColor(resource["purple"].value(), ZLColor(128, 0, 128));
		addColor(resource["teal"].value(), ZLColor(0, 128, 128));
		addColor(resource["silver"].value(), ZLColor(192, 192, 192));
		addColor(resource["gray"].value(), ZLColor(128, 128, 128));
		addColor(resource["red"].value(), ZLColor(255, 0, 0));
		addColor(resource["lime"].value(), ZLColor(0, 255, 0));
		addColor(resource["yellow"].value(), ZLColor(255, 255, 0));
		addColor(resource["blue"].value(), ZLColor(0, 0, 255));
		addColor(resource["magenta"].value(), ZLColor(255, 0, 255));
		addColor(resource["cyan"].value(), ZLColor(0, 255, 255));
	}
}

result ColorOptionView::DrawElement(const Tizen::Graphics::Canvas& canvas, const Tizen::Graphics::Rectangle& rect, Tizen::Ui::Controls::CustomListItemStatus itemStatus)
{
	result r = E_SUCCESS;
	AppLog("DrawElement");
	Tizen::Graphics::Canvas* pCanvas = const_cast<Tizen::Graphics::Canvas*>(&canvas);
	AppLog("pCanvas");
	pCanvas->SetLineWidth(5);

	if (pCanvas->FillRectangle(Color(myColor.Red,myColor.Green,myColor.Blue),rect)!= E_SUCCESS)
		return r;
	pCanvas->SetForegroundColor(Tizen::Graphics::Color::GetColor(COLOR_ID_GREY));
	if (pCanvas->DrawRectangle(rect) != E_SUCCESS)
		return r;
/*
	pCanvas->SetForegroundColor(Tizen::Graphics::Color::COLOR_WHITE);
	if (pCanvas->DrawText(Tizen::Graphics::Point(rect.x+20, rect.y+5), *pEnrichedText) != E_SUCCESS)
		return r;
*/
	return r;
}

void ColorOptionView::_createItem() {
	AppLog("ComboOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());
	initVectors();
	pItem = new OptionListItem(this);
    pItem->Construct(90);
    pItem->SetItemFormat(*myTab->form()->__pColorListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
    const ZLColor &color = ((ZLColorOptionEntry&)*myOption).color();
    myColor = ((ZLColorOptionEntry&)*myOption).color();

//	const char *text = (((ZLColorOptionEntry&)*myOption).initialValue()).c_str();
	//myEditField->SetText(String(text));
//	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String("color"));

//	pItem->SetElement(ID_LIST_BITMAP, BitmapNormal, &BitmapNormal);
  //  pItem->SetCheckBox(ID_LIST_CHECKBOX);
	pItem->SetElement(ID_LIST_COLOR, *this);
    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);
	groupIndex = myTab->form()->GroupCount-1;
	itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
}

void ColorOptionView::reset() {

}

void ColorOptionView::_onAccept() const {
	((ZLColorOptionEntry&)*myOption).onAccept(myColor);
}

void ColorOptionView::OnItemStateChanged(const Tizen::Ui::Control &source, int index, int itemId, Tizen::Ui::ItemStatus status){
	AppLog("myTab->form()->SendUserEvent");
	myTab->form()->SendUserEvent(0, null);
}

void ColorOptionView::Update() {
	myTab->form()->__pCustomList->RefreshItem(groupIndex, itemIndex);
}

void ColorOptionView::OnActionPerformed(const Tizen::Ui::Control& source, int actionId){

}

void ColorOptionView::OnActionPerformed(int actionId)
{
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("BooleanOptionView::ID_BUTTON_CHECKED");
	    	myTab->form()->ShowColorComboOptionPopup(this);
	    	//onStateChanged(true);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("BooleanOptionView::ID_BUTTON_UNCHECKED");
	    	//onStateChanged(false);
	        // Todo:
	        break;
    default:
        break;
    }
}


ColorComboOptionPopup::ColorComboOptionPopup(void){}

ColorComboOptionPopup::~ColorComboOptionPopup(void){}

result ColorComboOptionPopup::Construct(const Tizen::Ui::Controls::Form* pParentForm,  ColorOptionView* parentColorOptionView) {
    int PopupHeight = 460;
    int sliderWidth = 310;
    int sliderHeight = 90;
    int dx = 150;


	result r = Popup::Construct(true, Dimension(465,PopupHeight));
	if(IsFailed(r))
		return r;
	__parentColorOptionView = parentColorOptionView;
	  tmpColor = __parentColorOptionView->myColor;
	//SetTitleText(String(parentColorOptionView->title().c_str()));
	SetTitleText(String("Select color"));
	__pParentForm = const_cast<Form*>(pParentForm);

	if(__pParentForm == null)
		return E_FAILURE;

	Button* pCreateButton = new Button();
	pCreateButton->Construct(Rectangle(20, PopupHeight - 180, 200, 70), L"OK");
	AddControl(*pCreateButton);
	pCreateButton->SetActionId(ID_BUTTON_CREATE);
	pCreateButton->AddActionEventListener(*this);


	Button* pCancelButton = new Button();
	pCancelButton->Construct(Rectangle(230, PopupHeight - 180, 200, 70), L"Cancel");
	AddControl(*pCancelButton);
	pCancelButton->SetActionId(ID_BUTTON_CANCEL);
	pCancelButton->AddActionEventListener(*this);

	panelColor = new Panel();
	panelColor->Construct(Rectangle(10, 15, dx-10, 3*sliderHeight-20));
	panelColor->SetBackgroundColor(Tizen::Graphics::Color(tmpColor.Red,tmpColor.Green, tmpColor.Blue));
	//panelColor->SetCompositeEnabled(false);
    //Adds a Panel to the Form
    AddControl(*panelColor);



	   // Creates a ColorPicker.
    // Creates a Slider.
	sliderR = new Slider();
	sliderR->Construct(Rectangle(dx, 05, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
	sliderR->SetValue(tmpColor.Red);
	sliderR->AddAdjustmentEventListener(*this);
    AddControl(*sliderR);

	sliderG = new Slider();
	sliderG->Construct(Rectangle(dx, 05+sliderHeight, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
	sliderG->SetValue(tmpColor.Green);
	sliderG->AddAdjustmentEventListener(*this);
    AddControl(*sliderG);

	sliderB = new Slider();
	sliderB->Construct(Rectangle(dx, 05+2*sliderHeight, sliderWidth, sliderHeight), BACKGROUND_STYLE_NONE, false, 0, 255);
	sliderB->SetValue(tmpColor.Blue);
	sliderB->AddAdjustmentEventListener(*this);
    AddControl(*sliderB);


	return E_SUCCESS;
}

void ColorComboOptionPopup::OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment){
	//tmpValue = adjustment;
	tmpColor = ZLColor(sliderR->GetValue(),sliderG->GetValue(),sliderB->GetValue());
	panelColor->SetBackgroundColor(Tizen::Graphics::Color(tmpColor.Red,tmpColor.Green, tmpColor.Blue));
	panelColor->Draw();
//	Draw();
	this->RequestRedraw(true);
	AppLog("adjustment %d",adjustment);
}

void ColorComboOptionPopup::OnActionPerformed(const Control& source, int actionId)
{
	switch(actionId)
	{
		case ID_BUTTON_CREATE:
			//if(CreateCategory() == true)
			__parentColorOptionView->myColor = tmpColor;
			__pParentForm->SendUserEvent(0, null);
			__parentColorOptionView->Update();
			break;
		case ID_BUTTON_CANCEL:
			__pParentForm->SendUserEvent(0, null);
			break;
		default:
			break;
	}
}

