

#include "ZLBadaViewWidget.h"
#include "ZLbadaPaintContext.h"
#include "../dialogs/ZLbadaDialogManager.h"
#include "badaForm.h"
#include "OpenFileForm.h"
#include "../dialogs/DialogForm.h"
#include "badaForm.h"
#include <FSystem.h>
#include "../../../../../fbreader/src/fbreader/FBReader.h"
#include "../../../../../fbreader/src/fbreader/FBReaderActions.h"
#include "../../../../../fbreader/src/fbreader/BookTextView.h"

#include "ZLTextArea.h"
#include "../library/ZLBadaLibraryImplementation.h"

#include <FMedia.h>



using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
using namespace Tizen::System;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Media;

#define ID_BACK_TO_READING	2600


badaForm *badaForm::ourInstance = 0;

badaForm &badaForm::Instance() {
	return *ourInstance;
}


result badaForm::OnDraw(void)
{
	AppLog("badaForm::OnDraw(void) %d", myDrawMode);
	DrawMode __drawMode = myDrawMode;
	Tizen::Graphics::Canvas* pCanvas =   this->GetCanvasN();
	if (myHolder == null ) __drawMode = DRAW_BLACK_SCREEN;

	switch(__drawMode) {
		case DRAW_BLACK_SCREEN:
			AppLog("DRAW_BLACK_SCREEN");
			pCanvas->FillRectangle(Tizen::Graphics::Color::GetColor(COLOR_ID_BLACK), formRect);
			this->SendUserEvent(3, null);
			pCanvas->Show();
			break;

		case SLIDE_NEXT:
			AppLog("SLIDE_NEXT");
			if (myHolder->myCanvas) pCanvas->Copy(Point(0,0),*myHolder->myCanvas,formRect);
			if (srcRect.width > 0) {
				pCanvas->Copy(Point(0,0),*capturedCanvas,srcRect);
							pCanvas->SetForegroundColor(Tizen::Graphics::Color::GetColor(COLOR_ID_GREY));
							pCanvas->SetLineWidth(2);
							pCanvas->DrawLine(Point(srcRect.width+1,0),Point(srcRect.width+1,srcRect.height));
			}
			pCanvas->Show();
			break;

		case SLIDE_PREV:
			AppLog("SLIDE_PREV");
			pCanvas->Copy(Point(0,0),*capturedCanvas,formRect);
			if (srcRect.width > 0) {
				if (myHolder->myCanvas) pCanvas->Copy(Point(0,0),*myHolder->myCanvas,srcRect);
							pCanvas->SetForegroundColor(Tizen::Graphics::Color::GetColor(COLOR_ID_GREY));
							pCanvas->SetLineWidth(2);
							pCanvas->DrawLine(Point(srcRect.width+1,0),Point(srcRect.width+1,srcRect.height));
			}
			pCanvas->Show();
			break;

		case DRAW_CURRENT_PAGE:
			AppLog("DRAW_CURRENT_PAGE");
		    if (needRepaintHolder) {
		        needRepaintHolder = false;
		    	if (myHolder) myHolder->repaint();
		    }
			if (myHolder->myCanvas) pCanvas->Copy(Point(0,0),*myHolder->myCanvas,formRect);
			pCanvas->Show();
		break;
	default:
		AppLog("default");
		break;
	};

	delete pCanvas;
	return E_SUCCESS;

}

result badaForm::GetSystemInfomation(void)
{
    result r = E_SUCCESS;
    AppLog("GetSystemInfomation ");
    String key(L"PlatformVersion");
    String platformVersion;

  //  r = SystemInfo::GetValue(key, platformVersion);
  //  TryCatch(r == E_SUCCESS, , "MySystemInfo: To get a value is failed");
  //  AppLog("platformVersion %s",platformVersion.GetPointer());
  //  mchar ch;
   // platformVersion.GetCharAt(0,ch);
  //  if (ch == '2') apiVersion = 2;
  //  else
    	apiVersion = 2;
    AppLog("apiVersion %d",apiVersion);
    return E_SUCCESS;

  // CATCH:
  //  return r;
}

