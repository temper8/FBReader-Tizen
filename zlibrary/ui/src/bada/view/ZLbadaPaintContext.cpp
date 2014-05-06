/*
 * ZLbadaPaintContext.cpp
 *
 *  Created on: 13.10.2011
 *      Author: Alex
 */

#include "ZLbadaPaintContext.h"
#include "../image/ZLbadaImageManager.h"

#include <ZLTextStyleCollection.h>
#include <ZLTextStyleOptions.h>
#include "../../../../fbreader/src/options/FBOptions.h"
#include "../../../../fbreader/src/options/FBTextStyle.h"

#include <FIo.h>
#include <FText.h>
#include <FXml.h>
#include <FAppApp.h>

using namespace Tizen::Graphics;
using namespace Tizen::Base::Utility;
using namespace Tizen::Base;
using namespace Tizen::Text;
using namespace Tizen::Io;
using namespace Tizen::Xml;

void ZLbadaPaintContext::fillFamiliesList(std::vector<std::string> &families) const {
	AppLog( "fillFamiliesList");
    Tizen::Base::Collection::IList* FontList;
    FontList = Tizen::Graphics::Font::GetSystemFontListN();
	int Count = FontList->GetCount();
	AppLog( "fillFamiliesList %d", Count);
	badaFonts.clear();
	for (int i =0; i<Count; i++) {
		Tizen::Base::String* f = (Tizen::Base::String*)FontList->GetAt(i);
		Utf8Encoding utf8;
		ByteBuffer* pBB = utf8.GetBytesN(*f);
		std::string  family(( const char*)pBB->GetPointer());//,f->GetLength());
		AppLog( "family name = %s",family.c_str()) ;
		delete pBB;
		bool check = false;
		for (std::vector<std::string>::const_iterator it = families.begin(); it != families.end(); ++it) {
				if  (*it == family) {
					check = true;
					break;
				}
		}
		if (!check)	{
			families.push_back(family);
			badaFonts.push_back(family);
		}
	}
	FontList->RemoveAll(true);

	for (std::vector<ZLFont*>::const_iterator it=fontsList.begin() ; it != fontsList.end(); it++ ){
			ZLFont* f = *it;
			//std::string  family(f.family);
			families.push_back(f->family);
			AppLog( "myFontsList = %s",f->family.c_str()) ;
		}
}

const std::string ZLbadaPaintContext::realFontFamilyName(std::string &fontFamily) const {
//	AppLog( "realFontFamilyName %s",fontFamily.c_str());
	/*
	QString fullName = QFontInfo(QFont(fontFamily.c_str())).family();
	if (fullName.isNull() || fullName.isEmpty()) {
		fullName = QFontInfo(QFont::defaultFont()).family();
		if (fullName.isNull() || fullName.isEmpty()) {
			return HELVETICA;
		}
	}*/
	return fontFamily;//fullName.left(fullName.find(" [")).ascii();
}

Tizen::Graphics::Font* ZLbadaPaintContext::loadExternalFont(const std::string &family, const std::string &path, int style, int size)
	{
	Tizen::Graphics::Font* pFont;
	pFont = new Tizen::Graphics::Font;


   // AppLog("loadExternalFont size = %d",size);
   // AppLog("loadExternalFont style = %d",style);

	if (pFont->Construct(Tizen::Base::String(path.c_str()),style,size) != E_SUCCESS){
				AppLog("loadExternalFont not E_SUCCESS");
				delete pFont;
				delete fontData;
				fontData = 0;
				return null;
			}
 return pFont;
}

void ZLbadaPaintContext::printFaceName(Tizen::Graphics::Font* font){
	ByteBuffer* bb;
	Tizen::Base::String fontFaceName;
	fontFaceName=font->GetFaceName();
	bb = Tizen::Base::Utility::StringUtil:: StringToUtf8N(fontFaceName);
	AppLog( "fontFaceName2 %s",(char *)bb->GetPointer());
	delete bb;
}

void ZLbadaPaintContext::setFont2(const std::string &family, int size, bool bold, bool italic){
	setFont2(defaultFont,size,bold,italic);
}
void ZLbadaPaintContext::restoreFont(){
	setFont(myStoredFamily,myStoredSize,myStoredBold,myStoredItalic);
}

