
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

class ButtonAction : public Tizen::Ui::Controls::ICustomListElement {
public :
	ButtonAction(PictureView* holder, Bitmap* Bmp1, Bitmap* Bmp2);
	~ButtonAction();
    void SetCaption(std::string &text);
	void SetAction(shared_ptr<ZLRunnableWithKey> action);
	bool OnActionPerformed(int actionId);
	bool visible;

private :
	Tizen::Graphics::EnrichedText* pEnrichedText;
	PictureView* myHolder;
	shared_ptr<ZLRunnableWithKey> myAction;
	Bitmap* myButtonBmp1;
	Bitmap* myButtonBmp2;
	result DrawElement(const Tizen::Graphics::Canvas& canvas, const Tizen::Graphics::Rectangle& rect, Tizen::Ui::Controls::CustomListItemStatus itemStatus);

};
bool ButtonAction::OnActionPerformed(int actionId){
	AppLog("myAction->run %d",actionId);
	if (!myAction.isNull()) {
		//std::string text = myAction->text(ZLResource::resource("networkView")["bookNode"]);
		std::string text = myAction->key().Name;
		AppLog("OnActionPerformed= %s", text.c_str());
		myAction->run();
		if (text=="readDemo") 	return true;
		if (text=="read") 	return true;
	}
	return false;
}

void  ButtonAction::SetAction(shared_ptr<ZLRunnableWithKey> action){
	myAction=action;
	std::string text = myAction->text(ZLResource::resource("networkView")["bookNode"]);
	AppLog("SetActiont %s", text.c_str());
	SetCaption(text);
	visible = true;
}

ButtonAction::~ButtonAction(){
	AppLog("~ButtonAction  1");
	if(pEnrichedText) {
		AppLog("~ButtonAction  2");
		pEnrichedText->RemoveAll(true);
		delete pEnrichedText;
	}
	AppLog("~ButtonAction  3");
}

ButtonAction::ButtonAction(PictureView* holder, Bitmap* Bmp1, Bitmap* Bmp2):myHolder(holder), myAction(null), myButtonBmp1(Bmp1), myButtonBmp2(Bmp2)
	{
	 result r = E_SUCCESS;
	 TextElement* pTextElement1 = null;
    pTextElement1 = new TextElement();
	pEnrichedText = new EnrichedText();
    r = pEnrichedText->Construct(Dimension(220, 50));
    //if (IsFailed(r))   {  goto CATCH;  }
    pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_CENTER);
    pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
    pEnrichedText->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);


    r = pTextElement1->Construct("Text Button");
    	//if (IsFailed(r))    	    { 	    	        goto CATCH;	    	    }
   	pTextElement1->SetTextColor(Color::GetColor(COLOR_ID_BLACK));
       	{
       	Font font;
       	font.Construct(FONT_STYLE_PLAIN, 25);
       	pTextElement1->SetFont(font);
      	}
    pEnrichedText->Add(*pTextElement1);
}

void ButtonAction::SetCaption(std::string &text){
	result r = E_SUCCESS;
	TextElement* pTextElement1 = null;
	AppLog("SetCaption  1 %s",text.c_str());
	pEnrichedText->RemoveAllTextElements(true);
	//pEnrichedText->RemoveAll(false);
	AppLog("SetCaption  2");
    pTextElement1 = new TextElement();
    r = pTextElement1->Construct(text.c_str());
    	//if (IsFailed(r))    	    { 	    	        goto CATCH;	    	    }
   	pTextElement1->SetTextColor(Color::GetColor(COLOR_ID_BLACK));
       	{
       	Font font;
       	font.Construct(FONT_STYLE_PLAIN, 25);
       	pTextElement1->SetFont(font);
      	}
    pEnrichedText->Add(*pTextElement1);
}

