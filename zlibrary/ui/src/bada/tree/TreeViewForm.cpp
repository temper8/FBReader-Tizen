
#include "TreeViewForm.h"
//#include "PageForm.h"
#include "ZLTreeNode.h"
#include "ZLTreeTitledNode.h"
#include <ZLTreeActionNode.h>
//#include <ZLTreePageNode.h>

#include <FIo.h>
#include "../view/badaForm.h"
#include "../image/ZLbadaImageManager.h"

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Content;
using namespace Tizen::Graphics;
using namespace Tizen::Base::Runtime;

#define	ID_ACT_UPDATE	1600
#define ID_ACT_DELETE	1601
#define ID_ACT_CLOSE	1602

#define ID_HEADER_ITEM  1000

TreeViewForm::TreeViewForm():__pListView(0),showIcons(true), ItemCount(0) {
	// TODO Auto-generated constructor stub

}

TreeViewForm::~TreeViewForm() {
	// TODO Auto-generated destructor stub
	AppLog("TreeViewForm::~TreeViewForm()");
	__myTreeDialog = 0;
	AppLog("__myTreeDialog = 0");
	myTreeDialog = 0;
	//__pCustomList->RemoveAllItems();
	AppLog("__pCustomList->RemoveAllItems()");
//    delete __pCustomListItemFormat;
//	AppLog("delete __pCustomListItemFormat;");
//	delete __pNoIconsListItemFormat;
//    delete __pCustomList;
    AppLog("delete __pCustomList;");
}
/*
bool TreeViewForm::OnStart(void){
	AppLog("TreeViewForm::OnStart()");
}

// Called after the Run() method is called.
void TreeViewForm::OnStop(void){
	AppLog("TreeViewForm::OnStop()");
	if(myMonitor != null) 	myMonitor->Notify();
}
*/
//bool TreeViewForm::Initialize(const char *title)
bool TreeViewForm::Initialize(ZLTreeDialog* treeDialog)
{
	AppLog("TreeViewForm::Initialize");

	myTreeDialog = treeDialog;

	const char *title = myTreeDialog->myResource["title"].value().c_str();

	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_HEADER |FORM_STYLE_FOOTER );

	Header* pHeader = GetHeader();
    pHeader->SetTitleText(String(title));

	if (String(title).EndsWith("Content") ) {
		exitFlag = true;
		AppLog("exitFlag = true;");
	}
	else exitFlag= false;

	Footer* pFooter = GetFooter();
	pFooter->SetStyle(FOOTER_STYLE_BUTTON_TEXT);
	pFooter->SetBackButton();


	SetFormBackEventListener(this);

	//pFooter->AddActionEventListener(*this);

	return true;
}



result TreeViewForm::OnInitializing(void)
{

	AppLog("TreeViewForm::OnInitializing \n");
	result r = E_SUCCESS;

	formArea = GetClientAreaBounds();
	iconRect = Tizen::Graphics::Rectangle(5, 5, 70, 90);

	__pListView = new (std::nothrow) ListView();
	__pListView->Construct(Rectangle(0, 0, formArea.width, formArea.height), true, false);
	__pListView->SetItemProvider(*this);
	__pListView->AddListViewItemEventListener(*this);

	AddControl(*__pListView);
	AddOrientationEventListener(*this);

	AppLog("TreeViewForm::OnInitializing height=%d",formArea.height);


	return r;
}

Bitmap* TreeViewForm::makeIcon(Bitmap* srcBmp){
	Bitmap *pBmp = new Bitmap;
	pBmp->Construct(Dimension(iconRect.width, iconRect.height), BITMAP_PIXEL_FORMAT_ARGB8888);
	int imageWidth = srcBmp->GetWidth();
	int imageHeight = srcBmp->GetHeight();
	AppLog("makeIcon image w = %d, h = %d", imageWidth, imageHeight);
	int dy = (iconRect.height - imageHeight) / 2;
	int dx = (iconRect.width - imageWidth) / 2;
	if ((dy<0)||(dx<0)) {
		srcBmp->Scale(Dimension(iconRect.width, iconRect.height));
		pBmp->Merge(Point(0,0), *srcBmp, Rectangle(0,0,iconRect.width,iconRect.height));
	}
	else
		pBmp->Merge(Point(dx,dy), *srcBmp, Rectangle(0,0,imageWidth,imageHeight));
	return pBmp;
}

