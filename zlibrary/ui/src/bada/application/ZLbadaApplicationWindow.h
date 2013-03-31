/*
 * ZLBadaApplicationWindow.h
 *
 *  Created on: 11.10.2011
 *      Author: Alex
 */

#ifndef ZLBADAAPPLICATIONWINDOW_H_
#define ZLBADAAPPLICATIONWINDOW_H_
#include <FBase.h>
#include <FUi.h>
#include "ZLApplicationWindow.h"
#include "../../../../core/src/application/ZLMenu.h"
#include "../view/badaApp.h"

class ZLbadaViewWidget;

class ZLbadaApplicationWindow: public ZLApplicationWindow {
public:
	ZLbadaApplicationWindow(ZLApplication *application);
	~ZLbadaApplicationWindow();

private:

	class MenuBuilder : public ZLMenuVisitor {

	public:
		MenuBuilder(ZLbadaApplicationWindow &window);

	private:
		void processSubmenuBeforeItems(ZLMenubar::Submenu &submenu);
		void processSubmenuAfterItems(ZLMenubar::Submenu &submenu);
		void processItem(ZLMenubar::PlainItem &item);
		void processSepartor(ZLMenubar::Separator &separator);

	private:
		ZLbadaApplicationWindow &myWindow;
	};
	void initMenu();

protected:

	virtual void processAllEvents();

	virtual void setToolbarItemState(ZLToolbar::ItemPtr item, bool visible, bool enabled);
	virtual void addToolbarItem(ZLToolbar::ItemPtr item);

private:
	ZLbadaViewWidget *myViewWidget;

public:

	ZLbadaViewWidget &viewWidget() const;
	badaApp*  myBadaApp;
	ZLViewWidget *createViewWidget();

	virtual void setCaption(const std::string &caption);
	virtual void setToggleButtonState(const ZLToolbar::ToggleButtonItem &toggleButton);

	friend class MenuBuilder;
};

inline ZLbadaViewWidget &ZLbadaApplicationWindow::viewWidget() const { return *myViewWidget; }

#endif /* ZLBADAAPPLICATIONWINDOW_H_ */