//virtual bool onStylusPress(int x, int y);
//virtual bool onStylusRelease(int x, int y);
//virtual bool onStylusMove(int x, int y);
//virtual bool onStylusMovePressed(int x, int y);
//virtual bool onFingerTap(int x, int y);

void badaForm::OnKeyLongPressed (const Tizen::Ui::Control &source, Tizen::Ui::KeyCode keyCode){
	AppLog("OnKeyLongPressed");
	if (apiVersion == 2) this->ConsumeInputEvent();
}

void badaForm::OnKeyPressed (const Tizen::Ui::Control &source, Tizen::Ui::KeyCode keyCode){
	AppLog("OnKeyPressed %d",keyCode);
	if (!FBReader::Instance().EnableTapScrollingByVolumeKeysOption.value()) return;

	switch (keyCode)
		{
	 	 case KEY_SIDE_UP :
	 		    NextPage();
	 	 	 	//FBReader::Instance().doAction(ActionCode::TAP_SCROLL_FORWARD);
	 	 	 	break;

	 	 case KEY_SIDE_DOWN :
	 		     PrevPage();
	 		    //FBReader::Instance().doAction(ActionCode::TAP_SCROLL_BACKWARD);
	 	 	 	break;

	 	 };
	//if (apiVersion == 2) this->ConsumeInputEvent();
}

void badaForm::OnKeyReleased (const Tizen::Ui::Control &source, Tizen::Ui::KeyCode keyCode){
	AppLog("OnKeyReleased");
	switch (keyCode)
		{

	 	 case 171:// KEY_CONTEXT_MENU :
	 		     AppLog("KEY_CONTEXT_MENU");

	 			if (__pOptionMenu != null){
	 					__pOptionMenu->SetShowState(true);
	 					__pOptionMenu->Show();
	 				}

	 		    //FBReader::Instance().doAction(ActionCode::TAP_SCROLL_BACKWARD);
	 	 	 	break;
	 	 };
	//if (apiVersion == 2) this->ConsumeInputEvent();

}

void badaForm::OnFormMenuRequested (Tizen::Ui::Controls::Form &source){
	AppLog("OnFormMenuRequested");
	if (__pOptionMenu != null){
			__pOptionMenu->SetShowState(true);
			__pOptionMenu->Show();
		}
}

void badaForm::OnTimerExpired(Timer& timer){
	dx = dx+ vx;
	vx = vx + 20;

	AppLog("OnTimerExpired %d",dx);
	AppLog("formRect.width %d",formRect.width);
	switch(myDrawMode) {
		case SLIDE_NEXT:
			srcRect = Rectangle(dx,0,formRect.width-dx,formRect.height);
			if (dx<formRect.width) {
					//Draw();
					Invalidate(false);
					myTimer->Start(1);
			}
			else	{
					srcRect = Rectangle(formRect.width,0,0,formRect.height);
					myDrawMode = DRAW_CURRENT_PAGE;
					//Draw();
					delete myTimer;
					myTimer = 0;
					//touchMove = 0;
					//showNewPage = true;
					//Draw();
					Invalidate(false);
			}
			break;

		case SLIDE_PREV:
			srcRect = Rectangle(formRect.width-dx,0,dx,formRect.height);
			if (dx<formRect.width) {
		 			//Draw();
		 			Invalidate(false);
		 			myTimer->Start(1);
		 		}
		 	else	{
		 			srcRect = Rectangle(0,0,formRect.width,formRect.height);
		 			myDrawMode = DRAW_CURRENT_PAGE;
		 			delete myTimer;
		 			myTimer = 0;

		 			//Draw();
		 			Invalidate(false);
		 	}
			break;
	default:
		break;
	};

}

