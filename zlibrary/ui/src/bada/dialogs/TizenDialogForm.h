/*
 * TizenDialogForm.h
 *
 *  Created on: Jul 23, 2013
 *      Author: Alex
 */

#ifndef TIZENDIALOGFORM_H_
#define TIZENDIALOGFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>

#include <FContent.h>


#include <ZLOptionsDialog.h>

class TizenDialogForm :
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::Controls::IFormBackEventListener {
public:
	TizenDialogForm();
	virtual ~TizenDialogForm();

public:
	bool Initialize(const char *title, bool showApplyButton);
	void SetPreviousForm(Tizen::Ui::Controls::Form* preForm);

	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

public:

	Tizen::Ui::Controls::Form*	pPreviousForm;
	shared_ptr<ZLOptionsDialog> __badaOptionsDialog;

protected:
	bool showApplyButton;

};

#endif /* TIZENDIALOGFORM_H_ */
