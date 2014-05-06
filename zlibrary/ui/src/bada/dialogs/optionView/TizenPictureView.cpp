/*
 * TizenPictureView.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: temper8
 */

#include "TizenPictureView.h"
#include "../../image/ZLbadaImageManager.h"
#include "../TizenDialogForm.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;


Bitmap* TizenPictureView::makeCover(Bitmap* srcBmp){
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

void TizenPictureView::_createItem() {
	 myCaption.Format(30, L"TizenPictureView %s", ZLOptionView::name().c_str());
	 myImage = ((ZLPictureOptionEntry&)*myOption).image();

}

void TizenPictureView::_onAccept() const {

}

void TizenPictureView::OnActionPerformed(const Control& source, int actionId)
{
	int id = actionId - 300;
	AppLog("OnActionPerformed id= %d",id);
	if (id<0) return;
	shared_ptr<ZLRunnableWithKey> action = myActions[id];

	if (!action.isNull()) {
			//std::string text = myAction->text(ZLResource::resource("networkView")["bookNode"]);
			std::string text = action->key().Name;
			AppLog("OnActionPerformed= %s", text.c_str());
			action->run();

			if ((text=="readDemo")||(text=="read")) {
				Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
				TizenDialogForm* myForm = (TizenDialogForm*)pFrame->GetCurrentForm();
				myForm->pPreviousForm->SendUserEvent(2, null);
			}
			else {
				Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
				TizenDialogForm* myForm = (TizenDialogForm*)pFrame->GetCurrentForm();
				myForm->__pTableView->UpdateTableView();
				AppLog("OnActionPerformed UpdateTableView");
			}
		}
}

void TizenPictureView::createActionButtons(TableViewItem* pItem){
	std::string s0 = "Button0";
	std::string s1 = "Button1";

	int actionsCount = myActions.size();
	AppLog("action Count %d", actionsCount);

	actionsCount =0;
	for (int i =1; i<myActions.size();i++){
		shared_ptr<ZLRunnableWithKey> a = myActions[i];
		std::string text = a->text(ZLResource::resource("networkView")["bookNode"]);
		AppLog("action text %s", text.c_str());
		if (a->makesSense()&&(actionsCount<4)) { AppLog("action makesSense true %d",actionsCount);
		//if (i<4) { AppLog("makesSense true %d",actionsCount);

			Button* pButton = new Button();
			pButton->Construct(Rectangle(300, 20+100*actionsCount, 350, 80),String(text.c_str()));
			pButton->SetActionId(300 + i);
			pButton->AddActionEventListener(*this);
			pItem->AddControl(pButton);
			pItem->SetIndividualSelectionEnabled(pButton, true);
			actionsCount++;
		}
		else AppLog("action makesSense false %d",actionsCount);
	}
}

TableViewItem* TizenPictureView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, 3*defaultItemHeight), style);
	//pItem->SetEnabled(false);
	String text;
	//text.Format(30, L"t=%s", myCaption.c_str());
	Label* pLabel0 = new Label();
	pLabel0->Construct(Rectangle(30, 0, itemWidth, 3*defaultItemHeight), text);
	pItem->AddControl(pLabel0);

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(30, 0, 200, 300), text);

    Bitmap *pBmp = null;
	if (!myImage.isNull()) {
			shared_ptr<ZLImage> cover = myImage;
			if (!cover.isNull())	{
					shared_ptr<ZLImageData> coverData = ZLImageManager::Instance().imageData(*cover);
					if (!coverData.isNull()) {
						ZLImageData &image = *coverData;
						Bitmap *tmpBmp = 	((ZLbadaImageData&)image).pBitmap;
						pBmp = makeCover(tmpBmp);
					}
			}
	}
	if (pBmp!=null) {
			pLabel->SetBackgroundBitmap(*pBmp);
			delete pBmp;
	}

	pItem->AddControl(pLabel);

	createActionButtons(pItem);

	pItem->SetIndividualSelectionEnabled(pLabel0, true);
	pItem->SetIndividualSelectionEnabled(pLabel, true);
//	pItem->SetIndividualSelectionEnabled(pButton1, true);
//	pItem->SetIndividualSelectionEnabled(pButton2, true);

	return pItem;
}
