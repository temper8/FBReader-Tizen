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

//#include <qvbox.h>
//#include <qpushbutton.h>
#include <FBase.h>
#include <ZLDialogManager.h>
#include "ZLbadaDialog.h"

//#include "ZLQtDialog.h"
//#include "ZLQtDialogContent.h"
//#include "ZLQtUtil.h"

ZLbadaDialog::ZLbadaDialog(const ZLResource &resource) /*: QDialog(0, 0, true)*/ {
	AppLog(" ZLbadaDialog::ZLbadaDialog()");
	/*
	setCaption(::qtString(resource[ZLDialogManager::DIALOG_TITLE].value()));

	QVBoxLayout *layout = new QVBoxLayout(this);
	QWidget *widget = new QVBox(this);
	layout->add(widget);
	myTab = new ZLQtDialogContent(widget, resource);

	myButtonGroup = new QButtonGroup(this);
	layout->add(myButtonGroup);
	myButtonLayout = new QGridLayout(myButtonGroup, 1, 0, 8, 6);
	*/
}


ZLbadaDialog::~ZLbadaDialog() {
}

void ZLbadaDialog::addButton(const ZLResourceKey &key, bool accept) {
	AppLog(" ZLbadaDialog::addButton()");
/*	QPushButton *button = new QPushButton(myButtonGroup);
	button->setText(::qtButtonName(key));
	myButtons.push_back(button);
	myButtonLayout->addWidget(button, 0, myButtons.size());
	connect(button, SIGNAL(clicked()), this, accept ? SLOT(accept()) : SLOT(reject()));*/
}

bool ZLbadaDialog::run() {
	AppLog(" ZLbadaDialog::run()");

	/*QSize maxSize(0, 0);
	for (std::vector<QButton*>::const_iterator it = myButtons.begin(); it != myButtons.end(); ++it) {
		QSize buttonSize = (*it)->sizeHint();
		maxSize = QSize(
			std::max(maxSize.width(), buttonSize.width()),
			std::max(maxSize.height(), buttonSize.height())
		);	
	}
	for (std::vector<QButton*>::iterator it = myButtons.begin(); it != myButtons.end(); ++it) {
		(*it)->setFixedSize(maxSize);
	}
	((ZLQtDialogContent*)myTab)->close();
	return exec();*/
	return true;
}

