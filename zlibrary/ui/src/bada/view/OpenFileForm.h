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
	public Tizen::Ui::Controls::IFormBackEventListener,
	public Tizen::Ui::IActionEventListener,
//    public Tizen::Ui::IItemEventListener,
    public Tizen::Ui::IAnimationEventListener,
    public Tizen::Base::Runtime::IRunnable,
    public Tizen::Ui::Controls::IListViewItemEventListener,
    public Tizen::Ui::Controls::IListViewItemProvider
{
public:
	OpenFileForm();
	~OpenFileForm();
	bool Initialize(void);

protected:
	// Ui

	Object* Run(void);
	static const int ID_SEARCH_START		= 301;
	static const int ID_SEARCH_DONE			= 300;

	Tizen::Ui::Controls::Form*			pPreviousForm;
	Tizen::Ui::Controls::Button*			pBtnClose;
	Tizen::Ui::Controls::ListView*			__pLstSearchList;
	Tizen::Ui::Controls::Popup*			__pCommonPopup;

	Tizen::Base::Collection::IList*				__pLstContentType;
	Tizen::Base::Collection::IList*				__pLstContentInfo;
	Tizen::Content::ContentType					__ContentType;

	Tizen::Ui::Controls::Popup*			__pProgressPopup;
	Tizen::Base::Runtime::Thread* 		__pThread;
	Tizen::Ui::Controls::Animation* 		__pAnimation;
	Tizen::Base::Collection::ArrayList* 	__pAnimationFrameList;


	void    _ClearContentInfoList();

	// IListViewItemEventListener
	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView &listView, int index, Tizen::Ui::Controls::SweepDirection direction);
	virtual void OnListViewItemLongPressed(Tizen::Ui::Controls::ListView &listView, int index, int elementId, bool& invokeListViewItemCallback);


	// IListViewItemProvider implementation
	Tizen::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
	bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);
	int GetItemCount(void);

	void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

public:


	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
//    void 	OnItemStateChanged(const Tizen::Ui::Control &source, int index, int itemId, Tizen::Ui::ItemStatus status);
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
