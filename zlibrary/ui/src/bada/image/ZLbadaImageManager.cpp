/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

//#include <QtGui/QPainter>
 #include <FBase.h>
  #include <FMedia.h>
  #include <FGraphics.h>
  #include <FIo.h>
  #include <FUi.h>


#include <ZLImage.h>

#include "ZLbadaImageManager.h"

using namespace Tizen::Base;
using namespace Tizen::Media;
using namespace Tizen::Graphics;



ZLbadaImageData::ZLbadaImageData(): pBitmap(0), myX(0), myY(0){
}

ZLbadaImageData::~ZLbadaImageData() {
	if (pBitmap != 0) {
		delete pBitmap;
	}
}

unsigned int ZLbadaImageData::width() const {
	return (pBitmap != 0) ? pBitmap->GetWidth() : 0;
}

unsigned int ZLbadaImageData::height() const {
	return (pBitmap != 0) ? pBitmap->GetHeight() : 0;
}

void ZLbadaImageData::init(unsigned int width, unsigned int height) {
	if (pBitmap != 0) {
		delete pBitmap;
	}
	//pImage = new QImage(width, height, QImage::Format_RGB32);
//	AppLog("new Bitmap %d %d",width,height );
	// pBitmap = new Bitmap();
     // Construct Bitmap without buffer scaling.
   //  pBitmap->Construct(Dimension(width, height), BITMAP_PIXEL_FORMAT_ARGB8888);


}

void ZLbadaImageData::setPosition(unsigned int x, unsigned int y) {
	myX = x;
	myY = y;
}

void ZLbadaImageData::moveX(int delta) {
	myX += delta;
}

void ZLbadaImageData::moveY(int delta) {
	myY += delta;
}

void ZLbadaImageData::setPixel(unsigned char r, unsigned char g, unsigned char b) {
//	myImage->setPixel(myX, myY, qRgb(r, g, b));
}

void ZLbadaImageData::copyFrom(const ZLImageData &source, unsigned int targetX, unsigned int targetY) {
//	const QImage *sourceImage = ((const ZLbadaImageData*)&source)->image();
//	if ((myImage != 0) && (sourceImage != 0)) {
//		QPainter painter(myImage);
//		painter.drawImage(targetX, targetY, *sourceImage);
//	}
}

shared_ptr<ZLImageData> ZLbadaImageManager::createData() const {
	return new ZLbadaImageData();
}

bool ZLbadaImageManager::convertImageDirect(const std::string &stringData, ZLImageData &data) const {

	result r = E_SUCCESS;
	Image Image;

	r = Image.Construct();
//	AppLog("convertImageDirect" );
	//IMG_FORMAT_NONE  No image format type
	//IMG_FORMAT_JPG  The JPEG image format type
	//IMG_FORMAT_PNG  The PNG image format type
	//IMG_FORMAT_GIF  The GIF image format type
	//IMG_FORMAT_BMP  The BMP image format type
	//IMG_FORMAT_TIFF  The TIFF image format type
	//IMG_FORMAT_WBMP  The WBMP image format type
	int imageWidth=0;
	int imageHeight=0;
	ByteBuffer *pBuffer;
	pBuffer = new ByteBuffer();
	pBuffer->Construct(stringData.length());
    pBuffer->SetArray((const unsigned char*)stringData.data(),0, stringData.length());
//    AppLog("SetArray %d",  stringData.length());
    ImageFormat iformat;
    if (strncmp(stringData.data()+1, "PNG", 3) == 0) {
    	AppLog("iformat = IMG_FORMAT_PNG" );
    	iformat = IMG_FORMAT_PNG;
    }
    else
    if (strncmp(stringData.data(), "GIF", 3) == 0) {
        	AppLog("iformat = IMG_FORMAT_GIF" );
        	iformat = IMG_FORMAT_GIF;
        }
    else {
    	iformat = IMG_FORMAT_JPG;
    	AppLog("iformat = IMG_FORMAT_JPG" );
    }
    Bitmap* tmpBitmap = Image.DecodeN(*pBuffer,iformat, BITMAP_PIXEL_FORMAT_ARGB8888);
    //((ZLbadaImageData&)data).pBitmap = Image.DecodeN(*pBuffer,iformat, BITMAP_PIXEL_FORMAT_ARGB8888);
	//AppLog("DecodeN" );
 //   ((ZLbadaImageData&)data).pBitmap = Image.DecodeN(*pBuffer,iformat, BITMAP_PIXEL_FORMAT_RGB565);
    r = GetLastResult();
	//AppLog("GetLastResult =%d", r);
	if (!IsFailed(r)) {
		((ZLbadaImageData&)data).init(0, 0);
		((ZLbadaImageData&)data).pBitmap = tmpBitmap;
	    imageWidth = ((ZLbadaImageData&)data).pBitmap->GetWidth();
	    imageHeight = ((ZLbadaImageData&)data).pBitmap->GetHeight();
		AppLog("image w = %d, h = %d", imageWidth, imageHeight);
		delete pBuffer;
		return true;
	}
	else {
		AppLog("DecodeN IsFailed" );
		//((ZLbadaImageData&)data).pBitmap = null;
		delete pBuffer;
		return false;
	}



}
