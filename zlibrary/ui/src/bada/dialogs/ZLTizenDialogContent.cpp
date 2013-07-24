/*
 * ZLTizenDialogContent.cpp
 *
 *  Created on: Jul 19, 2013
 *      Author: Alex
 */

#include <FBase.h>

#include "ZLTizenDialogContent.h"

ZLTizenDialogContent::ZLTizenDialogContent(TizenDialogForm *form, const ZLResource &resource) : ZLDialogContent(resource), myForm(form) {
	// TODO Auto-generated constructor stub


}

ZLTizenDialogContent::~ZLTizenDialogContent() {
	// TODO Auto-generated destructor stub
}

void ZLTizenDialogContent::addOption(const std::string &name, const std::string &tooltip, ZLOptionEntry *option) {
	AppLog("addOption %s %s",name.c_str(),tooltip.c_str());
	createViewByEntry(name, tooltip, option, 0, 12);

}

void ZLTizenDialogContent::addOptions(const std::string &name0, const std::string &tooltip0, ZLOptionEntry *option0,
								const std::string &name1, const std::string &tooltip1, ZLOptionEntry *option1) {

	AppLog("addOptions0 %s %s",name0.c_str(), tooltip0.c_str());
	AppLog("addOptions1 %s %s",name1.c_str(), tooltip1.c_str());
	createViewByEntry(name0, tooltip0, option0, 0, 5);
	createViewByEntry(name1, tooltip1, option1, 7, 12);
}

/*void ZLTizenDialogContent::addItem(DialogForm *form, int row, int fromColumn, int toColumn) {

}*/

void ZLTizenDialogContent::close() {

}


void ZLTizenDialogContent::createViewByEntry(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, int fromColumn, int toColumn) {

}