result ButtonAction::DrawElement(const Tizen::Graphics::Canvas& canvas, const Tizen::Graphics::Rectangle& rect, Tizen::Ui::Controls::CustomListItemStatus itemStatus)
{
	result r = E_SUCCESS;
	if (!visible) return r;
//	AppLog("DrawElement");
	Tizen::Graphics::Canvas* pCanvas = const_cast<Tizen::Graphics::Canvas*>(&canvas);
//	AppLog("pCanvas");
	switch(itemStatus) {
	case  CUSTOM_LIST_ITEM_STATUS_NORMAL:
		    pCanvas->DrawBitmap(rect,*myButtonBmp1);
			break;
	case  CUSTOM_LIST_ITEM_STATUS_SELECTED:
	    pCanvas->DrawBitmap(rect,*myButtonBmp2);
		    break;
	case  CUSTOM_LIST_ITEM_STATUS_FOCUSED:
	    pCanvas->DrawBitmap(rect,*myButtonBmp2);
			break;
	default : break;
	}

/*	pCanvas->SetLineWidth(5);
	pCanvas->SetForegroundColor(Tizen::Graphics::Color::COLOR_GREEN);
	if (pCanvas->DrawRectangle(rect) != E_SUCCESS)
		return r;
*/

	//pCanvas->SetForegroundColor(Tizen::Graphics::Color::COLOR_BLACK);
	if (pCanvas->DrawText(Tizen::Graphics::Point(rect.x, rect.y+10), *pEnrichedText) != E_SUCCESS)
		//return r;

	return r;
}

PictureView::PictureView(const std::string &name, const std::string &tooltip, ZLPictureOptionEntry *option, ZLbadaDialogContent *tab,int row,int fromColumn,int  toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn), myActions(option->myActions) {
	 AppLog("PictureView::PictureView");
	 //myNode = option->node();
	  AppLog("PictureView::PictureView 1");

	  myImage = option->image();
    AppLog("PictureView::PictureView 2");
}

PictureView::~PictureView(){
	  AppLog("~PictureView 1");
	delete myBottonActions[0];
	delete myBottonActions[1];
	delete myBottonActions[2];
	delete myBottonActions[3];
	  AppLog("~PictureView 2");
}

void PictureView::updateActions(){
	std::string s0 = "Button0";
	std::string s1 = "Button1";

	myBottonActions[0]->visible = false;
	myBottonActions[1]->visible = false;
	myBottonActions[2]->visible = false;
	myBottonActions[3]->visible = false;

	int actionsCount = myActions.size();
	AppLog("actionsCount %d", actionsCount);

	actionsCount = myActions.size();
	AppLog("after init actionsCount %d", actionsCount);
	actionsCount =0;
	for (int i =1; i<myActions.size();i++){
		shared_ptr<ZLRunnableWithKey> a = myActions[i];
		if (a->makesSense()&&(actionsCount<4)) { AppLog("makesSense true %d",actionsCount);
			myBottonActions[actionsCount++]->SetAction(a);
		}
		else AppLog("makesSense false");
	}
}

Bitmap* PictureView::makeCover(Bitmap* srcBmp){
	Dimension coverDim = Dimension(200,300);
	Bitmap *pBmp = new Bitmap;
	pBmp->Construct(coverDim, BITMAP_PIXEL_FORMAT_ARGB8888);
	int imageWidth = srcBmp->GetWidth();
	int imageHeight = srcBmp->GetHeight();
	AppLog("makeIcon image w = %d, h = %d", imageWidth, imageHeight);

	if (imageWidth>50) {
		srcBmp->Scale(coverDim);
		pBmp->Merge(Point(0,0), *srcBmp, Rectangle(0,0,coverDim.width,coverDim.height));
	}
	else
		{
		float kx = coverDim.width/imageWidth;
		float ky = coverDim.height/imageHeight;
		int k;
		if (kx<ky) k=kx; else k=ky;
		AppLog("k = %d", k);
		Dimension coverDim2 = Dimension(imageWidth*k,imageHeight*k);
		int dy = (coverDim.height - coverDim2.height) / 2;
		int dx = (coverDim.width - coverDim2.width) / 2;
		srcBmp->Scale(coverDim2);
		//pBmp->Merge(Point(0,0), *srcBmp, Rectangle(0,0,coverDim.width,coverDim.height));
		pBmp->Merge(Point(dx,dy), *srcBmp, Rectangle(0,0,coverDim2.width,coverDim2.height));
		}
	return pBmp;
}