void   TreeViewForm::updateItem(ZLTreeTitledNode &node, int index){
/*		AppLog("updateItem ");
	 	Bitmap *pBmp = null;
		String title = String(node.title().c_str());
	    CustomListItem* pItem = new CustomListItem();
	    //CustomListItem* pItem = (CustomListItem*)__pCustomList->GetItemAt(index);
	    pItem->Construct(100);

	    if (showIcons){
	    	 AppLog("есть иконки ");
	    	 pItem->SetItemFormat(*__pCustomListItemFormat);
	       	 shared_ptr<ZLImage> cover =node.image();
	    	 if (!cover.isNull()) 	{
	    	 		shared_ptr<ZLImageData> coverData = ZLImageManager::Instance().imageData(*cover);
	    	 		if (!coverData.isNull()) {
	    	 				ZLImageData &image = *coverData;
	    	 				Bitmap *tmpBmp = 	((ZLbadaImageData&)image).pBitmap;
	    	 				pBmp = makeIcon(tmpBmp);
	    	 				}
	    	 		}
	    	}

	    else
	    	pItem->SetItemFormat(*__pNoIconsListItemFormat);

	    pItem->SetElement(ID_LIST_TEXT_TITLE, title);
	    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, String(node.subtitle().c_str()));
	    if (pBmp!=null) pItem->SetElement(ID_LIST_BITMAP, *pBmp, pBmp);
	    result r =__pCustomList->SetItemAt(index, *pItem, ID_LIST_TEXT_TITLE);
	    if (r==E_SUCCESS) AppLog("SetItemAt E_SUCCESS");
	    		else AppLog("SetItemAt error");

	    if (pBmp != null) delete pBmp;
*/
	//    __pCustomList->RefreshItem(index);

	 //	RequestRedraw(true);
}

Tizen::Ui::Controls::ListItemBase* TreeViewForm::CreateItem (int index, int itemWidth){
	AppLog("CreateItem");
	CustomItem* pItem = null;
	ZLTreeNode* node = myTreeDialog->myCurrentNode->children().at(index);
	if (const ZLTreeTitledNode *TitledNode = zlobject_cast<const ZLTreeTitledNode*>(node)) {
			AppLog("ZLTreeTitledNode.titile %s",TitledNode->title().c_str());
			//AppLog("ZLTreeTitledNode.imageUrl =  %s",TitledNode->imageUrl().c_str());

			String strName = String(TitledNode->title().c_str());
			String strSub = String(TitledNode->subtitle().c_str());

			pItem = new (std::nothrow) CustomItem();
			Dimension itemDimension(itemWidth,100);
			pItem->Construct(itemDimension, LIST_ANNEX_STYLE_NORMAL);

			Bitmap *pBmp = null;
			Color blk = Color::GetColor(COLOR_ID_BLACK);

			if (showIcons)  {
				shared_ptr<ZLImage> cover = TitledNode->extractCoverImage();
				if (!cover.isNull()) 	{
						shared_ptr<ZLImageData> coverData = ZLImageManager::Instance().imageData(*cover);
						if (!coverData.isNull()) {
								ZLImageData &image = *coverData;
								Bitmap *tmpBmp = 	((ZLbadaImageData&)image).pBitmap;
								//int imageWidth = tmpBmp->GetWidth();
								//int imageHeight = tmpBmp->GetHeight();
								//AppLog("image w = %d, h = %d", imageWidth, imageHeight);
								pBmp = makeIcon(tmpBmp);
								}
						}

				pItem->AddElement(iconRect, ID_FORMAT_BITMAP, *pBmp, null, null);
				pItem->AddElement(Rectangle(85, 12, formArea.width - 85, 40), ID_FORMAT_TITLE, strName,30, blk,blk,blk, true);
				pItem->AddElement(Rectangle(85, 37, formArea.width - 85, 80), ID_FORMAT_SUBTITLE, strSub,22, blk,blk,blk, true);
				}
			else
			{
				pItem->AddElement(Rectangle(15, 12, formArea.width - 15, 40), ID_FORMAT_TITLE, strName,30, blk,blk,blk, true);
				pItem->AddElement(Rectangle(15, 37, formArea.width - 15, 80), ID_FORMAT_SUBTITLE, strSub,22, blk,blk,blk, true);

			}


			if (pBmp != null) delete pBmp;

	}

	return pItem;
}

bool  TreeViewForm::DeleteItem (int index, Tizen::Ui::Controls::ListItemBase *pItem, int itemWidth){
	delete pItem;
	pItem = null;
	return true;
}

