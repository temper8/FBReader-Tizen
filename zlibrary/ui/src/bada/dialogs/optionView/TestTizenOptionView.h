/*
 * TestTizenOptionView.h
 *
 *  Created on: Aug 8, 2013
 *      Author: temper8
 */

#ifndef TESTTIZENOPTIONVIEW_H_
#define TESTTIZENOPTIONVIEW_H_

#include "ZLTizenOptionView.h"


class TestTizenOptionView: public ZLTizenOptionView {
public:
	
	TestTizenOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}
	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);

protected:
	void _createItem();
	void _onAccept() const;
};

#endif /* TESTTIZENOPTIONVIEW_H_ */
