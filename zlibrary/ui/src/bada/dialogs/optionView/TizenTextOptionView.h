/*
 * TizenTextOptionView.h
 *
 *  Created on: Aug 12, 2013
 *      Author: temper8
 */

#ifndef TIZENTEXTOPTIONVIEW_H_
#define TIZENTEXTOPTIONVIEW_H_

#include "ZLTizenOptionView.h"

class TizenTextOptionView: public ZLTizenOptionView {
	public:

		TizenTextOptionView(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, ZLTizenDialogContent *tab, int row, int fromColumn, int toColumn) : ZLTizenOptionView(name, tooltip, option, tab, row, fromColumn, toColumn) {}
		virtual Tizen::Ui::Controls::TableViewItem* createTableViewItem(int itemWidth, int defaultItemHeight);

	protected:
		void _createItem();
		void _onAccept() const;

		int textHeight;
		Tizen::Base::String myText;
		Tizen::Graphics::EnrichedText* pEnrichedText;
		void addParagraph(std::string &text);
		int initText(const char *caption, std::string &text,  int height);
};

#endif /* TIZENTEXTOPTIONVIEW_H_ */
