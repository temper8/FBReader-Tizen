/*
 * ZLTizenOptionsDialog.h
 *
 *  Created on: Jul 23, 2013
 *      Author: Alex
 */

#ifndef ZLTIZENOPTIONSDIALOG_H_
#define ZLTIZENOPTIONSDIALOG_H_

#include "ZLOptionsDialog.h"
#include "TizenDialogForm.h"

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>

class ZLTizenOptionsDialog: public ZLOptionsDialog {

public:
	ZLTizenOptionsDialog(Tizen::Ui::Controls::Form  *PreviousForm, const ZLResource &resource, shared_ptr<ZLRunnable> applyAction, bool showApplyButton);
	virtual ~ZLTizenOptionsDialog();

public:
	virtual ZLDialogContent &createTab(const ZLResourceKey &key);
	virtual bool run();
    virtual void setMenuEntry(ZLMenuOptionEntry* option);
    TizenDialogForm *myDialogForm;
	void apply();

protected:
//	MenuView* myMenuView;
//	Tizen::Ui::Controls::Form   &myPreviousForm;
	virtual const std::string &selectedTabKey() const;
	virtual void selectTab(const ZLResourceKey &key);
	virtual bool runInternal() {}

};

#endif /* ZLTIZENOPTIONSDIALOG_H_ */
