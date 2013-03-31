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

void ZLbadaOptionView::_show() {
	AppLog("BooleanOptionView::_show()");
	myTab->form()->__pCustomList->SetItemEnabled(groupIndex,itemIndex,true);
	myTab->form()->RequestRedraw(true);
}

void ZLbadaOptionView::_hide() {
	AppLog("ZLbadaOptionView::_hide()");
	AppLog("groupIndex =%d itemIndex=%d",groupIndex,itemIndex);
	myTab->form()->__pCustomList->SetItemEnabled(groupIndex,itemIndex,false);
	myTab->form()->RequestRedraw(true);
}

void ZLbadaOptionView::_setActive(bool active) {
	AppLog("StringOptionView::_setActive %s",(active)?"true":"false");
	myTab->form()->__pCustomList->SetItemEnabled(groupIndex,itemIndex,active);
}


void BooleanOptionView::_createItem() {
	AppLog("BooleanOptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());

	OptionListItem* pItem = new OptionListItem(this);
    pItem->Construct(100);
    pItem->SetItemFormat(*myTab->form()->__pBooleanListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
	//    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
	//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
    pItem->SetCheckBox(ID_LIST_CHECKBOX);
  //  pItem->SetValue(50);
    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
	myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);
	groupIndex = myTab->form()->GroupCount-1;
	itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
	AppLog("BooleanOptionView groupIndex =%d itemIndex=%d",groupIndex,itemIndex);
	//myTab->form()->__pCustomList->GetLastCheckedItemIndex( groupIndex, itemIndex);
	checkState = ((ZLBooleanOptionEntry&)*myOption).initialState();
	myTab->form()->__pCustomList->SetItemChecked(groupIndex,itemIndex,checkState);
	AppLog("BooleanOptionView:: %d, %d",groupIndex,itemIndex );
}


void BooleanOptionView::_onAccept() const {
	AppLog("BooleanOptionView::_onAccept");
	((ZLBooleanOptionEntry&)*myOption).onAccept(checkState);
}

void BooleanOptionView::onStateChanged(bool state) {
	AppLog("BooleanOptionView::onStateChanged()");
	checkState = state;
	((ZLBooleanOptionEntry&)*myOption).onStateChanged(state);
}

void BooleanOptionView::OnActionPerformed(int actionId)
{
	AppLog("BooleanOptionView::OnActionPerformed %d", actionId);
	onStateChanged(!checkState);
}


void Boolean3OptionView::_createItem() {
	AppLog("Boolean3OptionView::_createItem() name = %s",(ZLOptionView::name()).c_str());

	OptionListItem* pItem = new OptionListItem(this);
	    pItem->Construct(100);
	    pItem->SetItemFormat(*myTab->form()->__pCustomListItemFormat2);
	    pItem->SetElement(ID_LIST_TEXT_TITLE,String((ZLOptionView::name()).c_str()));
		//    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
		//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
	    pItem->SetCheckBox(ID_LIST_CHECKBOX);
	    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
		myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);
		groupIndex = myTab->form()->GroupCount-1;
		itemIndex = myTab->form()->__pCustomList->GetItemCountAt(groupIndex)-1;
		AppLog("Boolean3OptionView groupIndex =%d itemIndex=%d",groupIndex,itemIndex);

 /*   myCheckButton = new CheckButton();
    myCheckButton->Construct(Rectangle(5, myTab->form()->YPos, myTab->form()->clientArea.width-10, 80),
	        CHECK_BUTTON_STYLE_MARK, BACKGROUND_STYLE_DEFAULT,
	        false, ZLOptionView::name().c_str());

	bool state = false;
	switch (((ZLBoolean3OptionEntry&)*myOption).initialState()) {
		case B3_FALSE:
			state = false;
			break;
		case B3_TRUE:
			state = true;
			break;
		case B3_UNDEFINED:
			state = false;
			break;
	}
    myCheckButton->SetSelected(state);
	myTab->form()->pScrollPanel->AddControl(*myCheckButton);
	myTab->form()->YPos+=120;
*/
	//myWidgets.push_back(myCheckBox);
	//myTab->addItem(myCheckBox, myRow, myFromColumn, myToColumn);
	//connect(myCheckBox, SIGNAL(stateChanged(int)), this, SLOT(onStateChanged(int)));
}

void Boolean3OptionView::_onAccept() const {
	AppLog("Boolean3OptionView::_onAccept");
	/*
	ZLBoolean3 value = B3_UNDEFINED;
	switch (myCheckBox->checkState()) {
		case Qt::Checked:
			value = B3_TRUE;
			break;
		case Qt::Unchecked:
			value = B3_FALSE;
			break;
		case Qt::PartiallyChecked:
			value = B3_UNDEFINED;
			break;
	}
	((ZLBoolean3OptionEntry&)*myOption).onAccept(value);
	*/
}

void Boolean3OptionView::OnActionPerformed(int actionId)
{
	AppLog("Boolean3OptionView::OnActionPerformed");
    switch (actionId)
    {
	case ID_BUTTON_CHECKED:
	        // Todo:
	    	AppLog("BooleanOptionView::ID_BUTTON_CHECKED");
	    	//onStateChanged(true);
	        break;
	case ID_BUTTON_UNCHECKED:
	    	AppLog("BooleanOptionView::ID_BUTTON_UNCHECKED");
	    	//onStateChanged(false);
	        // Todo:
	        break;
    default:
        break;
    }
}
/*
void Boolean3OptionView::onStateChanged(int state) const {

	ZLBoolean3 value = B3_UNDEFINED;
	switch (state) {
		case Qt::Checked:
			value = B3_TRUE;
			break;
		case Qt::Unchecked:
			value = B3_FALSE;
			break;
		case Qt::PartiallyChecked:
			value = B3_UNDEFINED;
			break;
	}
	((ZLBoolean3OptionEntry&)*myOption).onStateChanged(value);

}*/

