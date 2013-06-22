
#ifndef TREEVIEWFORM_H_
#define TREEVIEWFORM_H_

#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FContent.h>
//#include "ZLbadaTreeModel.h"
#include "ZLTreeNode.h"
#include "ZLTreeTitledNode.h"
#include <ZLTreeDialog.h>

#define ID_LIST_ITEM  			101
#define ID_LIST_TEXT_TITLE  	102
#define ID_LIST_TEXT_SUBTITLE  	103
#define ID_LIST_BITMAP  		104
#define ID_LIST_CHECKBOX  		105
#define ID_FORMAT_CUSTOM  		106

//class ZLTreeDialog;

class TreeViewForm :
	public Tizen::Ui::Controls::Form,
	//public Tizen::Ui::ITouchEventListener,
	public Tizen::Ui::IActionEventListener,
    //public Tizen::Ui::IItemEventListener,
    public Tizen::Ui::ICustomItemEventListener,
	public Tizen::Ui::IOrientationEventListener,
	//public Tizen::Base::Runtime::Thread
	public Tizen::Ui::Controls::IFormBackEventListener,
	public Tizen::Ui::Controls::IListViewItemEventListener,
	public Tizen::Ui::Controls::IListViewItemProvider
{
public:
	TreeViewForm();
	~TreeViewForm();
	//bool Initialize(const char *title);
	bool Initialize(ZLTreeDialog* treeDialog);
	Tizen::Base::Runtime::Monitor* myMonitor;
	shared_ptr<ZLTreeDialog> __myTreeDialog;
    bool showIcons;

private:
	static const int ID_FORMAT_TITLE = 500;
	static const int ID_FORMAT_SUBTITLE = 501;
	static const int ID_FORMAT_BITMAP = 502;
protected:
	// Ui
//	bool OnStart(void);
	// Called after the Run() method is called.
//	void OnStop(void);

	ZLTreeDialog* myTreeDialog;
	static const int ID_CONTEXT_ITEM = 200;
	static const int ID_CONTEXT_ITEM1 = 201;

	Tizen::Ui::Controls::Form*			pPreviousForm;
	Tizen::Ui::Controls::Button*			pBtnClose;
	Tizen::Ui::Controls::List*			__pLstSearchList;
	Tizen::Ui::Controls::Popup*			__pCommonPopup;
//	Tizen::Ui::Controls::ContextMenu* __pContextMenuIconText;

	Tizen::Base::Collection::IList*				__pLstContentType;
	Tizen::Base::Collection::IList*				__pLstContentInfo;
	Tizen::Content::ContentType					__ContentType;

	void    _ClearContentInfoList();
	void CreateContextMenuListStyle(void);
	Tizen::Graphics::Point TouchPosition;

public:


	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
//    void 	OnItemStateChanged(const Tizen::Ui::Control &source, int index, int itemId, Tizen::Ui::ItemStatus status);
	virtual void OnOrientationChanged( const Tizen::Ui::Control&  source,  Tizen::Ui::OrientationStatus  orientationStatus );


//    virtual void  OnTouchDoublePressed (const Tizen::Ui::Control &source,	const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
//	virtual void  OnTouchFocusIn (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
//	virtual void  OnTouchFocusOut (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
//	virtual void  OnTouchLongPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
//	virtual void  OnTouchMoved (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
//	virtual void  OnTouchPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
//	virtual void  OnTouchReleased (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);

	void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);
    virtual void OnItemStateChanged(const Tizen::Ui::Control& source, int index, int itemId, Tizen::Ui::ItemStatus status);
    virtual void OnItemStateChanged(const Tizen::Ui::Control& source, int index, int itemId, int elementId, Tizen::Ui::ItemStatus status);

	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);


	// IListViewItemEventListener
	virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
	virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
	virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView &listView, int index, Tizen::Ui::Controls::SweepDirection direction);
	virtual void OnListViewItemLongPressed(Tizen::Ui::Controls::ListView &listView, int index, int elementId, bool& invokeListViewItemCallback);

	//IListViewItemProvider
	virtual Tizen::Ui::Controls::ListItemBase* CreateItem (int index, int itemWidth);
	virtual bool  DeleteItem (int index, Tizen::Ui::Controls::ListItemBase *pItem, int itemWidth);
	virtual int GetItemCount(void);
    int ItemCount;


	void	LoadContentInfo(Tizen::Content::ContentSearchResult* pSearchResult);

	void    updateItem(ZLTreeTitledNode &node, int index);
	void	UpdateContent();
	void	DeleteContent();
//	ZLbadaTreeModel* myModel;

protected:
	ZLTreeNode* selectedNode;
	bool exitFlag;
//    static const int ID_LIST_ITEM = 101;
//	static const int ID_LIST_TEXT_TITLE = 102;
//	static const int ID_LIST_TEXT_SUBTITLE = 103;
//	static const int ID_LIST_BITMAP = 104;
//	static const int ID_LIST_CHECKBOX = 105;
//	static const int ID_FORMAT_CUSTOM = 106;
	Tizen::Graphics::Bitmap* makeIcon(Tizen::Graphics::Bitmap* srcBmp);
	Tizen::Graphics::Rectangle iconRect;
	Tizen::Graphics::Rectangle formArea;
	Tizen::Ui::Controls::ListView*  __pListView;


    result AddListItem(Tizen::Base::String title, Tizen::Base::String subTitle, Tizen::Graphics::Bitmap* pBitmapNormal);

    void RemoveAllListItems();

public :

	void SetPreviousForm(Tizen::Ui::Controls::Form* preForm);
 //   void setModel(ZLbadaTreeModel* TreeModel);
};
//inline void TreeViewForm::setModel(ZLbadaTreeModel* TreeModel) {myModel = TreeModel; };
#endif /* TREEVIEWFORM_H_ */