int TreeViewForm::GetItemCount(void){
	AppLog("GetItemCount %d", ItemCount);
	return ItemCount;
}


result TreeViewForm::AddListItem(String title,String subTitle, Bitmap* pBitmapNormal)
{
    // Creates an item of the CustomList
	AppLog("AddListItem ");
	SimpleItem* pItem = new (std::nothrow) SimpleItem();
	Dimension itemDimension(720,100);
	pItem->Construct(itemDimension, LIST_ANNEX_STYLE_NORMAL);
	pItem->SetElement(title,null);

/*
    CustomListItem* pItem = new CustomListItem();
    pItem->Construct(100);
    if (showIcons)
    	pItem->SetItemFormat(*__pCustomListItemFormat);
    else
    	pItem->SetItemFormat(*__pNoIconsListItemFormat);
    pItem->SetElement(ID_LIST_TEXT_TITLE,title);
    pItem->SetElement(ID_LIST_TEXT_SUBTITLE, subTitle);
    if (pBitmapNormal!=null) pItem->SetElement(ID_LIST_BITMAP, *pBitmapNormal, pBitmapNormal);
    customList.AddItem(*pItem, ID_LIST_ITEM);
*/
    return E_SUCCESS;
}


result TreeViewForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}

void TreeViewForm::SetPreviousForm(Tizen::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}

void TreeViewForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source){
	AppLog("Back is clicked!");
	if (myTreeDialog->back()) {
		//UpdateContent();
	}
	else	{
	    pPreviousForm->SendUserEvent(0, null);
	}
}

void TreeViewForm::OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state){
	AppLog("OnListViewContextItemStateChanged");




}

void TreeViewForm::OnListViewItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status){
	AppLog("OnListViewItemStateChanged");
	if (status == LIST_ITEM_STATUS_SELECTED) {
		AppLog("index %d",index);

			Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
			String strName;

			//ZLTreeNode* node = myModel->myCurrentNode->children().at(index);
			ZLTreeNode* node = myTreeDialog->myCurrentNode->children().at(index);
		    int actionsCount = node->actions().size();
			AppLog("node->actions().size %d", actionsCount);


			switch (actionsCount){
			case  0: if (ZLTreeTitledNode *TitledNode = zlobject_cast<ZLTreeTitledNode*>(node))
						{
					 	 AppLog("Node is  %s ",TitledNode->title().c_str());
					 	 myTreeDialog->enter(node);
					 	 AppLog("exit enter");
						};
					 break;
			//case  1:
					// pFrame->SetCurrentForm(*pPreviousForm);
				//TODO испраивть на приличную проверку что действие в содежаннии

				// break;
			default:
				/*
				if (exitFlag){
						AppLog("exitFlag == true");
						//pFrame->SetCurrentForm(*pPreviousForm);

					}
				*/
				      std::string actionName = node->actions()[0]->key().Name;
				      AppLog("action name %s",actionName.c_str());
				      if (actionName == "gotoParagraph") pPreviousForm->SendUserEvent(0, null);
					  myTreeDialog->treadTerminator();
					  node->actions()[0]->run();
					  break;
			}

	}
}

void TreeViewForm::OnListViewItemSwept(Tizen::Ui::Controls::ListView &listView, int index, Tizen::Ui::Controls::SweepDirection direction){
	AppLog("OnListViewItemSwept");
}

void TreeViewForm::OnListViewItemLongPressed(Tizen::Ui::Controls::ListView &listView, int index, int elementId, bool& invokeListViewItemCallback){
	AppLog("OnListViewItemLongPressed");
}



void TreeViewForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	switch(actionId)
	{
	case ID_CONTEXT_ITEM:
		AppLog("ID_CONTEXT_ITEM0 is clicked! \n");
	    pPreviousForm->SendUserEvent(0, null);

	case ID_CONTEXT_ITEM+1:
		AppLog("ID_CONTEXT_ITEM1 is clicked! \n");
	case ID_CONTEXT_ITEM+2:
		AppLog("ID_CONTEXT_ITEM2 is clicked! \n");
		if (selectedNode) {
			std::string actionText = selectedNode->actionText(selectedNode->actions()[actionId-ID_CONTEXT_ITEM]);
			AppLog("делаем  %s",actionText.c_str());
			//myHolder.doAction(ActionIdList[indx]);
			shared_ptr<ZLRunnableWithKey> _action = selectedNode->actions()[actionId-ID_CONTEXT_ITEM];
			if (!_action.isNull()) {
				AppLog("doAction %s",actionText.c_str());
				_action->run();
				AppLog("doAction end");
			   //pPreviousForm->SendUserEvent(0, null);
			}
		}
		break;
	case ID_ACT_CLOSE:
		{
			AppLog("Close button is clicked! \n");
			if (myTreeDialog->back()) {
				//UpdateContent();
			}
			else	{
			    pPreviousForm->SendUserEvent(0, null);
			}
		}
		break;
	case ID_ACT_UPDATE:
		{
			AppLog("UpdateContent");
			UpdateContent();
			break;
		}
	/*case ID_ACT_DELETE:
		{
			DeleteContent();
			break;
		}*/
	default:
		break;
	}
}


