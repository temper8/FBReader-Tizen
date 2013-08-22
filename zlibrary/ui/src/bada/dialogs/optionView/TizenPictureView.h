/*
 * TizenPictureView.h
 *
 *  Created on: Aug 13, 2013
 *      Author: temper8
 */

#ifndef TIZENPICTUREVIEW_H_
#define TIZENPICTUREVIEW_H_

#include "ZLTizenOptionView.h"

class TizenPictureView: public ZLTizenOptionView,
						public Tizen::Ui::IActionEventListener {
public:

	TizenPictureView(const std::string &name, const std::string &tooltip, ZLPictureOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn), myActions(option->myActions) {}
	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);

protected:

	void _createItem();
	void _onAccept() const;
	shared_ptr<ZLImage> myImage;
	const  std::vector<shared_ptr<ZLRunnableWithKey> > &myActions;
	Tizen::Graphics::Bitmap* makeCover(Tizen::Graphics::Bitmap* srcBmp);
	void createActionButtons(Tizen::Ui::Controls::TableViewItem* pItem);

};

#endif /* TIZENPICTUREVIEW_H_ */