const std::string ZLbadaPaintContext::findFont(const std::string &family, bool bold, bool italic) {
	for (std::vector<ZLFont*>::const_iterator it=fontsList.begin() ; it != fontsList.end(); it++ ){
			ZLFont* f = *it;
			if (f->family ==  family ) return f->getFileName(bold,italic);
		}
	return std::string();
}

std::string ZLbadaPaintContext::checkFont(const std::string &family) {
	std::string badaFont;
//	AppLog("checkFont %s",family.c_str());
	for (std::vector<std::string>::const_iterator it=badaFonts.begin() ; it != badaFonts.end(); it++ )
			if (*it ==  family ) {
				badaFont = *it;
				break;
		};
	if (!badaFont.empty()) return badaFont;

	std::string font = findFont(family, false, false);
	if (!font.empty())return family;

	FBTextStyle &baseStyle = FBTextStyle::Instance();
	font = baseStyle.FontFamilyOption.value();
//	AppLog("baseStyle newFont %s",font.c_str());
	return font;
}

void ZLbadaPaintContext::setFont(const std::string &family, int size, bool bold, bool italic) {
//	AppLog( "setFont %s",family.c_str());
//	AppLog( "setFont size %d, %d, %d ",size,bold,italic);
//	AppLog( "setFont family %s",family.c_str());
	bool fontChanged = false;
	bool famylyChanged = false;
	bool styleChanged = false;

	std::string newFont = checkFont(family);

	if ((myStoredFamily != newFont)||(myStoredSize != size)||(myStoredBold != bold)) famylyChanged = true;
	int style = ( bold ? FONT_STYLE_BOLD : FONT_STYLE_PLAIN);// | ( italic ? FONT_STYLE_ITALIC : 0);
	if ((myStoredItalic != italic)) {
		styleChanged = true;
	}
	if ((!famylyChanged)) {
		AppLog( "setFont not famylyChanged");
		 if ((pCanvas!=0))  {
			if (italic) myFont = myFontItalic;
				else myFont = myFontRegular;
			if (myFont!=0) pCanvas->SetFont(*myFont);
			}
		  return;
		}


	myStoredSize = size;
	myStoredBold = bold ;
	myStoredItalic = italic;
	myStoredFamily = newFont;
/*
	if (famylyChanged) {
		deltaItalic = 0;
		if (myFontRegular!=null) delete myFontRegular;
		myFontRegular = null;
		if (myFontItalic!=null) delete myFontItalic;
		myFontItalic = null;
		if (myFontRegular == null) {
					myFontRegular = new Tizen::Graphics::Font;
					AppLog( "Construct font");
					int r = myFontRegular->Construct(style,size);
					if (IsFailed(r))
					        {
								AppLog( "IsFailed");
					        }
					}

		if (myFontItalic == null) {
					myFontItalic = new Tizen::Graphics::Font;
					myFontItalic->Construct(style| FONT_STYLE_ITALIC ,size);
					}
	//	AppLog( "setFont end");
	}*/

	//	std::string newFont = checkFont(family);
		AppLog("newFont %s",newFont.c_str());

		std::string badaFont;
		for (std::vector<std::string>::const_iterator it=badaFonts.begin() ; it != badaFonts.end(); it++ )
				if (*it ==  newFont ) {
					badaFont = *it;
					break;
			}

		std::string fontRegular;
		std::string fontItalic;
		if (badaFont.empty()) {
			fontRegular = findFont(newFont, false, false);

			AppLog("findFont");
			fontItalic = findFont(newFont, false, true);
			if (!fontRegular.empty()) {
						AppLog("myFontRegular fontFamily %s",fontRegular.c_str());
						myFontRegular = new Tizen::Graphics::Font;
						if (myFontRegular->Construct(Tizen::Base::String(fontRegular.c_str()),style, size) != E_SUCCESS){
									AppLog("font == NULL");
									myFontRegular = new Tizen::Graphics::Font;
									myFontRegular->Construct(style,size);
								}
						}

			AppLog("findFont 2");
			if (!fontItalic.empty()) {
						AppLog("myFontItalic fontFamily %s",fontItalic.c_str());
						myFontItalic = new Tizen::Graphics::Font;
						if (myFontItalic->Construct(Tizen::Base::String(fontItalic.c_str()),style, size) != E_SUCCESS){
									AppLog("font == NULL");
									myFontItalic = new Tizen::Graphics::Font;
									myFontItalic->Construct(style,size);
								}
						else {
							deltaItalic = myFontRegular->GetAscender() - myFontItalic->GetAscender();
							AppLog("deltaItalic=%d", deltaItalic );
							if (deltaItalic<0) deltaItalic = -(myFontRegular->GetDescender() - myFontItalic->GetDescender());
							AppLog("deltaItalic=%d", deltaItalic );
						}
						}


		}
		else {	AppLog("findFont 3");
			myFontRegular = new Tizen::Graphics::Font;
			//myFontRegular->Construct(badaFont.c_str(),style,size);
			myFontRegular->Construct(style,size);
			myFontItalic = new Tizen::Graphics::Font;
			//myFontItalic->Construct(badaFont.c_str(),style| FONT_STYLE_ITALIC ,size);
			myFontItalic->Construct(style| FONT_STYLE_ITALIC ,size);
		}

		if (myFontRegular == null) {	AppLog("findFont 4");
					myFontRegular = new Tizen::Graphics::Font;
					myFontRegular->Construct(style,size);
					}

		if (myFontItalic == null) { 	AppLog("findFont 5");
					myFontItalic = new Tizen::Graphics::Font;
					myFontItalic->Construct(style| FONT_STYLE_ITALIC ,size);
					}

	//}



	if (italic) myFont = myFontItalic;
		else myFont = myFontRegular;
	//	AppLog("set myFont");
	//AppLog("maxh=%d, getsize=%d, getas=%d, getdes=%d", myFont->GetMaxHeight(), myFont->GetSize(), myFont->GetAscender(), myFont->GetDescender());
	mySpaceWidth = -1;
	//myDescent = myFont->GetDescender();

   // if (myFont!=0) delete myFont;
	//myFont = font;
	if ((myFont!=0)&&(pCanvas!=0))  {
	//	AppLog("pCanvas->SetFont(*myFont)");
		pCanvas->SetFont(*myFont);
	}
//	AppLog(" end setFont");
}

