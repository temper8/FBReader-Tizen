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

//#include <QtGui/QApplication>
//#include <QtGui/QDesktopWidget>
//#include <QtGui/QWidget>
//#include <QtGui/QLayout>

#include "ZLbadaDialogContent.h"
#include <FBase.h>
#include "optionView/ZLbadaOptionView.h"

void ZLbadaDialogContent::close() {
//	myLayout->setRowStretch(myRowCounter, 10);
}

ZLbadaDialogContent::ZLbadaDialogContent(DialogForm *form, const ZLResource &resource) : ZLDialogContent(resource), myForm(form) {
	AppLog("ZLbadaDialogContent::ZLbadaDialogContent");
	//myLayout = new QGridLayout(myWidget);
	myRowCounter = 0;
}

ZLbadaDialogContent::~ZLbadaDialogContent() {
	AppLog("ZLbadaDialogContent::~ZLbadaDialogContent");
}

void ZLbadaDialogContent::addOption(const std::string &name, const std::string &tooltip, ZLOptionEntry *option) {
	AppLog("addOption %s %s",name.c_str(),tooltip.c_str());
	createViewByEntry(name, tooltip, option, 0, 12);
	++myRowCounter;
}

void ZLbadaDialogContent::addOptions(const std::string &name0, const std::string &tooltip0, ZLOptionEntry *option0, const std::string &name1, const std::string &tooltip1, ZLOptionEntry *option1) {
	AppLog("addOptions0 %s %s",name0.c_str(), tooltip0.c_str());
	AppLog("addOptions1 %s %s",name1.c_str(), tooltip1.c_str());
	createViewByEntry(name0, tooltip0, option0, 0, 5);
	createViewByEntry(name1, tooltip1, option1, 7, 12);
//	++myRowCounter;
}

void ZLbadaDialogContent::addItem(DialogForm *form, int row, int fromColumn, int toColumn) {
	AppLog("addItem  row=%d fromColumn=%d toColumn=%d",row,fromColumn,toColumn);
	//myLayout->addWidget(widget, row, fromColumn, 1, toColumn - fromColumn + 1);
}

void ZLbadaDialogContent::createViewByEntry(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, int fromColumn, int toColumn) {
	AppLog("createViewByEntry ");
	if (option == 0) {
		return;
	}
	ZLbadaOptionView *view = 0;
	AppLog("createViewByEntry switch");
	switch (option->kind()) {
		case ZLOptionEntry::BOOLEAN:
			AppLog("ZLOptionEntry::BOOLEAN:");
			view = new BooleanOptionView(name, tooltip, (ZLBooleanOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::BOOLEAN3:
			AppLog("ZLOptionEntry::BOOLEAN3:");
			view = new Boolean3OptionView(name, tooltip, (ZLBoolean3OptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::STRING:
			AppLog("ZLOptionEntry::STRING:");
			view = new StringOptionView(name, tooltip, (ZLStringOptionEntry*)option, this, false, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::PASSWORD:
			AppLog("ZLOptionEntry::PASSWORD:");
			//view = new StringOptionView(name, tooltip, (ZLStringOptionEntry*)option, this, true, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::CHOICE:
			AppLog("ZLOptionEntry::CHOICE:");
			view = new ChoiceOptionView(name, tooltip, (ZLChoiceOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::SPIN:
			AppLog("ZLOptionEntry::SPIN:");
			view = new SpinOptionView(name, tooltip, (ZLSpinOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::COMBO:
			AppLog("ZLOptionEntry::COMBO:");
			view = new ComboOptionView(name, tooltip, (ZLComboOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::COLOR:
			AppLog("ZLOptionEntry::COLOR:");
			view = new ColorOptionView(name, tooltip, (ZLColorOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::KEY:
			AppLog("ZLOptionEntry::KEY:");
			//view = new KeyOptionView(name, tooltip, (ZLKeyOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::ORDER:
			AppLog("ZLOptionEntry::ORDER:");
			//view = new OrderOptionView(name, tooltip, (ZLOrderOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
		case ZLOptionEntry::STATIC:
			AppLog("ZLOptionEntry::STATIC:");
			  view = new StaticTextOptionView(name, tooltip, (ZLStaticTextOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
			break;
    	case ZLOptionEntry::PICTURE:
		    view = new PictureView(name, tooltip, (ZLPictureOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
		    break;
    	case ZLOptionEntry::BUTTON:
    		AppLog("ZLOptionEntry::BUTTON");
    		    view = new ButtonView(name, tooltip, (ZLButtonOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
    		    break;
    	case ZLOptionEntry::MENU:
    		AppLog("ZLOptionEntry::MENU");
    		    view = new MenuView(name, tooltip, (ZLMenuOptionEntry*)option, this, myRowCounter, fromColumn, toColumn);
    		    break;
	}

	if (view != 0) {
		view->setVisible(option->isVisible());
		addView(view);
	}
}

DialogForm *ZLbadaDialogContent::form() {
	return myForm;
}
