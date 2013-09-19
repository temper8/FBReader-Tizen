/*
 * OpenFileForm.cpp
 *
 *  Created on: 15.11.2011
 *      Author: Alex
 */

#include "OpenFileForm.h"
#include <FIo.h>
#include <FMedia.h>

#include "badaForm.h"
#include "../../../../fbreader/src/fbreader/FBReader.h"
using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Content;
using namespace Tizen::Graphics;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Media;

#define	ID_ACT_UPDATE	1600
#define ID_ACT_DELETE	1601
#define ID_ACT_CLOSE	1602

OpenFileForm::OpenFileForm():__pLstContentInfo(0) {
	// TODO Auto-generated constructor stub

}

OpenFileForm::~OpenFileForm() {
	// TODO Auto-generated destructor stub
}

bool OpenFileForm::Initialize()
{
	AppLog("OpenFileForm::Initialize \n");
	// Construct an XML form FORM_STYLE_INDICATOR|
//	Construct(FORM_STYLE_NORMAL|FORM_STYLE_TITLE|FORM_STYLE_SOFTKEY_1);
//	SetTitleText(L"Add Book");
	Form::Construct(FORM_STYLE_NORMAL|FORM_STYLE_HEADER );

	Header* pHeader = GetHeader();
    pHeader->SetTitleText(L"Add Book");

	SetFormBackEventListener(this);

//	AddSoftkeyActionListener(SOFTKEY_0, *this);
//	AddSoftkeyActionListener(SOFTKEY_1, *this);
//	SetSoftkeyActionId(SOFTKEY_0, ID_ACT_UPDATE);
//	SetSoftkeyActionId(SOFTKEY_1, ID_ACT_CLOSE);

	return true;
}

void OpenFileForm::OnFormBackRequested(Tizen::Ui::Controls::Form& source){
	AppLog("Back is clicked!");
	pPreviousForm->SendUserEvent(0, null);
}

