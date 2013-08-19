/*
 * TizenSpinOptionView.h
 *
 *  Created on: Aug 16, 2013
 *      Author: temper8
 */

#ifndef TIZENSPINOPTIONVIEW_H_
#define TIZENSPINOPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenSpinOptionView:  public ZLTizenOptionView,
							public Tizen::Ui::IAdjustmentEventListener {
public:

	TizenSpinOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}
	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual void OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment);

protected:
	int minValue;
	int maxValue;
	void _createItem();
	void _onAccept() const;
};

#endif /* TIZENSPINOPTIONVIEW_H_ */
