#ifndef _BADAFORM_H_
#define _BADAFORM_H_

#include <string>

#include <FBase.h>
#include <FUi.h>
//#include "ZLView.h"
#include <FGraphics.h>
#include <FContent.h>

class ZLbadaViewWidget;
class DialogForm;

class badaForm :
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::ITouchEventListener,
	public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::IOrientationEventListener,
	public Tizen::Ui::IKeyEventListener,
	public Tizen::Base::Runtime::ITimerEventListener,
	public Tizen::Ui::Controls::IFormMenuEventListener {

// Construction
	public:
		enum DrawMode {
			DRAW_BLACK_SCREEN = 0,
			SLIDE_NEXT = 1,
			SLIDE_PREV = 2,
			DRAW_CURRENT_PAGE = 3,
		};
	public:
		DrawMode myDrawMode;
		static badaForm &Instance();

	private:
		static badaForm *ourInstance;


public:
	badaForm(void);
	virtual ~badaForm(void);
	bool Initialize();
	bool Initialize(ZLbadaViewWidget* Holder);

// Implementation
protected:
	bool applicationWindowsNotInited;
	int MenuItemCount;
	//static const int ID_BUTTON_OK = 101;
	Tizen::Ui::Controls::Button *__pButtonOk;
	static const int ID_OPTIONKEY = 100;
	static const int ID_OPTIONMENU_ITEM0 = 200;

	Tizen::Ui::Controls::OptionMenu* __pOptionMenu;
	std::string ActionIdList[16];
	Tizen::Graphics::Canvas* pCanvas;
//	Tizen::Graphics::Canvas* myCanvas;
	Tizen::Graphics::Canvas* capturedCanvas;
	Tizen::Graphics::Bitmap* pCapturedBitmap;
	Tizen::Graphics::Bitmap* pNextPageBitmap;
	Tizen::Graphics::Point startTouchPosition;
	Tizen::Graphics::Rectangle formRect;
	Tizen::Graphics::Rectangle srcRect;
//	int touchMove;
//	bool showNewPage;
	bool needRepaintHolder;
	bool endOfBook;
	bool prevPage;
	bool touchMoved;
	int apiVersion;
	result GetSystemInfomation(void);
	Tizen::Base::Runtime::Timer* myTimer;
	int dx;
	int vx;

	void PrevPage();
	void NextPage();

	void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);

	void InitHeader();
	static const int ID_HEADER_LEFTBUTTON = 304;
	static const int ID_HEADER_RIGHTBUTTON = 305;

public:
	int ScreenHeight;
	int ScreenWidth;

//	DialogForm* CreateDalogForm(const char* name);
	DialogForm* CreateDalogForm(void);
    void AddMenuItem(const std::string &name,const  std::string &id);
    Tizen::Content::ContentSearchResult* pSearchResultInfo;
	void goOpenFileForm();
	ZLbadaViewWidget* myHolder;

	void setOrientation(int angle);

	virtual result OnDraw(void);
	virtual result OnInitializing(void);
	virtual result OnTerminating(void);
	virtual void OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
	virtual void OnOrientationChanged( const Tizen::Ui::Control&  source,  Tizen::Ui::OrientationStatus  orientationStatus );

	virtual void  OnTouchDoublePressed (const Tizen::Ui::Control &source,	const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchFocusIn (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchFocusOut (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchLongPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchMoved (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchPressed (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	virtual void  OnTouchReleased (const Tizen::Ui::Control &source, const Tizen::Graphics::Point &currentPosition, const Tizen::Ui::TouchEventInfo &touchInfo);
	void OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);

	virtual void  OnKeyLongPressed (const Tizen::Ui::Control &source, Tizen::Ui::KeyCode keyCode);
	virtual void  OnKeyPressed (const Tizen::Ui::Control &source, Tizen::Ui::KeyCode keyCode);
	virtual void  OnKeyReleased (const Tizen::Ui::Control &source, Tizen::Ui::KeyCode keyCode);

	virtual void OnFormMenuRequested (Tizen::Ui::Controls::Form &source);

};

#endif	//_BADAFORM_H_