void badaForm::PrevPage(){
	AppLog("PrevPage");
	if (myTimer) {
		myTimer->Cancel();
		delete myTimer;
		myTimer = 0;
	}
	FBReader &fbreader = FBReader::Instance();
	const ZLTextArea &textArea  = fbreader.bookTextView().textArea();
	if (textArea.isEmpty()) {
		AppLog("textArea isEmpty");
		return;
	}
	if (!textArea.myStartCursor.paragraphCursor().isFirst() || !textArea.myStartCursor.isStartOfParagraph())  {
				myTimer = new Timer;
				myTimer->Construct(*this);
				dx = 0;
				vx = 60;
				if (myHolder->myCanvas) capturedCanvas->Copy(Point(0,0),*myHolder->myCanvas,formRect);
				fbreader.doAction(ActionCode::PAGE_SCROLL_BACKWARD);
				myTimer->Start(1);
				myDrawMode = SLIDE_PREV;
	}
}


void badaForm::NextPage(){
	AppLog("NextPage");
	if (myTimer) {
			myTimer->Cancel();
			delete myTimer;
			myTimer = 0;
		}


	FBReader &fbreader = FBReader::Instance();
	const ZLTextArea &textArea  = fbreader.bookTextView().textArea();
	if (textArea.isEmpty()) {
		AppLog("textArea isEmpty");
		return;
	}
	if (!textArea.myEndCursor.paragraphCursor().isLast() ||
					!textArea.myEndCursor.isEndOfParagraph()) {
		myTimer = new Timer;
		myTimer->Construct(*this);
		dx = 0;
		vx = 60;
		if (myHolder->myCanvas) capturedCanvas->Copy(Point(0,0),*myHolder->myCanvas,formRect);

		fbreader.doAction(ActionCode::PAGE_SCROLL_FORWARD);

		myDrawMode = SLIDE_NEXT;

		myTimer->Start(1);
	}

}

void badaForm::OnTouchDoublePressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchDoublePressed");

}

void badaForm::OnTouchFocusIn(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusIn");
}

void badaForm::OnTouchFocusOut(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchFocusOut");
}

void badaForm::OnTouchLongPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("OnTouchLongPressed");

}

void badaForm::OnTouchMoved(const Tizen::Ui::Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	if (myTimer) return;
	AppLog("OnTouchMoved");
	//touchMoved = true;
	int dx = currentPosition.x - startTouchPosition.x;
	int dy = currentPosition.y - startTouchPosition.y;
	if (Math::Abs(dx)<10) return;

	FBReader &fbreader = FBReader::Instance();
	if ((!fbreader.EnableTapScrollingOption.value()) ||
			(fbreader.TapScrollingOnFingerOnlyOption.value())) {
		touchMoved = true;
		return;
	}

	const ZLTextArea &textArea  = fbreader.bookTextView().textArea();
	if (textArea.isEmpty()) {
		AppLog("textArea isEmpty");
		touchMoved = true;
		endOfBook = true;
		return;
	}

	if (endOfBook) return;

	if (!touchMoved) {
		AppLog("if (!touchMoved)");

		if ((dx<0)&& !(!textArea.myEndCursor.paragraphCursor().isLast() || !textArea.myEndCursor.isEndOfParagraph()))
		{
			touchMoved = true;
			endOfBook = true;
			return;
		}

		if ((dx>0)&& !(!textArea.myStartCursor.paragraphCursor().isFirst() || !textArea.myStartCursor.isStartOfParagraph()))
		{
			touchMoved = true;
			endOfBook = true;
			return;
		}

		AppLog("catch canvas");
		if (myHolder->myCanvas) capturedCanvas->Copy(Point(0,0),*myHolder->myCanvas,formRect);
		if (dx<0)
			FBReader::Instance().doAction(ActionCode::TAP_SCROLL_FORWARD);
		else
			FBReader::Instance().doAction(ActionCode::TAP_SCROLL_BACKWARD);
		AppLog("pCanvas->Show");
	}

	touchMoved = true;

	if (dx<0){
		myDrawMode = SLIDE_NEXT;
		AppLog("OnTouchMoved 1");
		srcRect = Rectangle(-dx, 0, formRect.width + dx, formRect.height);
	}
	else {
		myDrawMode = SLIDE_PREV;
		srcRect = Rectangle(formRect.width-currentPosition.x,0,currentPosition.x,formRect.height);
	}
	AppLog("pCanvas->Show");
	//Draw();
	Invalidate(false);
}