void ZLbadaPaintContext::deleteMyFont(){
	 //if (myFont!=0) delete myFont;
	 //myFont = 0;

	 if (myFontRegular!=0) delete myFontRegular;
	 myFontRegular = null;
	 if (myFontItalic!=0) delete myFontItalic;
	 myFontItalic = null;
}

Tizen::Graphics::Font* ZLbadaPaintContext::loadDefaultFont( int style, int size){
	AppLog("ZLbadaPaintContext::loadDefaultFont()");
	Tizen::Graphics::Font* font = null;
	std::map<std::string, std::string>::const_iterator it = myFontsList.find(defaultFont);
	if (it != myFontsList.end()) {
		std::string fontPath;
		fontPath = it->second;
		//font = loadExternalFont(defaultFont,fontPath,style,size);
		font = new Tizen::Graphics::Font;
		if (font->Construct(String(fontPath.c_str()),style,size) != E_SUCCESS){
			//	AppLog("defaultFontLoaded not E_SUCCESS");
				delete font;
				font = null;
			}
	}
	return font;
}


int ZLbadaPaintContext::width() const {
//	if (!pCanvas) {
//		return 0;
//	}
//	return pCanvas->GetBounds().width;
	return myWidth;
}

int ZLbadaPaintContext::height() const {
	/*if (!pCanvas) {
		return 0;
	}
	return pCanvas->GetBounds().height;*/
	return  myHeight;
}

void ZLbadaPaintContext::clear(ZLColor color){
	pCanvas->SetBackgroundColor(Color(color.Red, color.Green, color.Blue, 0xFF));
	pCanvas->SetForegroundColor(Color::GetColor(COLOR_ID_GREY));
	pCanvas->Clear();
}

