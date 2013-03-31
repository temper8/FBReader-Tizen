/*
 * OpenFileForm.h
 *
 *  Created on: 15.11.2011
 *      Author: Alex
 */

#ifndef OPENFILEFORM_H_
#define OPENFILEFORM_H_

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FContent.h>

class OpenFileForm :
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::IActionEventListener,
    public Tizen::Ui::IItemEventListener,
    public Tizen::Ui::IAnimationEventListener,
    public Tizen::Base::Runtime::IRunnable
{
public:
	OpenFileForm();
	~OpenFileForm();
	bool Initialize(void);

protected:
	// Ui
	Object* Run(void);
	static const int ID_SEARCH_DONE			= 300;

	Tizen::Ui::Controls::Form*			pPreviousForm;
	Tizen::Ui::Controls::Button*			pBtnClose;
	Tizen::Ui::Controls::List*			__pLstSearchList;
	Tizen::Ui::Controls::Popup*			__pCommonPopup;

	Tizen::Base::Collection::IList*				__pLstContentType;
	Tizen::Base::Collection::IList*				__pLstContentInfo;
	Tizen::Content::ContentType					__ContentType;

	Tizen::Ui::Controls::Popup*			__pProgressPopup;
	Tizen::Base::Runtime::Thread* 		__pThread;
	Tizen::Ui::Controls::Animation* 		__pAnimation;
	Tizen::Base::Collection::ArrayList* 	__pAnimationFrameList;


	void    _ClearContentInfoList();

public:


	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
    void 	OnItemStateChanged(const Tizen::Ui::Control &source, int index, int itemId, Tizen::Ui::ItemStatus status);
	virtual void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);
	virtual void OnAnimationStopped(const Tizen::Ui::Control& source);


	void	SetPreviousForm(Tizen::Ui::Controls::Form* preForm);
	void	LoadContentInfo(Tizen::Content::ContentSearchResult* pSearchResult);
    void    StartSearch();
	void 	ShowProgressPopup(const bool show);
	void	UpdateContent();
	void	DeleteContent();

};

#endif /* OPENFILEFORM_H_ */
