
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



ButtonView::ButtonView(const std::string &name, const std::string &tooltip, ZLButtonOptionEntry *option, ZLbadaDialogContent *tab,int row,int fromColumn,int  toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {
    myAction = option->action();
    AppLog("ButtonView::ButtonView");
}

void ButtonView::_createItem() {
    AppLog("ButtonView::_createItem");
    if (myAction.isNull()) {
        return;
    }
  //  Bitmap *pBmp = myTab->form()->buttonBmp;
    Bitmap *pBmp = new Bitmap;
//    pBmp->Construct(Dimension(70,90), BITMAP_PIXEL_FORMAT_ARGB8888);
    pBmp->Construct(*myTab->form()->buttonBmp, Tizen::Graphics::Rectangle(0,0,300,52));
	ZLButtonOptionEntry &entry = (ZLButtonOptionEntry&)*myOption;
	//String str;// = "   Download Demo";
	//str.Format(25, L"Value %d ",entry.initialValue());
	//myAction->text()
	std::string text = myAction->text(ZLResource::resource("networkView")["bookNode"]);
	AppLog("Button text %s", text.c_str());
	String str;
	Tizen::Base::Utility::StringUtil::Utf8ToString(( const char *)text.c_str(), str);
	OptionListItem* pItem = new OptionListItem(this);
	pItem->Construct(75);
	pItem->SetItemFormat(*myTab->form()->__pButtonViewListItemFormat);
	pItem->SetElement(ID_LIST_BITMAP, *pBmp, pBmp);
	//pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
	pItem->SetElement(ID_LIST_TEXT_TITLE,String(text.c_str()));
	pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String("Bay"));

	//pItem->SetCheckBox(ID_LIST_CHECKBOX);
	//pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);
	AppLog("PictureView::_createItem() end");
}

void ButtonView::_onAccept() const {
	AppLog("ButtonView::_onAccept()");
}

void ButtonView::OnActionPerformed(int actionId){
	AppLog("myAction->run %d",actionId);
	std::string text = myAction->text(ZLResource::resource("networkView")["bookNode"]);
	AppLog("Button text %s", text.c_str());
	std::string an = myAction->key().Name;
	AppLog("action name %s", an.c_str());

	myAction->run();
	AppLog("action name %s finished", an.c_str());
	if (an=="readDemo") 	{
			AppLog("readDemo");
			myTab->form()->pPreviousForm->SendUserEvent(2, null);
	}
	myTab->form()->RequestRedraw(true);

}
void ButtonView::OnActionPerformed(const Control& source, int actionId)
{
	AppLog("ButtonView::OnActionPerformed %d",actionId);

}
