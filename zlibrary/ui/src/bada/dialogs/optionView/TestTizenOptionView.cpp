/*
 * TestTizenOptionView.cpp
 *
 *  Created on: Aug 8, 2013
 *      Author: temper8
 */

#include "TestTizenOptionView.h"



void TestTizenOptionView::_createItem() {
//	std::string myText = ((ZLStaticTextOptionEntry&)*myOption).initialValue();
//	const char *text = myText.c_str();
	 myCaption = ZLOptionView::name()+ ": 123";

}

void TestTizenOptionView::_onAccept() const {

}