void ZLbadaPaintContext::setColor(ZLColor color, LineStyle style){
	//pCanvas->SetLineStyle((style == SOLID_LINE) ? LINE_STYLE_SOLID : LINE_STYLE_MIN);
	pCanvas->SetLineStyle(LINE_STYLE_SOLID);
	pCanvas->SetForegroundColor(Color(color.Red, color.Green, color.Blue, 0xFF));
}

void ZLbadaPaintContext::setFillColor(ZLColor color, FillStyle style){
	//__pCanvas->SetForegroundColor(Color::COLOR_GREY);
	FillColor.SetColorComponents(color.Red, color.Green, color.Blue, 0xFF);
}

int ZLbadaPaintContext::stringWidth(const char *str, int len, bool) const {
	Tizen::Base::String bada_str;
    ByteBuffer buffer;
    buffer.Construct(len + 1);
    buffer.SetArray((byte*)str, 0, len);
    buffer.SetByte('\0');
    buffer.Flip();
//	AppLog("ZLbadaPaintContext::stringWidth %s",(const char *)buffer.GetPointer());
//	StringUtil::Utf8ToString((const char *)buffer.GetPointer(), bada_str);
    Utf8Encoding utf8;
    int charCount;
    utf8.GetCharCount(buffer, charCount);
    utf8.GetString(buffer, bada_str);

    Dimension dim;


	 //if (!myStoredItalic) {
		 myFont->GetTextExtent(bada_str, charCount, dim);
	//	AppLog("dim.width %d",dim.width);
		 return dim.width;// + charCount*(myFont->GetCharSpace());
	 /*}
	 else{
		 int width = 0;
		 //int startY = y-myFont->GetMaxHeight();
		 mchar ch;
		 for (int i=0; i<charCount; i++){
		     bada_str.GetCharAt(i, ch);
		     int rb;
		     myFont->GetRightBear(ch, rb);
		    // int lb;
		    // myFont->GetLeftBear(ch, lb);
		    // pCanvas->DrawText(Point(startX, startY), ch);
		     AppLog("width %d",width);
		     width = width + rb;
		     }
		 return width;
	 	 }*/


}

int ZLbadaPaintContext::spaceWidth() const {
	//if (mySpaceWidth == -1)
	if (myFont==0) mySpaceWidth =-1;
	else
	{
		Dimension dim;
		//AppLog("spaceWidth");
		myFont->GetTextExtent(L" ", 1, dim);
		//pCanvas->GetFontN()->GetTextExtent(L" ", 1, dim);

		mySpaceWidth = dim.width;//+1;??
	}
	//AppLog("spaceWidth %d",mySpaceWidth);
	return mySpaceWidth;
}

int ZLbadaPaintContext::stringHeight() const{
	//return myPainter->font().pointSize() + 2;
//	AppLog("stringHeight");

	if (myFont==0) {
	//AppLog("sH  0 ");
		return 0;
	}
	int tmp =  myFont->GetMaxHeight();
	//AppLog("stringHeight %d",tmp);
	return tmp;//pmyFont->GetMaxHeight();
	//return pCanvas->GetFontN()->GetMaxHeight();
}

int ZLbadaPaintContext::descent() const{
	return myDescent;
}

