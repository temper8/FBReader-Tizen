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

#ifndef __ZLBADADIALOGMANAGER_H__
#define __ZLBADADIALOGMANAGER_H__

#include <ZLDialogManager.h>

class ZLApplication;
class ZLbadaApplicationWindow;
class ZLbadaOptionsDialog;

class ZLbadaDialogManager : public ZLDialogManager {

public:
	static void createInstance() { ourInstance = new ZLbadaDialogManager(); }
	static ZLbadaDialogManager* badaInstance();
private:
	ZLbadaDialogManager() {}

public:
	void createApplicationWindow(ZLApplication *application) const ;

	shared_ptr<ZLDialog> createDialog(const ZLResourceKey &key) const;
	shared_ptr<ZLOptionsDialog> createOptionsDialog(const ZLResourceKey &key, shared_ptr<ZLRunnable> applyAction, bool showApplyButton) const;
	shared_ptr<ZLOpenFileDialog> createOpenFileDialog(const ZLResourceKey &key, const std::string &directoryPath, const std::string &filePath, const ZLOpenFileDialog::Filter &filter) const;
	void startOpenFileDialog() const;

	shared_ptr<ZLTreeDialog> createTreeDialog(const ZLResourceKey &key) const;
	static void deleteTreeDialog();
	shared_ptr<ZLDialogContent> createContent(const ZLResourceKey &key) const;

	void informationBox(const std::string &title, const std::string &message) const;
	void errorBox(const ZLResourceKey &key, const std::string &message) const;
	int questionBox(const ZLResourceKey &key, const std::string &message, const ZLResourceKey &button0, const ZLResourceKey &button1, const ZLResourceKey &button2) const;
	shared_ptr<ZLProgressDialog> createProgressDialog(const ZLResourceKey &key) const;

	bool isClipboardSupported(ClipboardType type) const { return false; }
	void setClipboardText(const std::string &text, ClipboardType type) const {}
	void setClipboardImage(const ZLImageData &imageData, ClipboardType type) const {}
private:
	mutable ZLbadaApplicationWindow *myApplicationWindow;
	static shared_ptr<ZLTreeDialog> myTreeDialog;
	mutable shared_ptr<ZLOptionsDialog> mybadaOptionsDialog;
	//mutable ZLOptionsDialog* mybadaOptionsDialog;
};

#endif /* __ZLBADADIALOGMANAGER_H__ */