result OpenFileForm::OnInitializing(void)
{
	result r = E_SUCCESS;
	AppLog("OpenFileForm::OnInitializing \n");
	SetSoftkeyText(SOFTKEY_1, L"Back");
	// Creates close button
	Rectangle formArea = GetClientAreaBounds();

/*	Button* pBtnClose = new Button();
	pBtnClose->Construct(Rectangle(50, 50, 150, 150), L"Нажми");
	if (pBtnClose == null)
	{
		AppLog("GetControl(IDC_BUTTON1) failed");
		return E_FAILURE;
	}else{
		pBtnClose->SetActionId(ID_ACT_UPDATE);
		pBtnClose->AddActionEventListener(*this);
		AddControl(*pBtnClose);
	}
*/
    // Creates List

    __pLstSearchList = new ListView();
  //  __pLstSearchList->Construct(Rectangle(0, 0, formArea.width, formArea.height-20), LIST_STYLE_NORMAL, LIST_ITEM_SINGLE_TEXT, 100, 0, 480, 0);
    __pLstSearchList->Construct(Rectangle(0, 0, GetClientAreaBounds().width, GetClientAreaBounds().height), true, false);
    __pLstSearchList->SetItemProvider(*this);
    __pLstSearchList->AddListViewItemEventListener(*this);
  //  __pListView->AddListViewItemEventListener(*this);


//pList->AddItemEventListener(*this);
 //   __pLstSearchList->AddItemEventListener(*this);


    // Adds a List to the Form
    AddControl(*__pLstSearchList);


//	__pProgressPopup = new Popup();
//	__pProgressPopup->Construct(true, Dimension(formArea.width-50, 250));
//	__pProgressPopup->SetTitleText(L"Searching");

	// Creates Bitmap.
	//AppResource *pAppResource = Application::GetInstance()->GetAppResource();
/*	Image *pImage = new Image();
    r = pImage->Construct();
	//Bitmap *pBitmap1 = pAppResource->GetBitmapN("/blue/progressing00_big.png");
	Tizen::Base::String aniPath = Tizen::App::App::GetInstance()->GetAppRootPath() +"/res/icons/ani/" ;
	Bitmap *pBitmap1 = pImage->DecodeN(aniPath + "progressing00.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	Bitmap *pBitmap2 = pImage->DecodeN(aniPath + "progressing01.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	Bitmap *pBitmap3 = pImage->DecodeN(aniPath + "progressing02.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	Bitmap *pBitmap4 = pImage->DecodeN(aniPath + "progressing03.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	Bitmap *pBitmap5 = pImage->DecodeN(aniPath + "progressing04.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	Bitmap *pBitmap6 = pImage->DecodeN(aniPath + "progressing05.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	Bitmap *pBitmap7 = pImage->DecodeN(aniPath + "progressing06.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
	Bitmap *pBitmap8 = pImage->DecodeN(aniPath + "progressing07.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);

	// Creates AnimationFrame.
	AnimationFrame *pAniFrame1 = new AnimationFrame(*pBitmap1, 100);
	AnimationFrame *pAniFrame2 = new AnimationFrame(*pBitmap2, 100);
	AnimationFrame *pAniFrame3 = new AnimationFrame(*pBitmap3, 100);
	AnimationFrame *pAniFrame4 = new AnimationFrame(*pBitmap4, 100);
	AnimationFrame *pAniFrame5 = new AnimationFrame(*pBitmap5, 100);
	AnimationFrame *pAniFrame6 = new AnimationFrame(*pBitmap6, 100);
	AnimationFrame *pAniFrame7 = new AnimationFrame(*pBitmap7, 100);
	AnimationFrame *pAniFrame8 = new AnimationFrame(*pBitmap8, 100);


	__pAnimationFrameList = new (std::nothrow) ArrayList();
	__pAnimationFrameList->Construct();
	__pAnimationFrameList->Add(*pAniFrame1);
	__pAnimationFrameList->Add(*pAniFrame2);
	__pAnimationFrameList->Add(*pAniFrame3);
	__pAnimationFrameList->Add(*pAniFrame4);
	__pAnimationFrameList->Add(*pAniFrame5);
	__pAnimationFrameList->Add(*pAniFrame6);
	__pAnimationFrameList->Add(*pAniFrame7);
	__pAnimationFrameList->Add(*pAniFrame8);

	Rectangle popupFormArea = __pProgressPopup->GetClientAreaBounds();
	__pAnimation = new Animation();
	__pAnimation->Construct(Rectangle(popupFormArea.width/2-60, 20, 120, 120), *__pAnimationFrameList);
	__pAnimation->AddAnimationEventListener(*this);
//	__pProgressPopup->AddControl(*__pAnimation);
*/
	return r;
}

//void OpenFileForm::OnItemStateChanged (const Tizen::Ui::Control &source, int index, int itemId, Tizen::Ui::ItemStatus status)
//{}
void OpenFileForm::OnListViewItemSwept(Tizen::Ui::Controls::ListView &listView, int index, Tizen::Ui::Controls::SweepDirection direction){
	AppLog("OnListViewItemSwept");
}

void OpenFileForm::OnListViewItemLongPressed(Tizen::Ui::Controls::ListView &listView, int index, int elementId, bool& invokeListViewItemCallback){
	AppLog("OnListViewItemLongPressed");
}
void OpenFileForm::OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state){
	AppLog("OnListViewContextItemStateChanged");
}

