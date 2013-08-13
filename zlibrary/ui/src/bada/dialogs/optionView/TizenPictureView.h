/*
 * TizenPictureView.h
 *
 *  Created on: Aug 13, 2013
 *      Author: temper8
 */

#ifndef TIZENPICTUREVIEW_H_
#define TIZENPICTUREVIEW_H_

#include "ZLTizenOptionView.h"

class TizenPictureView: public ZLTizenOptionView {
public:

	TizenPictureView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}
	virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);

protected:
	void _createItem();
	void _onAccept() const;
	shared_ptr<ZLImage> myImage;
	Tizen::Graphics::Bitmap* makeCover(Tizen::Graphics::Bitmap* srcBmp);
};

#endif /* TIZENPICTUREVIEW_H_ */