void badaForm::OnTouchPressed(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
 touchMoved = false;
 //startMove = true;
 endOfBook = false;
  if (myTimer) return;
  FBReader &fbreader = FBReader::Instance();
  if (!fbreader.EnableTapScrollingOption.value()) return;
  AppLog("OnTouchPressed");
  startTouchPosition = currentPosition;
//  myHolder->view()->onStylusPress(currentPosition.x, currentPosition.y);

}

void badaForm::OnTouchReleased(const Control &source, const Point &currentPosition, const TouchEventInfo &touchInfo)
{
	AppLog("currentPosition x=%d, y=%d",currentPosition.x, currentPosition.y);
	AppLog("formRect x=%d, y=%d",formRect.width, formRect.height);
	bool tapMenu = false;
	int dx = currentPosition.x - startTouchPosition.x;
	int dy = currentPosition.y - startTouchPosition.y;
	if ((Math::Abs(2*currentPosition.y-formRect.height)<500)
			&&(Math::Abs(2*currentPosition.x-formRect.width)<200))//&&
	//	(Math::Abs(dx)<5)&&(Math::Abs(dy)<5))
			{AppLog("OptionMenu");
			tapMenu = true;
			}

	if (touchMoved) {
		AppLog("if (touchMoved) DRAW_CURRENT_PAGE");
		myDrawMode = DRAW_CURRENT_PAGE;
		Invalidate(false);
		//Draw();
		return;
	}

//	if (myTimer) return;

	FBReader &fbreader = FBReader::Instance();
/*
	AppLog("OnTouchReleased 1");
	myHolder->view()->onStylusPress(currentPosition.x, currentPosition.y);
	AppLog("OnTouchReleased 2");
	if ((myHolder->view()->onStylusRelease(currentPosition.x, currentPosition.y))) 	{
		AppLog("onStylusRelease");
		FBReader &fbreader = FBReader::Instance();
		if (fbreader.isFootnoteMode()){
			AppLog("isFootnoteMode");
			SetFormStyle(FORM_STYLE_NORMAL|FORM_STYLE_SOFTKEY_1);
			AddSoftkeyActionListener(SOFTKEY_1, *this);
			SetSoftkeyActionId(SOFTKEY_1, ID_BACK_TO_READING);
			SetSoftkeyText(SOFTKEY_1, L"Back");
			myDrawMode = DRAW_CURRENT_PAGE;

		}
		//RequestRedraw();
		Invalidate(false);
		return;
	}
*/
//	else
	{

	if (tapMenu){AppLog("OptionMenu");
						if (__pOptionMenu != null){
									__pOptionMenu->SetShowState(true);
									__pOptionMenu->Show();
									}
	}
	else	{
				AppLog("no menu");
				//if (touchInfo.IsFlicked()) AppLog("Flicked true");else AppLog("Flicked false");
				if (2*currentPosition.x>formRect.width)
					{
						AppLog("next page");
						if ((!touchMoved)&&fbreader.EnableTapScrollingOption.value()) NextPage();
						//		FBReader::Instance().doAction(ActionCode::TAP_SCROLL_FORWARD);
					}
					else
					{
						AppLog("prev page");
						if ((!touchMoved)&&fbreader.EnableTapScrollingOption.value()) PrevPage();
						//FBReader::Instance().doAction(ActionCode::TAP_SCROLL_BACKWARD);
					}
				}
	}

}

void badaForm::setOrientation(int angle){

	Tizen::Ui::Orientation badaAngle;

	switch (angle) {
		case ZLView::DEGREES0:
			badaAngle = ORIENTATION_PORTRAIT;
			break;
		case ZLView::DEGREES90:
			badaAngle = ORIENTATION_LANDSCAPE ;
			break;
		case ZLView::DEGREES180:
			badaAngle = ORIENTATION_PORTRAIT_REVERSE;
			break;
	    case ZLView::DEGREES270:
		    badaAngle = ORIENTATION_LANDSCAPE_REVERSE;
			break;
	    case -1:
	    	badaAngle = ORIENTATION_AUTOMATIC_FOUR_DIRECTION;
	    	break;
	}
	AppLog("badaAngle %d",badaAngle);
	if (GetOrientation() != badaAngle) SetOrientation(badaAngle);
}