void ZLbadaPaintContext::drawString(int x, int y, const char *str, int len, bool rtl){
	Tizen::Base::String bada_str;
    ByteBuffer buffer;
    buffer.Construct(len + 1);
    buffer.SetArray((byte*)str, 0, len);
    buffer.SetByte('\0');
    buffer.Flip();
//AppLog("ZLbadaPaintContext::drawString %s",(const char *)str);
//	StringUtil::Utf8ToString((const char *)buffer.GetPointer(), bada_str);
    Utf8Encoding utf8;
    int charCount;
    utf8.GetCharCount(buffer, charCount);
    utf8.GetString(buffer, bada_str);
 //   AppLog("charCount = %d : len = %d", charCount,len);
 //   DrawEnrichedTex(x, y-myFont->GetMaxHeight(),bada_str );
 //   AppLog("myStoredSize = %d ", myStoredSize);
 //   AppLog("myFont->GetMaxHeight() = %d ", myFont->GetMaxHeight());
    //Tizen::Graphics::Color clr = Tizen::Graphics::Color::COLOR_GREEN;

	if ((myFont!=0)&&(pCanvas!=0))  {
	//	AppLog("pCanvas->SetFont(*myFont)");
	//	pCanvas->SetFont(*myFont);

	 if (myStoredItalic)
		 pCanvas->DrawText(Point(x, y - myFont->GetMaxHeight()+ deltaItalic), bada_str);
	 else
		 pCanvas->DrawText(Point(x, y - myFont->GetMaxHeight()), bada_str);
}
//	AppLog("ZLbadaPaintContext::drawString end");
 /*
 if (!myStoredItalic) pCanvas->DrawText(Point(x, y-myFont->GetMaxHeight()), bada_str);
 else{
	 int startX = x;
	 int startY= y-myFont->GetMaxHeight();
	 mchar ch;
	 for (int i=0; i<charCount; i++){
	     bada_str.GetCharAt(i, ch);
	     int rb;
	     myFont->GetRightBear(ch, rb);
	     int lb;
	     myFont->GetLeftBear(ch, lb);
	     pCanvas->DrawText(Point(startX, startY), ch);
	     startX = startX + rb;
	     }
 	 }

*/
	//pCanvas->DrawText(Point(x, y-myFont->GetMaxHeight()), bada_str, Tizen::Graphics::Color::COLOR_WHITE);
//	pCanvas->DrawText(Point(x, y-myFont->GetMaxHeight()), bada_str, charCount);
//	pCanvas->DrawText(Point(x, y), bada_str,charCount);
}


void ZLbadaPaintContext::fillRectangle(int x0, int y0, int x1, int y1){
	pCanvas->FillRectangle(FillColor, Rectangle(x0, y0, x1-x0+1, y1-y0+1));
}

void ZLbadaPaintContext::drawFilledCircle(int x, int y, int r) {
	pCanvas->DrawEllipse(Rectangle(x - r, y - r, 2 * r + 1, 2 * r + 1));
}

void ZLbadaPaintContext::drawLine(int x0, int y0, int x1, int y1) {
	pCanvas->DrawLine(Point(x0, y0), Point(x1, y1));
}

void ZLbadaPaintContext::drawImage(int x, int y, const ZLImageData &image) {
	Bitmap *pBmp;
	pBmp = 	((ZLbadaImageData&)image).pBitmap;
    int imageWidth = pBmp->GetWidth();
    int imageHeight = pBmp->GetHeight();
//	AppLog("draw image w = %d, h = %d", imageWidth, imageHeight);
	pCanvas->DrawBitmap(Point(x, y), *pBmp);
}

void ZLbadaPaintContext::drawImage(int x, int y, const ZLImageData &image, int width, int height, ScalingType type) {
	Bitmap *pBmp;
	pBmp = 	((ZLbadaImageData&)image).pBitmap;
	if (pBmp == 0) {
		return;
	}
	//TODO ScalingType ни как не обрабатывается

	int w =	imageWidth(image, width, height, type);
	int h = imageHeight(image, width, height, type);
	//	Qt::KeepAspectRatio,
	//	Qt::SmoothTransformation
	pCanvas->DrawBitmap(Rectangle(x,y-h,w,h),*pBmp);
}

void ZLbadaPaintContext::collectFiles(std::map<std::string, std::string> &names, const char* path ) {
   //TODO collectFiles
	 AppLog("ZLbadaPaintContext::collectFiles") ;
    Directory dir;
    DirEnumerator *pDirEnum = null;
    result r = E_SUCCESS;

    // Opens the directory
    r = dir.Construct(path);
	 AppLog(" dir.Construct %s",path) ;
    if(IsFailed(r))  AppLog("IsFailed");

       //goto CATCH;

    // Reads all the directory entries
    pDirEnum = dir.ReadN();
  //  if(!pDirEnum)
  //      goto CATCH;
    while(pDirEnum->MoveNext() == E_SUCCESS)
    {
        DirEntry dirEntry = pDirEnum->GetCurrentDirEntry();
        Tizen::Base::String str = dirEntry.GetName();
       // AppLog("dirEntry name Length = %d",str.GetLength()) ;
        Utf8Encoding utf8;
       	ByteBuffer* pBB = utf8.GetBytesN(str);
        std::string  shortName((const char*)pBB->GetPointer());//,str.GetLength());
        AppLog("dirEntry name = %s",shortName.c_str()) ;
        if (shortName !="." && shortName !="..")	{
        	std::string fullName;
        	fullName = path + shortName;
        	AppLog("fullName = %s",fullName.c_str());
        	names.insert(std::make_pair(shortName,fullName));
        }
        delete pBB;
       // names.push_back(shortName);
    }

    // Deletes the enumerator
    delete pDirEnum;

    AppLog("Succeeded");
}

