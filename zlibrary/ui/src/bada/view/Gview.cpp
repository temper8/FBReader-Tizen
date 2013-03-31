/*
 * Gview.cpp
 *
 *  Created on: 13.10.2011
 *      Author: Alex
 */
#include <FBase.h>
#include "ZLView.h"
#include "ZLbadaPaintContext.h"
#include "Gview.h"


 using namespace Tizen::Base;
 using namespace Tizen::Base::Utility;

 void GView::ReadImage(){
	 AppLog("GView::ReadImage");
	 ZLFile file("/Home/SampleImage.jpg");
	 const std::string ext = file.extension();
	//if (ext == "gif" || ext == "jpeg" || ext == "jpg") {
		 AppLog("file.ext = %s", ext.c_str());
	//	 AppLog("file.mime %s", file.mimeType().c_str());
	 	 testImage = new ZLFileImage(file, 0);
//		}
	 	//shared_ptr<ZLImage> cover = coverImage();
	 	testImageData = ZLImageManager::Instance().imageData(*testImage);
	//context.drawImage(width) / 2, vOffset + (h + height) / 2, *coverData, width, height, ZLPaintContext::SCALE_FIT_TO_SIZE);

 }

bool GView::onStylusRelease(int x, int y) {
	CircleXY.x=x;
	CircleXY.y=y;
	return true;
}


GView::GView(ZLPaintContext &context) :	ZLView(context) {
	// TODO Auto-generated constructor stub
	AppLog("GView::GView(ZLPaintContext &context)");
//	ReadImage();
}

GView::~GView() {
	// TODO Auto-generated destructor stub
}

void GView::paint() {
	ReadImage();
	AppLog("GView::paint()");
	ZLbadaPaintContext &c = (ZLbadaPaintContext&)this->context();

	this->context().clear(ZLColor(255, 255, 255));

    int h,w;
    h = this->context().height();
    w = this->context().width();

    this->context().setFillColor(ZLColor(240, 240, 240));
   	this->context().fillRectangle(20,20,w-20,h-20);
   //	this->context().drawImage(20,20, *testImageData);
   	this->context().drawImage(200,300, *testImageData,100,100,ZLPaintContext::SCALE_FIT_TO_SIZE);
	this->context().setColor(ZLColor(127, 127, 127));
	this->context().drawLine(10, 10, 200+ (Math::Rand() % (200)), 400+ (Math::Rand() % (200)));

	this->context().setColor(ZLColor(0, 255, 0));
	this->context().drawLine(10, 600, 200+ (Math::Rand() % (200)), 100+ (Math::Rand() % (200)));

	this->context().setFillColor(ZLColor(200, 0, 0));
	this->context().fillRectangle(CircleXY.x-50,CircleXY.y-50,CircleXY.x+50,CircleXY.y+50);

	this->context().setFillColor(ZLColor(200, 200, 0));
	this->context().fillRectangle(CircleXY.x-25,CircleXY.y-25,CircleXY.x+75,CircleXY.y+75);

	this->context().setColor(ZLColor(0, 0, 0));
	this->context().drawFilledCircle(CircleXY.x,CircleXY.y,60);

	this->context().setColor(ZLColor(0, 0, 255));
	this->context().drawString(CircleXY.x-20,CircleXY.y-0,"TextРусский",10,0);

	AppLog("h=%d, w=%d",h,w);
	Tizen::Base::String str;
	str.Format(20, L"Canvas size h=%d, w=%d", h, w);
    c.pCanvas->DrawText(Point(20, 300), str,40);

    str.Format(20, L"SpaceWidth =%d", this->context().spaceWidth());
     c.pCanvas->DrawText(Point(20, 330), str,20);

	ByteBuffer* bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(str);
	AppLog((char*)bb->GetPointer());
	this->context().drawString(20,20, (char*)bb->GetPointer(), 20,0);

	this->context().setFont("family", 16, false, false);
	this->context().drawString(20,60, "Size = 12 Normal__________",25,0);

	this->context().setFont("family", 18, false, true);
	this->context().drawString(20,100, "Size = 16 Normal   Italic_",25,0);

	this->context().setFont("family", 24, true, false);
	this->context().drawString(20,140,"Size = 20 Bold____________",25,0);
	int ws =this->context().stringWidth("Size = 20 Bold____________",25,0);
	this->context().drawLine(20, 140, 20 + ws, 140);

	this->context().setFont("family", 32, true, true);
	this->context().drawString(20,180,"Size = 32 Bold     Italic_",25,0);
	ws =this->context().stringWidth("Size = 32 Bold     Italic_",25,0);
	this->context().drawLine(20, 180, 20 + ws, 180);

	str.Format(40, L"32 SpaceWidth =%d descent =%d", this->context().spaceWidth(),this->context().descent());
	c.pCanvas->DrawText(Point(20, 360), str,80);
	str.Format(20, L"32 stringHeight =%d ", this->context().stringHeight());
	c.pCanvas->DrawText(Point(20, 400), str,80);


	//c.pCanvas->Show();
}
