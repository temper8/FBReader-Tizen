/*
 * Copyright (C) 2004-2010 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#ifndef __ZLBADADIALOGCONTENT_H__
#define __ZLBADADIALOGCONTENT_H__

#include "../../../../core/src/dialogs/ZLOptionsDialog.h"

//class QWidget;
class DialogForm;

class ZLbadaDialogContent : public ZLDialogContent {

public:
	ZLbadaDialogContent(DialogForm *form, const ZLResource &resource);
	~ZLbadaDialogContent();

	void addOption(const std::string &name, const std::string &tooltip, ZLOptionEntry *option);
	void addOptions(const std::string &name0, const std::string &tooltip0, ZLOptionEntry *option0,
									const std::string &name1, const std::string &tooltip1, ZLOptionEntry *option1);

	void addItem(DialogForm *form, int row, int fromColumn, int toColumn);

	void close();
	DialogForm *form();
//	QWidget *parentWidget();

private:
	void createViewByEntry(const std::string &name, const std::string &tooltip, ZLOptionEntry *option, int fromColumn, int toColumn);

private:
	DialogForm *myForm;
//	QGridLayout *myLayout;
	int myRowCounter;
//	QWidget *myParentWidget;
};

#endif /* __ZLBADADIALOGCONTENT_H__ */
