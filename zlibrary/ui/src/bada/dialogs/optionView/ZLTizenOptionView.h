/*
 * ZLTizenOptionView.h
 *
 *  Created on: Aug 8, 2013
 *      Author: temper8
 */

#ifndef ZLTIZENOPTIONVIEW_H_
#define ZLTIZENOPTIONVIEW_H_

#include "../../../../../core/src/dialogs/ZLOptionView.h"
#include "../ZLTizenDialogContent.h"
#include <FUi.h>

class ZLTizenOptionView: public ZLOptionView {
protected:
	ZLTizenOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLOptionView(name, tooltip, option), myTab(tab), myRow(row), myFromColumn(fromColumn), myToColumn(toColumn) {}
//	virtual ~ZLTizenOptionView();

	void _show();
	void _hide();
	void _setActive(bool active);

protected:
	int groupIndex;
	int itemIndex;
	int myRow, myFromColumn, myToColumn;
public :
	std::string myCaption; 
	ZLTizenDialogContent *myTab;
	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight) = 0;

	//virtual void OnActionPerformed(int actionId) = 0;
};

#endif /* ZLTIZENOPTIONVIEW_H_ */
