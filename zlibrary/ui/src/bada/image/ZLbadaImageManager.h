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

#ifndef __ZLbadaIMAGEMANAGER_H__
#define __ZLbadaIMAGEMANAGER_H__

#include <map>
//#include <QtGui/QImage>
#include <FMedia.h>
#include <FGraphics.h>

#include <ZLImageManager.h>

using namespace Tizen::Media;
using namespace Tizen::Graphics;

class ZLImage;
class ZLbadaImageData : public ZLImageData {

public:
	ZLbadaImageData();
	~ZLbadaImageData();

	unsigned int width() const;
	unsigned int height() const;

	void init(unsigned int width, unsigned int height);
	void setPosition(unsigned int x, unsigned int y);
	void moveX(int delta);
	void moveY(int delta);
	void setPixel(unsigned char r, unsigned char g, unsigned char b);

	void copyFrom(const ZLImageData &source, unsigned int targetX, unsigned int targetY);

	const Bitmap *image() const { return pBitmap; }
	Bitmap* pBitmap;
private:
//	QImage *myImage;

	unsigned int myX, myY;

friend class ZLbadaImageManager;
};

class ZLbadaImageManager : public ZLImageManager {

public:
	static void createInstance() { ourInstance = new ZLbadaImageManager(); }

private:
	ZLbadaImageManager() {}
	
protected:
	~ZLbadaImageManager() {}
	shared_ptr<ZLImageData> createData() const;
	bool convertImageDirect(const std::string &stringData, ZLImageData &imageData) const;
};

#endif /* __ZLbadaIMAGEMANAGER_H__ */
