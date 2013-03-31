/*
 * ZLBadaApplicationWindow.cpp
 *
 *  Created on: 11.10.2011
 *      Author: Alex
 */

#include "ZLbadaApplicationWindow.h"
#include "../view/ZLbadaViewWidget.h"
#include <ZLView.h>
#include "../library/ZLbadaLibraryImplementation.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::System;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;



void ZLbadaApplicationWindow::initMenu() {
	AppLog("ZLbadaApplicationWindow::initMenu() ");
	MenuBuilder(*this).processMenu(application());
}

ZLbadaApplicationWindow::MenuBuilder::MenuBuilder(ZLbadaApplicationWindow &window) : myWindow(window) {
	//myMenuStack.push(myWindow.myMenu);
}

void ZLbadaApplicationWindow::MenuBuilder::processSubmenuBeforeItems(ZLMenubar::Submenu &submenu) {
	AppLog("ZLbadaApplicationWindow:::MenuBuilder::processSubmenuBeforeItems ");

}

void ZLbadaApplicationWindow::MenuBuilder::processSubmenuAfterItems(ZLMenubar::Submenu&) {
	//myMenuStack.pop();
}

void ZLbadaApplicationWindow::MenuBuilder::processItem(ZLMenubar::PlainItem &item) {
	AppLog("MenuBuilder::processItem actionId=%s name=%s",item.actionId().c_str(),item.name().c_str());
	const std::string &id = item.actionId();
	const std::string &name = item.name();
	shared_ptr<ZLApplication::Action> action = myWindow.application().action(id);
	myWindow.myViewWidget->mybadaForm->AddMenuItem(name, id);
	//__pOptionMenu->AddItem(item.name().c_str(),200);
	//__pOptionMenu->AddItem("Библиотека",ID_OPTIONMENU_ITEM1);

	/*GtkWidget *gtkItem = gtk_button_new_with_label(item.name().c_str());

	if (!action.isNull()) {
		ZLGtkSignalUtil::connectSignalAfter(GTK_OBJECT(gtkItem), "clicked", G_CALLBACK(menuActionSlot), &*action);
	}
	myWindow.myMenuItems[id] = gtkItem;
	hildon_app_menu_append(myWindow.myMenu, GTK_BUTTON(gtkItem));
	gtk_widget_show_all(GTK_WIDGET(gtkItem));*/
}

void ZLbadaApplicationWindow::MenuBuilder::processSepartor(ZLMenubar::Separator&) {
}



void ZLbadaApplicationWindow::processAllEvents(){
	AppLog("ZLbadaApplicationWindow::processAllEvents ");
}

void ZLbadaApplicationWindow::setToolbarItemState(ZLToolbar::ItemPtr item, bool visible, bool enabled) {
//	AppLog("setToolbarItemState ");
/*	QAction *action = myActions[&*item];
	if (action != 0) {
		action->setEnabled(enabled);
		action->setVisible(visible);
	}*/
	switch (item->type()) {
		default:
			break;
		case ZLToolbar::Item::MENU_BUTTON:
			//AppLog("MENU_BUTTON ");
			/*{


			ZLToolbar::MenuButtonItem &buttonItem = (ZLToolbar::MenuButtonItem&)*item;
			shared_ptr<ZLPopupData> data = buttonItem.popupData();
			if (!data.isNull() && (data->id() != myPopupIdMap[&buttonItem])) {
				myPopupIdMap[&buttonItem] = data->id();
				QToolButton *button = myMenuButtons[&buttonItem];
				QMenu *menu = button->menu();
				menu->clear();
				const size_t count = data->count();
				for (size_t i = 0; i < count; ++i) {
					menu->addAction(new ZLQtRunPopupAction(menu, data, i));
				}
			}*/
			break;
		}

}

