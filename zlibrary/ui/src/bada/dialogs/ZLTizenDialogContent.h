/*
 * ZLTizenDialogContent.h
 *
 *  Created on: Jul 19, 2013
 *      Author: Alex
 */

#ifndef ZLTIZENDIALOGCONTENT_H_
#define ZLTIZENDIALOGCONTENT_H_

#include "ZLDialogContent.h"

class TizenDialogForm;

class ZLTizenDialogContent: public ZLDialogContent {
public:
	ZLTizenDialogContent(TizenDialogForm *form, const ZLResource &resource);
	virtual ~ZLTizenDialogContent();

	void addOption(const std::string &name, const std::string &tooltip, ZLOptionEntry *option);
	void addOptions(const std::string &name0, const std::string &tooltip0, ZLOptionEntry *option0,
									const std::string &name1, const std::string &tooltip1, ZLOptionEntry *option1);

	//void addItem(DialogForm *form, int row, int fromColumn, int toColumn);

	void close();

private:
	void createViewByEntry(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, int fromColumn, int toColumn);
	TizenDialogForm *myForm;

};

#endif /* ZLTIZENDIALOGCONTENT_H_ */