void OpenFileForm::OnListViewItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status){


	String tmpContentPath;
	ByteBuffer* bb;
	AppLog("index %d",index);
	ContentSearchResult* pInfo = (ContentSearchResult*)__pLstContentInfo->GetAt(index);
	//TryCatch(pInfo != null, popStr = "Fail to convert to ContentSearchResult", "Fail to convert %i th node.", i);

	tmpContentPath = ((ContentInfo*)pInfo->GetContentInfo())->GetContentPath();
	bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(tmpContentPath);
	AppLog("tmpContentPath %s",(char*)bb->GetPointer());

	AppLog("Выбран файл! \n");
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();

	if (pInfo) {
			tmpContentPath = ((ContentInfo*)pInfo->GetContentInfo())->GetContentPath();
			bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(tmpContentPath);
			AppLog("tmpContentPath %s",(char*)bb->GetPointer());
			//selectedFile =  std::string((const char*)bb->GetPointer()) ;
			FBReader::Instance().openFile(ZLFile(std::string((const char*)bb->GetPointer())));

		}
	pPreviousForm->SendUserEvent(2, null);
}


result OpenFileForm::OnTerminating(void)
{
	result r = E_SUCCESS;

	return r;
}

void OpenFileForm::SetPreviousForm(Tizen::Ui::Controls::Form* preForm)
{
	pPreviousForm = preForm;
}


void OpenFileForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
	switch(actionId)
	{
	case ID_ACT_CLOSE:
		{
			AppLog("Close button is clicked! \n");
			//Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
			//pFrame->SetCurrentForm(*pPreviousForm);
			//pPreviousForm->Draw();
			//pPreviousForm->Show();
			//((badaForm*)pPreviousForm)->pSearchResultInfo=null;
			pPreviousForm->SendUserEvent(0, null);
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

void OpenFileForm::OnUserEventReceivedN(RequestId requestId, IList* pArgs)
{
	Frame* pFrame = Tizen::App::Application::GetInstance()->GetAppFrame()->GetFrame();
	//FormMgr* pFormMgr = dynamic_cast<FormMgr*> (pFrame->GetControl("FormMgr"));

	//if(pFormMgr == null)
	//	return;

	switch(requestId)
	{
	case ID_SEARCH_START:
		//ShowProgressPopup(true);
		//StartSearch();
		UpdateContent();
			SendUserEvent(OpenFileForm::ID_SEARCH_DONE, null);
		break;
	case ID_SEARCH_DONE:
			{

				//ShowProgressPopup(false);

			/*	bool ret = (static_cast<Boolean*>(pArgs->GetAt(0)))->ToBool();
			//	pArgs->RemoveAll(true);
			//	delete pArgs;
				if(ret)
					pFormMgr->SendUserEvent(FormMgr::REQUEST_ID_SEARCH_RESULT_FORM, null);
				else
				{
					SetSearchButtonEnabled(true);
					ShowErrorMessageBox(L"Failed to search contacts.");
				}
				*/
			}
			break;
		default:
			break;
	}
}


void    OpenFileForm::StartSearch(){
	if(__pThread)
	{
		__pThread->Join();
		delete __pThread;
		__pThread = null;
	}
	//ShowProgressPopup(true);

	__pThread = new Thread();
	__pThread->Construct(*this);
	result r = __pThread->Start();
	if(IsFailed(r))
	{
		//ShowErrorMessageBox(L"Failed to search contacts.");
		//return false;
	}

}

Object* OpenFileForm::Run() {
	UpdateContent();
	SendUserEvent(OpenFileForm::ID_SEARCH_DONE, null);
	return null;
}

void OpenFileForm::UpdateContent(){
	//__pCommonPopup = new Popup;
	//__pCommonPopup->Initialize();
	//__pCommonPopup->SetMessage("Searching...");
	//__pCommonPopup->Show();

	String popStr;

	String sortColumn = null;
	String strQuery = L"";
	String strName = "";
	String tmpContentPath;
	String ch;
	String keyword = null;

	int totalPage = 0;
	int totalCount = 0;
	int nItemCount = 0;
	int nStartIndex = 0;
	int nIndex = 0;
	ByteBuffer* bb;
	ContentSearch contentSearch;

	result r = E_SUCCESS;

	_ClearContentInfoList();		// Clear content info list
//	__pLstSearchList->RemoveAllItems();  // Clear ui list

	ch.Append("/");

	r = contentSearch.Construct(CONTENT_TYPE_ALL);
	TryCatch(E_SUCCESS == r, popStr = "Search fail - Construct fail.", "Construct() is failed by %s.", GetErrorMessage(r));

	strQuery = L"ContentFileName LIKE '%.fb2' OR ContentFileName LIKE '%.epub'";

	bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(strQuery);
	AppLog("strQuery %s",(char*)bb->GetPointer());
	__pLstContentInfo = contentSearch.SearchN(1, 200, totalPage, totalCount, strQuery, sortColumn, SORT_ORDER_NONE);
	TryCatch(__pLstContentInfo != null, popStr = "Search failed.", "ContentSearch.SearchN() is failed by %s", GetErrorMessage(GetLastResult()));

	nItemCount = __pLstContentInfo->GetCount();
	if(nItemCount == 0){
		popStr = "No search result.";
		goto CATCH;
	}


	__pLstSearchList->UpdateList();
	return;

CATCH:

	//delete __pCommonPopup;
	//__pCommonPopup = new CommonPopup;
	//__pCommonPopup->Initialize();
	//__pCommonPopup->SetMessage(popStr);
	//__pCommonPopup->Show(2000);
	//delete __pCommonPopup;

	return;
}

void OpenFileForm::_ClearContentInfoList()
{
	if(__pLstContentInfo != null)
	{
		__pLstContentInfo->RemoveAll(true);
		delete __pLstContentInfo;
		__pLstContentInfo = null;
	}
}

void OpenFileForm::ShowProgressPopup(const bool show)
{
	if(show == true)
	{
		// Changes to the desired show state.
		__pProgressPopup = new Popup();
		__pProgressPopup->Construct(true, Dimension(GetClientAreaBounds().width-50, 250));
		__pProgressPopup->SetTitleText(L"Searching");
		__pProgressPopup->SetShowState(true);
		__pProgressPopup->Show();
		// __pAnimation->Play();
	}
	else
	{
		//__pAnimation->Stop();
		__pProgressPopup->SetShowState(false);
		Draw();
		Show();
	}
}
void OpenFileForm::OnAnimationStopped(const Control& source)
{
	if(__pAnimation)
		__pAnimation->Play();
}


// IListViewItemProvider implementation
ListItemBase* OpenFileForm::CreateItem(int index, int itemWidth)
{
	if (!__pLstContentInfo) return NULL;

    // Creates an instance of CustomItem
    SimpleItem* pItem = new SimpleItem();
    String ch= L"/";
	String ItemName = "";

	ContentSearchResult* pInfo = (ContentSearchResult*)__pLstContentInfo->GetAt(index);
//	TryCatch(pInfo != null, popStr = "Fail to convert to ContentSearchResult", "Fail to convert %i th node.", i);

	String tmpContentPath = ((ContentInfo*)pInfo->GetContentInfo())->GetContentPath();
	ByteBuffer* bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(tmpContentPath);
	AppLog("tmpContentPath %s",(char*)bb->GetPointer());
	int nStartIndex = 0;
	int nIndex = 0;

	while(nIndex != -1){
		tmpContentPath.IndexOf(ch, nStartIndex, nIndex);
		if(nIndex != -1) nStartIndex = nIndex+1;
	}

	tmpContentPath.SubString(nStartIndex, ItemName);

    pItem->Construct(Dimension(itemWidth,100), LIST_ANNEX_STYLE_NORMAL);
    pItem->SetElement(ItemName);

 //   pItem->SetContextItem(__pItemContext);

    return pItem;
}

bool OpenFileForm::DeleteItem(int index, ListItemBase* pItem, int itemWidth)
{
    delete pItem;
    pItem = null;
    return true;
}

int
OpenFileForm::GetItemCount(void)
{
	if (__pLstContentInfo) return __pLstContentInfo->GetCount();
	else return 0;
}

