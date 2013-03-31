/*
 * ZLbadaPaintContext.h
 *
 *  Created on: 13.10.2011
 *      Author: Alex
 */

#ifndef ZLBADAPAINTCONTEXT_H_
#define ZLBADAPAINTCONTEXT_H_

#include "ZLPaintContext.h"
#include <FGraphics.h>
#include <map>

using namespace Tizen::Graphics;

class ZLFont {
public:
	std::string family;
	std::string fontStyles[4];
	ZLFont();
	~ZLFont();
	void initValue(char* name, char* value);
	std::string getFileName(bool bold, bool italic);
};

class ZLbadaPaintContext: public ZLPaintContext {
private:

	mutable int mySpaceWidth;
	int myDescent;

	bool myFontIsStored;
	std::string myStoredFamily;
	int myStoredSize;
	bool myStoredBold;
	bool myStoredItalic;
	bool defaultFontLoaded;
	std::string defaultFont;
	int deltaItalic;
	Tizen::Graphics::Color FillColor;
	Tizen::Graphics::Font* myFont;
	Tizen::Graphics::Font* myFontRegular;
	Tizen::Graphics::Font* myFontItalic;
	Tizen::Base::ByteBuffer* fontData;
	Tizen::Graphics::Font* loadExternalFont(const std::string &family, const std::string &path, int style, int size);
	void printFaceName(Tizen::Graphics::Font* font);
	Tizen::Graphics::Font* loadDefaultFont( int style, int size);
protected:
	std::map<std::string, std::string> fontsCache;
	std::map<std::string, std::string> myFontsList;
	mutable std::vector<std::string> badaFonts;
	std::vector<ZLFont*> fontsList;
	std::string checkFont(const std::string &family);
	const std::string findFont(const std::string &family, bool bold, bool italic);
	void collectFiles(std::map<std::string, std::string> &names, const char* path );
	void initMyFontsList();

	virtual void fillFamiliesList(std::vector<std::string> &families) const;
	void setFont2(const std::string &family, int size, bool bold, bool italic);

public:
	//void init();
	int myWidth;
	int myHeight;
	void deleteMyFont();
	void restoreFont();
    virtual const std::string realFontFamilyName(std::string &fontFamily) const;
	virtual void clear(ZLColor color);
	virtual void setColor(ZLColor color, LineStyle style = SOLID_LINE);
	virtual void setFillColor(ZLColor color, FillStyle style = SOLID_FILL);

	virtual void setFont(const std::string &family, int size, bool bold, bool italic);

	virtual int width() const;
	virtual int height() const;


	virtual int stringWidth(const char *str, int len, bool rtl) const;
	virtual int spaceWidth() const;
	virtual int stringHeight() const;
	virtual int descent() const;

	virtual void drawString(int x, int y, const char *str, int len, bool rtl);

	virtual void drawImage(int x, int y, const ZLImageData &image);
	virtual void drawImage(int x, int y, const ZLImageData &image, int width, int height, ScalingType type);

	virtual void fillRectangle(int x0, int y0, int x1, int y1);
	virtual void drawFilledCircle(int x, int y, int r);
	virtual void drawLine(int x0, int y0, int x1, int y1);

	Canvas* pCanvas;
	ZLbadaPaintContext();
	virtual ~ZLbadaPaintContext();
};

#endif /* ZLBADAPAINTCONTEXT_H_ */
