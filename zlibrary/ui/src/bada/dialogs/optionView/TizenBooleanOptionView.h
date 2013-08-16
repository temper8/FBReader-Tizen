/*
 * TizenBooleanOptionView.h
 *
 *  Created on: Aug 12, 2013
 *      Author: temper8
 */

#ifndef TIZENBOOLEANOPTIONVIEW_H_
#define TIZENBOOLEANOPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenBooleanOptionView: public ZLTizenOptionView {
public:

	TizenBooleanOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}
	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual void OnStateChanged(Tizen::Ui::Controls::TableViewItemStatus status);

protected:
	void _createItem();
	void _onAccept() const;
};

#endif /* TIZENBOOLEANOPTIONVIEW_H_ */