void badaForm::OnOrientationChanged( const Tizen::Ui::Control&  source,  Tizen::Ui::OrientationStatus  orientationStatus ){
    myDrawMode = DRAW_CURRENT_PAGE;
	if (myTimer) {
	   myTimer->Cancel();
	   delete myTimer;
	   myTimer = 0;
   }

	AppLog("OnOrientationChanged");
    needRepaintHolder = true;

	formRect = GetClientAreaBounds();
	if (capturedCanvas) delete capturedCanvas;
	capturedCanvas = new Canvas();
	capturedCanvas->Construct(formRect);
//    myDrawMode = DRAW_CURRENT_PAGE;
    //RequestRedraw(true);
	Draw();
}

badaForm::badaForm(void): needRepaintHolder(false),myDrawMode(DRAW_CURRENT_PAGE),applicationWindowsNotInited(true), myHolder(null), MenuItemCount(0), /*showNewPage(true), touchMove(0),*/ myTimer(0){
	ourInstance = this;
}

badaForm::~badaForm(void)
{
}

bool badaForm::Initialize(){
	AppLog("badaForm::Initialize()");
	Construct(FORM_STYLE_NORMAL);
	//Construct(FORM_STYLE_HEADER);
	//InitHeader();
	SetBackgroundColor(Tizen::Graphics::Color::GetColor(COLOR_ID_BLACK));
	formRect = GetClientAreaBounds();
	return true;
}

bool badaForm::Initialize(ZLbadaViewWidget* Holder)
{
	myHolder = Holder;




	AppLog("badaForm::Initialize2()");

	// Create an OptionMenu
	__pOptionMenu = new OptionMenu();
	__pOptionMenu->Construct();
	__pOptionMenu->AddActionEventListener(*this);
	__pOptionMenu->AddKeyEventListener(*this);
	 this->AddTouchEventListener(*this);
	 this->AddOrientationEventListener(*this);
	 this->AddKeyEventListener(*this);

	formRect = GetClientAreaBounds();

	this->SetFormMenuEventListener(this);

	if (capturedCanvas) delete capturedCanvas;
	capturedCanvas = new Canvas();
	capturedCanvas->Construct(formRect);

	GetSystemInfomation();

	return true;
}



void badaForm::InitHeader() {


    Image img;
    Bitmap* pBitmap1 = null;
    Bitmap* pBitmap2 = null;
    Bitmap* pBitmap3 = null;
    String filePath = Tizen::App::App::GetInstance()->GetAppRootPath() + L"res/icons/menu/ic_menu_library.png";
    img.Construct();
    pBitmap1 = img.DecodeN(filePath, BITMAP_PIXEL_FORMAT_R8G8B8A8);
    filePath = Tizen::App::App::GetInstance()->GetAppRootPath() + L"res/icons/menu/ic_menu_networklibrary.png";
    pBitmap2 = img.DecodeN(filePath, BITMAP_PIXEL_FORMAT_RGB565);
    filePath = Tizen::App::App::GetInstance()->GetAppRootPath() + L"res/icons/menu/ic_menu_toc.png";
    pBitmap3 = img.DecodeN(filePath, BITMAP_PIXEL_FORMAT_ARGB8888);


	Header* pHeader = GetHeader();
	//pHeader->AddActionEventListener(*this);


	//pHeader->RemoveAllButtons();
	//pHeader->RemoveAllItems();

	ButtonItem  buttonLeftItem;
	buttonLeftItem.Construct(BUTTON_ITEM_STYLE_ICON, ID_HEADER_LEFTBUTTON);

    if (pBitmap1 != null) buttonLeftItem.SetIcon(BUTTON_ITEM_STATUS_NORMAL, pBitmap1);
	//buttonLeftItem.SetText(L"Left");

	ButtonItem  buttonRightItem;
	buttonRightItem.Construct(BUTTON_ITEM_STYLE_ICON, ID_HEADER_RIGHTBUTTON);
	 if (pBitmap2 != null)  buttonRightItem.SetIcon(BUTTON_ITEM_STATUS_NORMAL, pBitmap2);
	ButtonItem  button3;
	button3.Construct(BUTTON_ITEM_STYLE_ICON, ID_HEADER_RIGHTBUTTON);
	if (pBitmap3 != null)  button3.SetIcon(BUTTON_ITEM_STATUS_NORMAL, pBitmap3);
	//buttonRightItem.SetText(L"Right");

	pHeader->SetStyle(HEADER_STYLE_TITLE);
	pHeader->SetTitleText(L"TITLE");
	pHeader->SetButton(BUTTON_POSITION_LEFT, buttonLeftItem);
	pHeader->SetButton(BUTTON_POSITION_RIGHT, button3);
//	pHeader->SetButton(BUTTON_POSITION_RIGHT, buttonRightItem);


}