static std::string fontDirectory;

ZLFont::ZLFont(){};
	//names.insert(std::make_pair(shortName,fullName));
ZLFont::~ZLFont(){};

void ZLFont::initValue(char* name, char* value){
	 AppLog("name = %s value = %s ", name, value);
	if (!strcmp(name,"family")) {
		 	family = value;
		 	return;
			}
	if (!strcmp(name,"regular")) {
			fontStyles[0]=fontDirectory + std::string(value);
			return;
			}
	if (!strcmp(name,"italic")) {
			fontStyles[1]=fontDirectory + std::string(value);
			return;
			}
	if (!strcmp(name,"bold")) {
			fontStyles[2]=fontDirectory + std::string(value);
			return;
			}
	if (!strcmp(name,"boldItalic")) {
			fontStyles[3]=fontDirectory + std::string(value);
			return;
			}
	return;
}
std::string ZLFont::getFileName(bool bold, bool italic){
	int style = 0;
	if (italic) style = 1;
	if (bold) style = 2;
	if (bold&&italic) style = 3;
	return fontStyles[style];
}

void ZLbadaPaintContext::initMyFontsList(){
//	myFontsList
	 AppLog("initMyFontsList");
//	collectFiles(myFontsList,"/Res/Fonts/");

	 //Create xml text reader
	 AppLog("Read FontsList");
	 xmlDocPtr pDocument = null;
	 xmlNodePtr pRoot = null;
	 xmlNodePtr pCurrentElement = null;
	 // Create UI controls
	 Tizen::Base::String path = Tizen::App::App::GetInstance()->GetAppRootPath() + L"/res/Fonts/";
	 Tizen::Base::ByteBuffer* bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(path);

	 fontDirectory = (char *)bb->GetPointer();
	 AppLog( "fontDirectory %s",fontDirectory.c_str());
	 std::string fontsFile = fontDirectory + "fonts.xml";
	 pDocument = xmlParseFile(fontsFile.c_str());
	 pRoot = xmlDocGetRootElement(pDocument);

	 for (pCurrentElement = pRoot->children; pCurrentElement;
	      pCurrentElement = pCurrentElement->next)
	 {
		 xmlNodePtr pChildElement = null;
		 if (pCurrentElement->type == XML_ELEMENT_NODE)
		 {
			 ZLFont* newFont = new ZLFont;
			 fontsList.push_back(newFont);
			 for (pChildElement = pCurrentElement->children->next; pChildElement;
				  pChildElement = pChildElement->next)
			 {
				 if (pChildElement->type == XML_ELEMENT_NODE)  {
				 				 AppLog("name : %s", (char*)pChildElement->name);
				 				 //AppLog("value : %s", (char*)pChildElement->content);
				 				 //AppLog("children name : %s", (char*)pChildElement->children->name);
				 				 AppLog("children value : %s", (char*)pChildElement->children->content);
				 				 newFont->initValue((char*)pChildElement->name,(char*)pChildElement->children->content);
				 			 }
			 }


		 }
	}
}

ZLbadaPaintContext::ZLbadaPaintContext():myFont(0), defaultFont("Liberation Serif"),myStoredFamily("xxx"),myStoredSize(1), defaultFontLoaded(false) {
	// TODO Auto-generated constructor stub
	AppLog("ZLbadaPaintContext::ZLbadaPaintContext()");
	mySpaceWidth = -1;
	myDescent = 0;
	myFontIsStored = false;
	//tizen
	initMyFontsList();
	fontData = 0;
	myFontRegular = null;
	myFontItalic  = null;


}

ZLbadaPaintContext::~ZLbadaPaintContext() {
	// TODO Auto-generated destructor stub
}