void ZLbadaApplicationWindow::addToolbarItem(ZLToolbar::ItemPtr item) {
	//QToolBar *tb = toolbar(type(*item));
	//QAction *action = 0;
	AppLog("addToolbarItem ");
	switch (item->type()) {
		case ZLToolbar::Item::PLAIN_BUTTON:
		case ZLToolbar::Item::TOGGLE_BUTTON:
		//	AppLog("TOGGLE_BUTTON ");//,(ZLToolbar::AbstractButtonItem&)*item.tooltip().c_str());

			//action = new ZLQtToolBarAction(this, (ZLToolbar::AbstractButtonItem&)*item);
			//tb->addAction(action);
			break;
		case ZLToolbar::Item::MENU_BUTTON:
		{
		//	AppLog("MENU_BUTTON ");

			/*ZLToolbar::MenuButtonItem &buttonItem = (ZLToolbar::MenuButtonItem&)*item;
			QToolButton *button = new QToolButton(tb);
			button->setFocusPolicy(Qt::NoFocus);
			button->setDefaultAction(new ZLQtToolBarAction(this, buttonItem));
			button->setMenu(new QMenu(button));
			button->setPopupMode(QToolButton::MenuButtonPopup);
			action = tb->addWidget(button);
			myMenuButtons[&buttonItem] = button;
			shared_ptr<ZLPopupData> popupData = buttonItem.popupData();
			myPopupIdMap[&buttonItem] =
				popupData.isNull() ? (size_t)-1 : (popupData->id() - 1);*/
			break;
		}
		case ZLToolbar::Item::TEXT_FIELD:
		case ZLToolbar::Item::SEARCH_FIELD:
		{
		//	AppLog("SEARCH_FIELD ");
		/*	ZLToolbar::ParameterItem &textFieldItem =
				(ZLToolbar::ParameterItem&)*item;
			LineEditParameter *para = new LineEditParameter(tb, *this, textFieldItem);
			addVisualParameter(textFieldItem.parameterId(), para);
			action = para->action();*/
			break;
		}
		case ZLToolbar::Item::SEPARATOR:
		//	AppLog("SEPARATOR ");
			//action = tb->addSeparator();
			break;
	}

	//if (action != 0) {
	//	myActions[&*item] = action;
	//}
}



void ZLbadaApplicationWindow::setCaption(const std::string &caption){
	AppLog("SetCaption %s",caption.c_str());
}

void ZLbadaApplicationWindow::setToggleButtonState(const ZLToolbar::ToggleButtonItem &button) {
	AppLog("setToggleButtonState %s",button.actionId().c_str());

	//myActions[&button]->setChecked(button.isPressed());
}


ZLbadaApplicationWindow::ZLbadaApplicationWindow(ZLApplication *a): ZLApplicationWindow(a) {
	// TODO Auto-generated constructor stub

	AppLog("ZLbadaApplicationWindow");
}

ZLbadaApplicationWindow::~ZLbadaApplicationWindow() {
	// TODO Auto-generated destructor stub
}



ZLViewWidget *ZLbadaApplicationWindow::createViewWidget() {

	AppLog("createViewWidget");
	ZLView::Angle Angle = ZLView::DEGREES0;// application().AngleStateOption.value();
	myViewWidget = new ZLbadaViewWidget(Angle);

	// Create a form
	//badaForm *pbadaForm = new badaForm(*myViewWidget);
	//pbadaForm->Initialize();
	badaForm &pbadaForm = badaForm::Instance();
	pbadaForm.Initialize(myViewWidget);
	//pbadaForm->SetOrientation(ORIENTATION_PORTRAIT_REVERSE );

	// Add the form to the frame
	ZLbadaLibraryImplementation::myBadaApp->TestTest();
	//Frame *pFrame = ZLbadaLibraryImplementation::myBadaApp->GetAppFrame()->GetFrame();
	//pFrame->AddControl(*pbadaForm);
	AppLog("pFrame->AddControl(*pbadaForm)");

	// Set the current form
	//pFrame->SetCurrentForm(*pbadaForm);
	AppLog("SetCurrentForm(*pbadaForm)");
	myViewWidget->mybadaForm = &pbadaForm;
	myViewWidget->myWindows = this;


//	QVBoxLayout *layout = new QVBoxLayout(main);
//	layout->addWidget(viewWidget->widget(), 1);

//	myRightButtonResource = CLOSE_BUTTON;
//	myCST = new UTIL_CST(main, ZLibrary::ApplicationName().c_str(), "CST_Menu", myRightButtonResource);
//	myCST->setFixedSize(ZGlobal::getCstR().size());
	//layout->addWidget(myCST);
//	myCST->getLeftBtn()->setPopup(myMenu);
//	myMainWindow->connectCSTButtons(myCST);

	//myMainWindow->setCentralWidget(main);
	return myViewWidget;
}