result badaForm::OnInitializing(void)
{
	AppLog("badaForm::OnInitializing()");
	result r = E_SUCCESS;

	return r;
}

result badaForm::OnTerminating(void)
{
	result r = E_SUCCESS;

    delete __pOptionMenu;

	return r;
}

void badaForm::AddMenuItem(const std::string &name, const  std::string &id){
	AppLog("badaForm::AddMenuItem %s,%s",name.c_str(),id.c_str());
	int count =__pOptionMenu->GetItemCount();
	AppLog("badaForm::AddMenuItem count=%d",count);
	AppLog("badaForm::AddMenuItem MenuItemCount=%d",MenuItemCount);

	if (count == 5) {
		__pOptionMenu->AddItem(name.c_str(),ID_OPTIONMENU_ITEM0 -1);
		ActionIdList[MenuItemCount] = id;
		//__pOptionMenu->AddSubItem(5,name.c_str(),ID_OPTIONMENU_ITEM0 + MenuItemCount);
	}
	if (count < 5) {
		ActionIdList[MenuItemCount] = id;
		__pOptionMenu->AddItem(name.c_str(),ID_OPTIONMENU_ITEM0 + MenuItemCount);
	}
	if (count > 5) {
			ActionIdList[MenuItemCount] = id;
			__pOptionMenu->AddSubItem(5,name.c_str(),ID_OPTIONMENU_ITEM0 + MenuItemCount);
		}
	MenuItemCount++;
}

void badaForm::OnActionPerformed(const Tizen::Ui::Control& source, int actionId)
{
    int indx;
    AppLog("actionId %d",actionId);
    if (actionId == ID_BACK_TO_READING ) {
    	FBReader &fbreader = FBReader::Instance();
    	fbreader.showBookTextView();
    	RemoveOptionkeyActionListener(*this);
    	SetFormStyle(FORM_STYLE_NORMAL);
    	Invalidate(false);
    	return;
    }

    indx = actionId - ID_OPTIONMENU_ITEM0;//__pOptionMenu->GetItemIndexFromActionId(actionId);
    if (indx<0) return;
    AppLog("OPTIONMENU %d",indx);
    AppLog("FB Action %s",  ActionIdList[indx].c_str());
    if (ActionIdList[indx] == "quit")  {
    	Application* a = Tizen::App::Application::GetInstance();
    	a->Terminate();
    }
    else
    {
    	myHolder->doAction(ActionIdList[indx]);
    	Invalidate(false);
    }
}

DialogForm* badaForm::CreateDalogForm(void){
	result r = E_SUCCESS;

	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	DialogForm* pDialogForm = new DialogForm;

	AppLog("pDialogForm->Initialize()");

	r = pFrame->AddControl(*pDialogForm);
	r = pFrame->SetCurrentForm(*pDialogForm);
	AppLog("r = pFrame->SetCurrentForm(*pDialogForm);");
	pDialogForm->SetPreviousForm(this);

	return pDialogForm;
}