void TreeViewForm::CreateContextMenuListStyle(void)
{
//	AppResource* pAppResource = Application::GetInstance()->GetAppResource();


//	__pContextMenuIconText = new ContextMenu();
//	__pContextMenuIconText->Construct(Point(100, 240), CONTEXT_MENU_STYLE_LIST);
//	__pContextMenuIconText->AddItem(L"text1",ID_CONTEXT_ITEM1, *pNormalBitmap1, pPressedBitmap1);
//	__pContextMenuIconText->AddItem(L"text2",ID_CONTEXT_ITEM2, *pNormalBitmap2, pPressedBitmap2);
//	__pContextMenuIconText->AddItem(L"text1",ID_CONTEXT_ITEM0);
//	__pContextMenuIconText->AddItem(L"text2",ID_CONTEXT_ITEM1);
//	__pContextMenuIconText->AddActionEventListener(*this);

	// Deallocate bitmaps
	//delete pNormalBitmap1;
	//delete pPressedBitmap1;
	//delete pNormalBitmap2;
	//delete pPressedBitmap2;

}


void TreeViewForm::OnItemStateChanged (const Tizen::Ui::Control &source, int index, int itemId, Tizen::Ui::ItemStatus status)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	String strName;
	AppLog("index %d",index);
	//ZLTreeNode* node = myModel->myCurrentNode->children().at(index);
	ZLTreeNode* node = myTreeDialog->myCurrentNode->children().at(index);
    int actionsCount = node->actions().size();
	AppLog("node->actions().size %d", actionsCount);


	switch (actionsCount){
	case  0: if (ZLTreeTitledNode *TitledNode = zlobject_cast<ZLTreeTitledNode*>(node))
				{
			 	 AppLog("Node is ZLTreeTitledNode %s ",TitledNode->title().c_str());
			 	 //myTreeDialog->enter(node);
			 	 AppLog("exit enter");
				};
			 break;
	//case  1:
			// pFrame->SetCurrentForm(*pPreviousForm);
		//TODO испраивть на приличную проверку что действие в содежаннии

		// break;
	default:
		/*
		if (exitFlag){
				AppLog("exitFlag == true");
				//pFrame->SetCurrentForm(*pPreviousForm);

			}
		*/
		      std::string actionName = node->actions()[0]->key().Name;
		      AppLog("action name %s",actionName.c_str());
		      if (actionName == "gotoParagraph") pPreviousForm->SendUserEvent(0, null);



			  myTreeDialog->treadTerminator();
			  //node->actions()[0]->run();
			  break;
	}

}

void TreeViewForm::RemoveAllListItems(){

}

