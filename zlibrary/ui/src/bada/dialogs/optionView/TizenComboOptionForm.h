/*
 * TizenComboOptionForm.h
 *
 *  Created on: Aug 17, 2013
 *      Author: Alex
 */

#ifndef TIZENCOMBOOPTIONFORM_H_
#define TIZENCOMBOOPTIONFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>

class TizenComboOptionForm :
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::Controls::IFormBackEventListener{
public:
	TizenComboOptionForm();
	virtual ~TizenComboOptionForm();

	void Initialize();
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);
	Tizen::Ui::Controls::Form*	pPreviousForm;
};

#endif /* TIZENCOMBOOPTIONFORM_H_ */
