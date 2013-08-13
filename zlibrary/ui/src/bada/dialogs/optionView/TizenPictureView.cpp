/*
 * TizenPictureView.cpp
 *
 *  Created on: Aug 13, 2013
 *      Author: temper8
 */

#include "TizenPictureView.h"
#include "../../image/ZLbadaImageManager.h"

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
//	std::string myText = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
//	const char *text = myText.c_str();
//	 myCaption = ZLOptionView::name()+ ": 123";
	 myCaption.Format(30, L"TizenPictureView %s", ZLOptionView::name().c_str());
	 myImage = ((ZLPictureOptionEntry&)*myOption).image();
}

void TizenPictureView::_onAccept() const {

}


TableViewItem* TizenPictureView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, 3*defaultItemHeight), style);

	//String text;
	//text.Format(30, L"t=%s", myCaption.c_str());

	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(10, 0, itemWidth / 3, 3*defaultItemHeight), myCaption);

    Bitmap *pBmp = null;
	if (!myImage.isNull()) {
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
					 {	AppLog("coverData.isNull()");}}
	    }

	if (pBmp!=null) {
			//pItem->SetElement(ID_LIST_BITMAP, *pBmp, pBmp);
			pLabel->SetBackgroundBitmap(*pBmp);
			delete pBmp;
	}


	pItem->AddControl(pLabel);

	return pItem;
}
