/*
 * TizenComboOptionView.h
 *
 *  Created on: Aug 16, 2013
 *      Author: temper8
 */

#ifndef TIZENCOMBOOPTIONVIEW_H_
#define TIZENCOMBOOPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenComboOptionView: public ZLTizenOptionView {
public:

	TizenComboOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}
	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual void OnStateChanged(Tizen::Ui::Controls::TableViewItemStatus status);

protected:
	Tizen::Base::String comboValue;
	void _createItem();
	void _onAccept() const;
};

#endif /* TIZENCOMBOOPTIONVIEW_H_ */
