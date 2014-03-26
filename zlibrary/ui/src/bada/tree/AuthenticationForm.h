/*
 * AuthenticationForm.h
 *
 *  Created on: Mar 25, 2014
 *      Author: Alex
 */

#ifndef AUTHENTICATIONFORM_H_
#define AUTHENTICATIONFORM_H_

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>

class AuthenticationForm :
	public Tizen::Ui::Controls::Form,
	 public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::Controls::IFormBackEventListener
{
public:
	AuthenticationForm();
	virtual ~AuthenticationForm();
	bool Initialize(void);

	result OnInitializing(void);
	result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	Tizen::Ui::Controls::Form*  myPreviousForm;
	void SetPreviousForm(Tizen::Ui::Controls::Form* form);
	Tizen::Base::String userName;
	Tizen::Base::String password;
private:
	Tizen::Ui::Controls::Label* userNameLabel;
	Tizen::Ui::Controls::EditField* userNameEditField;

	Tizen::Ui::Controls::Label* passwordLabel;
	Tizen::Ui::Controls::EditField* passwordEditField;
};

#endif /* AUTHENTICATIONFORM_H_ */