void PictureView::_createItem() {
    AppLog("PictureView::_createItem");
    if (myImage.isNull()) {
        return;
    }
    Bitmap *pBmp = null;

	shared_ptr<ZLImage> cover = myImage;
	if (cover.isNull()) {	AppLog("cover.isNull()");}
	else
			{
			shared_ptr<ZLImageData> coverData = ZLImageManager::Instance().imageData(*cover);
			if (!coverData.isNull()) {
				ZLImageData &image = *coverData;
				Bitmap *tmpBmp = 	((ZLbadaImageData&)image).pBitmap;
				pBmp = makeCover(tmpBmp);
			}
			else
			 {	AppLog("coverData.isNull()");}

			}

	myBottonActions[0] = new ButtonAction(this, myTab->form()->buttonBmp, myTab->form()->buttonBmp2);
	myBottonActions[1] = new ButtonAction(this, myTab->form()->buttonBmp, myTab->form()->buttonBmp2);
	myBottonActions[2] = new ButtonAction(this, myTab->form()->buttonBmp, myTab->form()->buttonBmp2);
	myBottonActions[3] = new ButtonAction(this, myTab->form()->buttonBmp, myTab->form()->buttonBmp2);
	updateActions();
	OptionListItem* pItem = new OptionListItem(this);
	pItem->Construct(330);
	pItem->SetItemFormat(*myTab->form()->__pImageViewListItemFormat);
	pItem->SetElement(ID_LIST_BACKGROUND, String(""));

	if (pBmp!=null) {
			pItem->SetElement(ID_LIST_BITMAP, *pBmp, pBmp);
			delete pBmp;
	}
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);

	groupIndex = myTab->form()->GroupCount-1;
	itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
	AppLog("groupIndex =%d itemIndex=%d",groupIndex,itemIndex);
	AppLog("PictureView::_createItem() end");
}

void PictureView::_onAccept() const {
	AppLog("PictureView::_onAccept()");
}

void PictureView::OnActionPerformed(const Control& source, int actionId)
{
	AppLog("PictureView::OnActionPerformed 1 %d",actionId);
}

void PictureView::OnActionPerformed(int actionId){
	AppLog("PictureView::OnActionPerformed 2 %d",actionId);
	bool exitFlag=false;
	bool needUpdate= false;
	   switch (actionId)
	    {
	        case ID_LIST_BITMAP1:
	        	if (myBottonActions[0]->visible)
	        	{
	        		exitFlag=myBottonActions[0]->OnActionPerformed(actionId);
	        		needUpdate= true;
	        	}
	        	break;
	        case ID_LIST_BITMAP2:
	        	if (myBottonActions[1]->visible)
	        	{
	        		exitFlag=myBottonActions[1]->OnActionPerformed(actionId);
	        		needUpdate= true;
	        	}
	        	break;
	        case ID_LIST_BITMAP3:
	        	if (myBottonActions[2]->visible)
	        	{
	        		needUpdate= true;
	        		exitFlag=myBottonActions[2]->OnActionPerformed(actionId);
	        	}
	        	break;
	        case ID_LIST_BITMAP4:
	        	if (myBottonActions[3]->visible){
	        		needUpdate= true;
	        		exitFlag=myBottonActions[3]->OnActionPerformed(actionId);
	        	}
	          	break;
	        default:
	        	break;
	    }
	   AppLog("PictureView::OnActionPerformed 2222 %d",actionId);
	   if (exitFlag) {
			myTab->form()->pPreviousForm->SendUserEvent(2, null);
			return;
	   }
	   if (needUpdate) 	{
		   updateActions();
		   myTab->form()->__pCustomList->RefreshItem( groupIndex,itemIndex );
		   myTab->form()->RequestRedraw(true);
		   //	myTab->form()->RequestRedraw(true);
		   //myTab->form()->Draw();
	   }



}