void ChoiceOptionView::_createItem() {
	AppLog(" ChoiceOptionView::_createItem()");

	myTab->form()->__pCustomList->AddGroup(String(ZLOptionView::name().c_str()), null);
	myTab->form()->GroupCount++;

	for (int i = 0; i < ((ZLChoiceOptionEntry&)*myOption).choiceNumber(); ++i) {
		AppLog(" i = %d",i);
		AppLog("choice title = %s",((ZLChoiceOptionEntry&)*myOption).text(i).c_str());
		OptionListItem* pItem = new OptionListItem(this);
	    pItem->Construct(100);
	    pItem->SetItemFormat(*myTab->form()->__pCustomListItemFormat2);
	    pItem->SetElement(ID_LIST_TEXT_TITLE,String(((ZLChoiceOptionEntry&)*myOption).text(i).c_str()));
		//    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
		//    pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
	    pItem->SetCheckBox(ID_LIST_CHECKBOX);
	    //pItem->SetElement(ID_FORMAT_CUSTOM, *(static_cast<ICustomListElement *>(__pListElement)));
		myTab->form()->__pCustomList->AddItem(myTab->form()->GroupCount-1, *pItem, ID_LIST_ITEM);

	}
}
/*
void ChoiceOptionView::_setActive(bool active) {
//	myGroupBox->setEnabled(active);
}
*/
void ChoiceOptionView::_onAccept() const {
/*	for (int i = 0; i < ((ZLChoiceOptionEntry&)*myOption).choiceNumber(); ++i) {
		if (myButtons[i]->isChecked()) {
			((ZLChoiceOptionEntry&)*myOption).onAccept(i);
			return;
		}
	}
*/
}

void ChoiceOptionView::OnActionPerformed(int actionId){
	AppLog("ChoiceOptionView::OnActionPerformed");
}




/*
class KeyLineEdit : public QLineEdit {

public:
	KeyLineEdit(KeyOptionView &keyView, QWidget *parent);

protected:
	void focusInEvent(QFocusEvent*);
	void focusOutEvent(QFocusEvent*);
	void keyPressEvent(QKeyEvent *keyEvent);

private:
	KeyOptionView &myKeyView;
};

KeyLineEdit::KeyLineEdit(KeyOptionView &keyView, QWidget *parent) : QLineEdit(parent), myKeyView(keyView) {
	focusOutEvent(0);
}

void KeyLineEdit::keyPressEvent(QKeyEvent *keyEvent) {
	std::string keyText = ZLQtKeyUtil::keyName(keyEvent);
	setText(keyText.c_str());
	if (!keyText.empty()) {
		myKeyView.myCurrentKey = keyText;
		myKeyView.myComboBox->setCurrentIndex(((ZLKeyOptionEntry&)*myKeyView.myOption).actionIndex(keyText));
		myKeyView.myComboBox->show();
	}
	((ZLKeyOptionEntry&)*myKeyView.myOption).onKeySelected(keyText);
}

void KeyLineEdit::focusInEvent(QFocusEvent*) {
	grabKeyboard();
}

void KeyLineEdit::focusOutEvent(QFocusEvent*) {
	releaseKeyboard();
}

void KeyOptionView::_createItem() {
	QWidget *widget = new QWidget(myTab->widget());
	QGridLayout *layout = new QGridLayout(widget);

	QLabel *label = new QLabel(widget);
	label->setText(::qtString(ZLResource::resource("keyOptionView")["actionFor"].value()));
	layout->addWidget(label, 0, 0);

	myKeyEditor = new KeyLineEdit(*this, widget);
	layout->addWidget(myKeyEditor, 0, 1);

	myWidgets.push_back(widget);
	myWidgets.push_back(label);
	myWidgets.push_back(myKeyEditor);

	myComboBox = new QComboBox(widget);
	const std::vector<std::string> &actions = ((ZLKeyOptionEntry&)*myOption).actionNames();
	for (std::vector<std::string>::const_iterator it = actions.begin(); it != actions.end(); ++it) {
		myComboBox->insertItem(it - actions.begin(), ::qtString(*it));
	}
	connect(myComboBox, SIGNAL(activated(int)), this, SLOT(onValueChanged(int)));
	layout->addWidget(myComboBox, 1, 0, 1, 2);
	myTab->addItem(widget, myRow, myFromColumn, myToColumn);
}

void KeyOptionView::reset() {
	if (myKeyEditor == 0) {
		return;
	}
	myCurrentKey.erase();
	myKeyEditor->setText("");
	((ZLKeyOptionEntry&)*myOption).onKeySelected(myCurrentKey);
	myComboBox->hide();
}

void KeyOptionView::_show() {
	ZLQtOptionView::_show();
	if (!myCurrentKey.empty()) {
		myComboBox->show();
	} else {
		myComboBox->hide();
	}
}

void KeyOptionView::_hide() {
	ZLQtOptionView::_hide();
	myComboBox->hide();
	myCurrentKey.erase();
	myKeyEditor->setText("");
	((ZLKeyOptionEntry&)*myOption).onKeySelected(myCurrentKey);
}

void KeyOptionView::_onAccept() const {
	((ZLKeyOptionEntry&)*myOption).onAccept();
}

void KeyOptionView::onValueChanged(int index) {
	if (!myCurrentKey.empty()) {
		((ZLKeyOptionEntry&)*myOption).onValueChanged(myCurrentKey, index);
	}
}
*/



