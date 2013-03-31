/*
 * MenuView.cpp
 *
 *  Created on: 12.04.2012
 *      Author: Alex
 */

#include "ZLbadaOptionView.h"
#include "ZLOptionEntry.h"

MenuView::MenuView(const std::string &name, const std::string &tooltip, ZLMenuOptionEntry *option, ZLbadaDialogContent *tab,int row,int fromColumn,int  toColumn) : ZLbadaOptionView(name, tooltip, option, tab, row, fromColumn, toColumn), myActions(option->myActions) {
	 AppLog("MenuView::MenuView");

     AppLog("MenuView::MenuView 2");
}
MenuView::~MenuView(){
	AppLog("MenuView::~MenuView()");
}