void TreeViewForm::UpdateContent(){
	AppLog("TreeViewForm::UpdateContent()");
	String popStr;
	String strSub;
	String strName;
	result r = E_SUCCESS;
//	__pLstSearchList->RemoveAllItems();  // Clear ui list
  // Clear ui list
	//AppLog("__pCustomList->RemoveAllItems()");

	Header* pHeader = GetHeader();


   if (ZLTreeTitledNode *myNode = zlobject_cast<ZLTreeTitledNode*>(myTreeDialog->myCurrentNode)) {
	  strName = String(myNode->title().c_str());
	 // SetTitleText(strName);
	  pHeader->SetTitleText(strName);
   }
   else {
		const char *title = myTreeDialog->myResource["title"].value().c_str();
		//SetTitleText(String(title));
		pHeader->SetTitleText(String(title));
   }

   //__pCustomList->RemoveAllItems();
   RemoveAllListItems();


	AppLog("children().size() = %d ",myTreeDialog->myCurrentNode->children().size());

	ItemCount = myTreeDialog->myCurrentNode->children().size();

	__pListView->UpdateList();
	/*
	ZLTreeNode::List::iterator it;
	for (int i =0; i<myTreeDialog->myCurrentNode->children().size(); i++) {
		ZLTreeNode* node = myTreeDialog->myCurrentNode->children().at(i);
		if (const ZLTreeTitledNode *TitledNode = zlobject_cast<const ZLTreeTitledNode*>(node)) {
				AppLog("ZLTreeTitledNode.titile %s",TitledNode->title().c_str());
				//AppLog("ZLTreeTitledNode.imageUrl =  %s",TitledNode->imageUrl().c_str());

				strName = String(TitledNode->title().c_str());
				strSub = String(TitledNode->subtitle().c_str());

				Bitmap *pBmp = null;

				if (showIcons)  {
					shared_ptr<ZLImage> cover =TitledNode->extractCoverImage();
					if (!cover.isNull()) 	{
							shared_ptr<ZLImageData> coverData = ZLImageManager::Instance().imageData(*cover);
							if (!coverData.isNull()) {
								ZLImageData &image = *coverData;
								Bitmap *tmpBmp = 	((ZLbadaImageData&)image).pBitmap;
								//int imageWidth = tmpBmp->GetWidth();
								//int imageHeight = tmpBmp->GetHeight();
								//AppLog("image w = %d, h = %d", imageWidth, imageHeight);
								pBmp = makeIcon(tmpBmp);
								}
					}
				}

				AddListItem(strName, strSub, pBmp);
				if (pBmp != null) delete pBmp;
				}
	}
	*/
	AppLog("before Draw");
//	delete pBitmapLeftIcon;
//	delete pBitmapRightIcon;
	//__pCustomList->Draw();
	AppLog("before Show");
	//__pCustomList->Show();
	AppLog("before ReDraw");
	  RequestRedraw(true);
	return;
}

void TreeViewForm::_ClearContentInfoList()
{
	AppLog("_ClearContentInfoList");
	if(__pLstContentInfo != null)
	{
		__pLstContentInfo->RemoveAll(true);
		delete __pLstContentInfo;
		__pLstContentInfo = null;
	}
}

/*
void TreeViewForm::OnTouchDoublePressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchDoublePressed");
}

void TreeViewForm::OnTouchFocusIn(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusIn");
}

void TreeViewForm::OnTouchFocusOut(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusOut");
}

void TreeViewForm::OnTouchLongPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchLongPressed");

	// Display the OptionMenu

}

void TreeViewForm::OnTouchMoved(const Tizen::Ui::Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchMoved");
//	myHolder.view()->onStylusMove(currentPosition.x, currentPosition.y);
}

void TreeViewForm::OnTouchPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchPressed");
	TouchPosition = currentPosition;
//	myHolder.view()->onStylusPress(currentPosition.x, currentPosition.y);
}

void TreeViewForm::OnTouchReleased(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchReleased");

}
*/

void TreeViewForm::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	AppLog("TreeViewForm::OnUserEventReceivedN requestId = %d", requestId);
	Form* prevForm = pFrame->GetCurrentForm();
	switch(requestId)
	{
	case 0:
		{
			pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
			if (prevForm != null)		{
				pFrame->RemoveControl(*prevForm);
				}

		}
		break;
	case 1:
		{
			AppLog("TreeViewForm::OnUserEventReceivedN 1");
			pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
		}
		break;
	case 2:
		{
			AppLog("TreeViewForm::OnUserEventReceivedN 2");
			pPreviousForm->SendUserEvent(0, null);
		}
		break;
	default:
		break;
	}

}
void TreeViewForm::OnOrientationChanged( const Tizen::Ui::Control&  source,  Tizen::Ui::OrientationStatus  orientationStatus ){

	AppLog("OnOrientationChanged");
}

// Implements an ICustomItemEventListener
/*
void
TreeViewForm::OnItemStateChanged(const Control& source, int index, int itemId, ItemStatus status)
{
    switch (itemId)
    {
        case ID_LIST_ITEM:
            // Todo:
            break;
        default:
            break;
    }
}
*/
void
TreeViewForm::OnItemStateChanged(const Tizen::Ui::Control& source, int index, int itemId, int elementId, Tizen::Ui::ItemStatus status)
{
    switch (itemId)
    {
        case ID_LIST_ITEM:
            {
                switch (elementId)
                {
                    case ID_LIST_TEXT_TITLE:
                        // Todo:
                        break;

                    case ID_LIST_BITMAP:
                        // Todo:
                        break;
                    default:
                        break;
                }
            }
            break;
        default:
            break;
    }
}

