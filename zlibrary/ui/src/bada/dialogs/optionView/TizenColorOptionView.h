/*
 * TizenColorOptionView.h
 *
 *  Created on: Aug 21, 2013
 *      Author: temper8
 */

#ifndef TIZENCOLOROPTIONVIEW_H_
#define TIZENCOLOROPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenColorOptionView:	public ZLTizenOptionView,
							public Tizen::Ui::IAdjustmentEventListener,
							public Tizen::Ui::IActionEventListener {
public:

	TizenColorOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}

	virtual void OnStateChanged(Tizen::Ui::Controls::TableViewItemStatus status);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	void OnAdjustmentValueChanged(const Tizen::Ui::Control& source, int adjustment);

	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);

protected:
	Tizen::Ui::Controls::Slider* sliderR;
	Tizen::Ui::Controls::Slider* sliderG;
	Tizen::Ui::Controls::Slider* sliderB;
	Tizen::Ui::Controls::Panel*  panelColor;
	Tizen::Ui::Controls::Popup* __pPopup;
	void CreateColorPopup(void);
	ZLColor tmpColor;
	ZLColor myColor;
	void _createItem();
	void _onAccept() const;
};

#endif /* TIZENCOLOROPTIONVIEW_H_ */