void badaForm::goOpenFileForm()
{
	result r = E_SUCCESS;
	AppLog("go detail form");
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		OpenFileForm* pOpenFileForm = new OpenFileForm;
		//pOpenFileForm->SetPreviousForm(this);
		pOpenFileForm->SetPreviousForm(pFrame->GetCurrentForm());
		if(pOpenFileForm->Initialize()){
			r = pFrame->AddControl(*pOpenFileForm);
			if(IsFailed(r)){AppLog("Initialize() is failed by %s.", GetErrorMessage(r));return;}

			r = pFrame->SetCurrentForm(*pOpenFileForm);
			if(IsFailed(r)){
				AppLog("pFrame->SetCurrentForm() is failed by %s.", GetErrorMessage(r));
				return;
			}

			AppLog("LoadContentInfo");
			//_detailForm->LoadContentInfo((ContentSearchResult*)__pLstContentInfo->GetAt(index));

			r = pFrame->Draw();
			if(IsFailed(r)){
				AppLog("pFrame->Draw() is failed by %s.", GetErrorMessage(r));
				return;
			}
			r = pFrame->Show();
			if(IsFailed(r)){
				AppLog("pFrame->Show() is failed by %s.", GetErrorMessage(r));
				return;
			}
			pOpenFileForm->StartSearch();
		}
}

void badaForm::OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs)
{
	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	AppLog("badaForm::OnUserEventReceivedN");
	Form* prevForm = pFrame->GetCurrentForm();
	switch(requestId)
	{
	case 0:
		{
			AppLog("badaForm::OnUserEventReceivedN requestId = 0 ");
			pFrame->SetCurrentForm(*this);
			//pFrame->RequestRedraw();
			Invalidate(false);
			//myHolder.doAction(ActionIdList[2]);
			//DetailForm* pDetailForm = static_cast<DetailForm *>(pFrame->GetControl("DetailForm"));
			//badaForm* pbadaForm = (badaForm*)(pFrame->GetControl("badaForm"));
			if (prevForm != null)
			{
				AppLog("prevForm != null");
				pFrame->RemoveControl(*prevForm);
				AppLog("RemoveControl(*prevForm);");
				//ZLbadaDialogManager::deleteTreeDialog();
				AppLog("deleteTreeDialog");
			}
		//	AddKeyEventListener(*this);

		}
		break;
	case 1:
		{
			AppLog("badaForm::а теперь Акшен открываем файл");
			pFrame->SetCurrentForm(*this);
			//pFrame->RequestRedraw();
			Invalidate(false);
			myHolder->doAction(ActionIdList[2]);
		/*	pFrame->SetCurrentForm(*this);
			pFrame->RequestRedraw();
			DetailForm* pDetailForm = static_cast<DetailForm *>(pFrame->GetControl("DetailForm"));
			if (pDetailForm != null)
				pFrame->RemoveControl(*pDetailForm);

			SearchContent();
			*/
		}
		break;
	case 2:
		{
			AppLog("badaForm::OnUserEventReceivedN requestId = 0 ");
				pFrame->SetCurrentForm(*this);
				//pFrame->RequestRedraw();
				Invalidate(false);
				//myHolder.doAction(ActionIdList[2]);
				//DetailForm* pDetailForm = static_cast<DetailForm *>(pFrame->GetControl("DetailForm"));
				//badaForm* pbadaForm = (badaForm*)(pFrame->GetControl("badaForm"));
				if (prevForm != null)
				{
					AppLog("prevForm != null");
					pFrame->RemoveControl(*prevForm);
					AppLog("RemoveControl(*prevForm);");
					//ZLbadaDialogManager::deleteTreeDialog();
					AppLog("deleteTreeDialog");
				}

		}
		break;
	case 3:
		AppLog("initWindow");
		if (applicationWindowsNotInited )ZLApplication::Instance().initWindow();
		applicationWindowsNotInited = false;
		break;
	default:
		break;
	}

}



