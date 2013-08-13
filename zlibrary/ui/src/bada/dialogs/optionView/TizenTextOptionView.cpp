/*
 * TizenTextOptionView.cpp
 *
 *  Created on: Aug 12, 2013
 *      Author: temper8
 */

#include "TizenTextOptionView.h"
#include <FUi.h>
#include <FText.h>


using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Graphics;

int trueStringLength(const char *str, int len){
    Tizen::Base:: String bada_str;
    ByteBuffer buffer;
    buffer.Construct(len + 1);
    buffer.SetArray(( byte*)str, 0, len);
    buffer.SetByte( '\0');
    buffer.Flip();
    Tizen::Text::Utf8Encoding utf8;
    int charCount;
    utf8.GetCharCount(buffer, charCount);
  return charCount;
}

void TizenTextOptionView::_createItem() {

	myCaption.Format(40, L"%s", name().c_str());
	std::string text = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
	int len = trueStringLength(text.c_str(), text.length());
	AppLog("text = %s",text.c_str());
	AppLog("text = %d",len);
	myText.Format(len+1, L"%s", text.c_str());
	//const char *text = myText.c_str();
	std::string caption = ZLOptionView::name()+ ": ";



	//TODO переделать эту фигню
	int n = len / 20;
	int h = 45;
	if (n>1) h=n*45;

	size_t found=caption.find("????");
	AppLog("found = %d",found);
//	if (found)  textHeight=initText(caption.c_str(),myText, 2000);
//	 	 	 else textHeight=initText(null,myText, 2000);
	AppLog("textHeight = %d",textHeight);

	//pItem->Construct(textHeight+20);

   // pItem->SetItemFormat(*myTab->form()->__pStaticTextListItemFormat);
   // pItem->SetElement(ID_LIST_CUSTOM, *this);

	//myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);
	//groupIndex = myTab->form()->GroupCount-1;
	//itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
	//myTab->form()->__pCustomList->SetItemEnabled(groupIndex,itemIndex,false);
}

void TizenTextOptionView::addParagraph(std::string &text){
	result r = E_SUCCESS;
/*	AppLog("addParagraph = %s",text.c_str());
	AppLog("addParagraph length = %d",text.length());
	if (text.length()==0) return;
    TextElement* pTextElement2 = new TextElement();
    r = pTextElement2->Construct(text.c_str());
    //  r = pTextElement2->Construct(L"ttterwerwe");
    if (IsFailed(r)) goto CATCH;
    //pTextElement2->SetTextColor(Color::COLOR_GREY);
    pTextElement2->SetTextColor(Color::GetColor(COLOR_ID_GREY));

    {
    	Font font;
    	font.Construct(FONT_STYLE_PLAIN, 30);
    	pTextElement2->SetFont(font);
    }

    pEnrichedText->Add(*pTextElement2);

    return;

    CATCH:
    	AppLog("addParagraph CATCH");
    	delete pTextElement2;
  */  return;
}

int TizenTextOptionView::initText(const char *caption, std::string &text, int height){
/*   result r = E_SUCCESS;
   int found;
   int found2;
   std::string p;

    // Creates an EnrichedText instance and sets the attributes
    pEnrichedText = new EnrichedText();
    r = pEnrichedText->Construct(Dimension(470, height ));
    if (IsFailed(r))    {        goto CATCH;    }
    pEnrichedText->SetHorizontalAlignment(TEXT_ALIGNMENT_LEFT);
    pEnrichedText->SetVerticalAlignment(TEXT_ALIGNMENT_TOP);
    pEnrichedText->SetTextWrapStyle(TEXT_WRAP_WORD_WRAP);
    //  pEnrichedText->SetTextAbbreviationEnabled(true);

	// Create a TextElement and set attributes.
	if (caption) {
	    	TextElement* pTextElement1 = new TextElement();
	    	r = pTextElement1->Construct(caption);
	    	//if (IsFailed(r))   {	        goto CATCH;   	    }
	    	pTextElement1->SetTextColor(Color::GetColor(COLOR_ID_WHITE));

	    	{
	    	Font font;
	    	font.Construct(FONT_STYLE_BOLD, 30);
	    	pTextElement1->SetFont(font);
	    	}
	    	pEnrichedText->Add(*pTextElement1);
	    }

    found=text.find("<p>");
    if (found) 	addParagraph(text);
    else
	    {
	    	AppLog("found0 = %d",found);
	    	do
	    	{
	    	found2=text.find("</p>",found);
	    	AppLog("found2 = %d",found2);
	    	p.assign(text,found+3,found2-found-3);
	    	p.append("\n");
	    	addParagraph(p);
	    	found=text.find("<p>",found2-3);
	    	AppLog("found = %d",found);
	    	}
	    	while (found>0);

	    }


		    // Cleans up
	   // pEnrichedText->RemoveAll(true);
	   // delete pEnrichedText;
	AppLog("GetTotalLineCount  = %d",pEnrichedText->GetTotalLineCount());
    return pEnrichedText->GetTotalLineHeight();

	CATCH:
	    if (pEnrichedText)
	    {
	      //  pEnrichedText->RemoveAll(true);
	       // delete pEnrichedText;
	    }
*/
	    return 0;

}

void TizenTextOptionView::_onAccept() const {

}


TableViewItem* TizenTextOptionView::createTableViewItem(int itemWidth, int defaultItemHeight) {
	TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_NORMAL;
	//TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_DETAILED;
	//TableViewAnnexStyle style = TABLE_VIEW_ANNEX_STYLE_MARK;
	TableViewItem* pItem = new TableViewItem();
	pItem->Construct(Dimension(itemWidth, 2*defaultItemHeight-25), style);



	Label* pLabel = new Label();
	pLabel->Construct(Rectangle(0, 0, itemWidth, defaultItemHeight-10), myCaption);
	pLabel->SetTextConfig(30.0f, LABEL_TEXT_STYLE_NORMAL);
	pLabel->SetTextHorizontalAlignment(ALIGNMENT_LEFT);

	pItem->AddControl(pLabel);

	// Creates an instance of TextBox
	TextBox* __pTextBox = new TextBox();
	__pTextBox->Construct(Rectangle(10, defaultItemHeight-30, itemWidth-20, defaultItemHeight-10), TEXT_BOX_BORDER_ROUNDED);

	    // Sets properties on the text box
	__pTextBox->SetTextSize(30);
    __pTextBox->SetText(myText);
	__pTextBox->SetTextColor(TEXT_BOX_TEXT_COLOR_HIGHLIGHTED, Color::GetColor(COLOR_ID_RED));
	//__pTextBox->SetTextSize(40);
	//__pTextBox->AppendText(L"\nTizen SDK");



	pItem->AddControl(__pTextBox);

	return pItem;
}
