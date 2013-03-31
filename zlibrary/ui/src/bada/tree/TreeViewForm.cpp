
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

TreeViewForm::TreeViewForm():__pCustomListItemFormat(0),__pCustomList(0),showIcons(true) {
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
    delete __pCustomListItemFormat;
	AppLog("delete __pCustomListItemFormat;");
	delete __pNoIconsListItemFormat;
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
	AppLog("TreeViewForm::Initialize \n");
	myTreeDialog = treeDialog;
	const char *title = myTreeDialog->myResource["title"].value().c_str();
	// Construct an XML form FORM_STYLE_INDICATOR|
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_1);
//	Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);

	SetTitleText(String(title));
	if (String(title).EndsWith("Content") ) {
		exitFlag = true;
		AppLog("exitFlag = true;");
	}
	else exitFlag= false;

//	AddSoftkeyActionListener(SOFTKEY_0, *this);
	AddSoftkeyActionListener(SOFTKEY_1, *this);
//	SetSoftkeyActionId(SOFTKEY_0, ID_ACT_UPDATE);
	SetSoftkeyActionId(SOFTKEY_1, ID_ACT_CLOSE);

	return true;
}



result TreeViewForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppLog("TreeViewForm::OnInitializing \n");
	Rectangle formArea = GetClientAreaBounds();

	SetSoftkeyText(SOFTKEY_1, L"Back");

	AddOrientationEventListener(*this);
	AppLog("TreeViewForm::OnInitializing height=%d",formArea.height);
   // Creates CustomList
    __pCustomList = new CustomList();
	//__pCustomList->Construct(Rectangle(0, 0, 480, 800), CUSTOM_LIST_STYLE_NORMAL);
	__pCustomList->Construct(Rectangle(0, 0, formArea.width, formArea.height), CUSTOM_LIST_STYLE_MARK);

	__pCustomList->AddCustomItemEventListener(*this);

	// Creates an item format of the CustomList
	iconRect = Tizen::Graphics::Rectangle(5, 5, 70, 90);

	__pNoIconsListItemFormat = new CustomListItemFormat();
	__pNoIconsListItemFormat->Construct();
	__pNoIconsListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(10, 15, formArea.width - 10, 40), 30);
	__pNoIconsListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(10, 55, formArea.width - 10, 80), 22);
	__pNoIconsListItemFormat->AddElement(ID_LIST_BITMAP, iconRect);
	__pNoIconsListItemFormat->AddElement(ID_LIST_CHECKBOX, Tizen::Graphics::Rectangle(420, 15, 50, 50));


	__pCustomListItemFormat = new CustomListItemFormat();
	__pCustomListItemFormat->Construct();
	__pCustomListItemFormat->AddElement(ID_LIST_TEXT_TITLE, Tizen::Graphics::Rectangle(85, 12, formArea.width - 85, 40), 30);
	__pCustomListItemFormat->AddElement(ID_LIST_TEXT_SUBTITLE, Tizen::Graphics::Rectangle(85, 52, formArea.width - 85, 80), 22);
	__pCustomListItemFormat->AddElement(ID_LIST_BITMAP, iconRect);
	__pCustomListItemFormat->AddElement(ID_LIST_CHECKBOX, Tizen::Graphics::Rectangle(420, 15, 50, 50));

    AddControl(*__pCustomList);
	CreateContextMenuListStyle();
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

	 	Bitmap *pBmp = null;
		String title = String(node.title().c_str());
	    CustomListItem* pItem = new CustomListItem();
	    //CustomListItem* pItem = (CustomListItem*)__pCustomList->GetItemAt(index);
	    pItem->Construct(100);
	    if (showIcons){
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

	    __pCustomList->RefreshItem(index);

	 	RequestRedraw(true);
}

result TreeViewForm::AddListItem(CustomList& customList, String title,String subTitle, Bitmap* pBitmapNormal)
{
    // Creates an item of the CustomList
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
			 	 myTreeDialog->enter(node);
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

	}

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
   if (ZLTreeTitledNode *myNode = zlobject_cast<ZLTreeTitledNode*>(myTreeDialog->myCurrentNode)) {
	  strName = String(myNode->title().c_str());
	  SetTitleText(strName);
   }
   else {
		const char *title = myTreeDialog->myResource["title"].value().c_str();
		SetTitleText(String(title));
   }

   __pCustomList->RemoveAllItems();
	AppLog("children().size() = %d ",myTreeDialog->myCurrentNode->children().size());
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

				AddListItem(*__pCustomList, strName, strSub, pBmp);
				if (pBmp != null) delete pBmp;
				}
	}

//	delete pBitmapLeftIcon;
//	delete pBitmapRightIcon;
	__pCustomList->Draw();
	__pCustomList->Show();
	  RequestRedraw(true);
	return;
}

void TreeViewForm::_ClearContentInfoList()
{
	if(__pLstContentInfo != null)
	{
		__pLstContentInfo->RemoveAll(true);
		delete __pLstContentInfo;
		__pLstContentInfo = null;
	}
}


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

