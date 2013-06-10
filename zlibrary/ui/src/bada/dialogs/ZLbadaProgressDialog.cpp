#include <unistd.h>

#include <ZLibrary.h>
#include <ZLTimeManager.h>

#include "ZLbadaProgressDialog.h"
//#include "ZLQtTreeDialog.h" // for TreeActionListener
//#include "ZLQtUtil.h"
#include "ZLbadaDialogManager.h"

#include <FBase.h>
#include <FUi.h>
#include <FMedia.h>
#include <FAppApp.h>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;
//using namespace Tizen::Content;
using namespace Tizen::Graphics;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Media;

/*
LoadingIcon::LoadingIcon(QWidget* parent) : QLabel(parent), myAngle(0) {
    const int ICON_WIDT H = 60;
    const int ICON_HEIGHT = ICON_WIDTH;
    QString iconFile = QString::fromStdString(ZLibrary::ApplicationImageDirectory()) +
                       QString::fromStdString(ZLibrary::FileNameDelimiter) +
                       "loading_icon.svg";
    qDebug() << "LoadingIcon" << iconFile;
    myTimer = new QTimer(this);
    myPixmap = QPixmap(iconFile);
    myPixmap = myPixmap.scaled(QSize(ICON_WIDTH, ICON_HEIGHT), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    this->setFixedSize(ICON_WIDTH, ICON_HEIGHT);
    connect(myTimer,SIGNAL(timeout()), this, SLOT(rotate()));
    this->hide();

}

void LoadingIcon::moveToPosition(QSize size) {
    move( (size.width() - myPixmap.width()) / 2,
          (size.height() - myPixmap.height()) / 2
        );
}

void LoadingIcon::start() {
    this->show();
    const int REFRESH_TIME = 100;
    myTimer->start(REFRESH_TIME);
}

void LoadingIcon::finish() {
    qDebug() << Q_FUNC_INFO;
    myTimer->stop();
    this->hide();
}

void LoadingIcon::rotate() {
    qDebug() << this->size();
    const int ANGLE_SPEED = 360/10;
    myAngle += ANGLE_SPEED;
    if (myAngle >= 360) {
        myAngle -= 360;
    }
    QPixmap tmpPixmap(myPixmap.size());
    tmpPixmap.fill(Qt::transparent);
    QPainter painter(&tmpPixmap);
    painter.setRenderHint(QPainter::SmoothPixmapTransform, true);
    painter.translate(myPixmap.width()/2,myPixmap.height()/2);
    painter.rotate(qreal(myAngle));
    painter.translate(-myPixmap.width()/2,-myPixmap.height()/2);
    painter.drawPixmap(0,0,myPixmap);
    painter.end();
    this->setPixmap(tmpPixmap);
    QWidget::raise();
}
*/

Tizen::Base::Collection::ArrayList* 	ZLbadaProgressDialog::__pAnimationFrameList = 0;

ZLbadaProgressDialog::ZLbadaProgressDialog(const ZLResourceKey &key) : ZLProgressDialog(key), myRunnable(null), __pProgressPopup(null) {

	AppLog("ZLbadaProgressDialog  = %s",messageText().c_str());


	__pProgressPopup  = new Tizen::Ui::Controls::Popup();
	if (__pProgressPopup) {
			result r;
			r = __pProgressPopup->Construct(true, Tizen::Graphics::Dimension(500,300));
			AppLog("r = %d",r);
			r =__pProgressPopup->SetTitleText(messageText().c_str());
			AppLog("r = %d",r);
			r = __pProgressPopup->SetShowState(true);
			AppLog("r = %d",r);
			//r = __pProgressPopup->Show();

			if (r!=0)	{
				delete __pProgressPopup;
				__pProgressPopup = null;
				AppLog("delete __pPopup");
				}
			}


}

static const double COEF_PROGRESS_BAR_WIDTH = 0.75;
void ZLbadaProgressDialog::ConstructAnimationFrameList(void){
	if (__pAnimationFrameList == null)
	{
	Image image;// = new Image();
	result r = image.Construct();
		//Bitmap *pBitmap1 = pAppResource->GetBitmapN("/blue/progressing00_big.png");
		Tizen::Base::String appPath = Tizen::App::App::GetInstance()->GetAppRootPath() +"/res/icons/ani/" ;
		Bitmap *pBitmap1 = image.DecodeN(appPath + "progressing00.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap2 = image.DecodeN(appPath + "progressing01.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap3 = image.DecodeN(appPath + "progressing02.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap4 = image.DecodeN(appPath + "progressing03.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap5 = image.DecodeN(appPath + "progressing04.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap6 = image.DecodeN(appPath + "progressing05.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap7 = image.DecodeN(appPath + "progressing06.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap8 = image.DecodeN(appPath + "progressing07.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);

		// Creates AnimationFrame.
		AnimationFrame *pAniFrame1 = new AnimationFrame(*pBitmap1, 100);
		AnimationFrame *pAniFrame2 = new AnimationFrame(*pBitmap2, 100);
		AnimationFrame *pAniFrame3 = new AnimationFrame(*pBitmap3, 100);
		AnimationFrame *pAniFrame4 = new AnimationFrame(*pBitmap4, 100);
		AnimationFrame *pAniFrame5 = new AnimationFrame(*pBitmap5, 100);
		AnimationFrame *pAniFrame6 = new AnimationFrame(*pBitmap6, 100);
		AnimationFrame *pAniFrame7 = new AnimationFrame(*pBitmap7, 100);
		AnimationFrame *pAniFrame8 = new AnimationFrame(*pBitmap8, 100);


		__pAnimationFrameList = new ArrayList();
		__pAnimationFrameList->Construct();
		__pAnimationFrameList->Add(*pAniFrame1);
		__pAnimationFrameList->Add(*pAniFrame2);
		__pAnimationFrameList->Add(*pAniFrame3);
		__pAnimationFrameList->Add(*pAniFrame4);
		__pAnimationFrameList->Add(*pAniFrame5);
		__pAnimationFrameList->Add(*pAniFrame6);
		__pAnimationFrameList->Add(*pAniFrame7);
		__pAnimationFrameList->Add(*pAniFrame8);

		delete pBitmap1;
		delete pBitmap2;
		delete pBitmap3;
		delete pBitmap4;
		delete pBitmap5;
		delete pBitmap6;
		delete pBitmap7;
		delete pBitmap8;
	}
}
/*
void TimerThread::ConstructAnimationFrameList(void){
	Image *pImage = new Image();
	result r = pImage->Construct();
		//Bitmap *pBitmap1 = pAppResource->GetBitmapN("/blue/progressing00_big.png");
		Bitmap *pBitmap1 = pImage->DecodeN("/Res/icons/ani/progressing00.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap2 = pImage->DecodeN("/Res/icons/ani/progressing01.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap3 = pImage->DecodeN("/Res/icons/ani/progressing02.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap4 = pImage->DecodeN("/Res/icons/ani/progressing03.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap5 = pImage->DecodeN("/Res/icons/ani/progressing04.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap6 = pImage->DecodeN("/Res/icons/ani/progressing05.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap7 = pImage->DecodeN("/Res/icons/ani/progressing06.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);
		Bitmap *pBitmap8 = pImage->DecodeN("/Res/icons/ani/progressing07.png", BITMAP_PIXEL_FORMAT_R8G8B8A8);

		// Creates AnimationFrame.
		AnimationFrame *pAniFrame1 = new AnimationFrame(*pBitmap1, 100);
		AnimationFrame *pAniFrame2 = new AnimationFrame(*pBitmap2, 100);
		AnimationFrame *pAniFrame3 = new AnimationFrame(*pBitmap3, 100);
		AnimationFrame *pAniFrame4 = new AnimationFrame(*pBitmap4, 100);
		AnimationFrame *pAniFrame5 = new AnimationFrame(*pBitmap5, 100);
		AnimationFrame *pAniFrame6 = new AnimationFrame(*pBitmap6, 100);
		AnimationFrame *pAniFrame7 = new AnimationFrame(*pBitmap7, 100);
		AnimationFrame *pAniFrame8 = new AnimationFrame(*pBitmap8, 100);


		__pAnimationFrameList = new ArrayList();
		__pAnimationFrameList->Construct();
		__pAnimationFrameList->Add(*pAniFrame1);
		__pAnimationFrameList->Add(*pAniFrame2);
		__pAnimationFrameList->Add(*pAniFrame3);
		__pAnimationFrameList->Add(*pAniFrame4);
		__pAnimationFrameList->Add(*pAniFrame5);
		__pAnimationFrameList->Add(*pAniFrame6);
		__pAnimationFrameList->Add(*pAniFrame7);
		__pAnimationFrameList->Add(*pAniFrame8);

		delete pBitmap1;
		delete pBitmap2;
		delete pBitmap3;
		delete pBitmap4;
		delete pBitmap5;
		delete pBitmap6;
		delete pBitmap7;
		delete pBitmap8;

}

void TimerThread::OnAnimationStopped(const Control& source)
{
	AppLog("OnAnimationStopped");
	if(__pAnimation)
		__pAnimation->Play();
}
*/

AnimationThread::AnimationThread(void):myAnimation(null)   { }

AnimationThread::~AnimationThread(void) { }

result AnimationThread::Construct(Tizen::Ui::Controls::Animation* __pAnimation){
	myAnimation=__pAnimation;
	return Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
//	return Thread::Construct(THREAD_TYPE_WORKER);
}

result  AnimationThread::Construct(Tizen::Base::Collection::ArrayList* 	__pAnimationFrameList){
	myAnimationFrameList=__pAnimationFrameList;

	return Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
}

bool AnimationThread::OnStart(void){
	myAnimation = new Animation();

	if (myAnimation == null) AppLog("__pAnimation = null ");
	Rectangle popupFormArea = myProgressPopup->GetClientAreaBounds();
	myAnimation->Construct(Rectangle(popupFormArea.width/2-50, 20, 120, 120), *myAnimationFrameList);
	AppLog("Construct ");
	myAnimation->AddAnimationEventListener(*this);
	myAnimation->SetRepeatCount(10000);
	myProgressPopup->AddControl(*myAnimation);
	if(myAnimation)	{
		AppLog("AnimationThread::OnStart");
	//	myAnimation->AddAnimationEventListener(*this);
		myAnimation->Play();
		myMonitor->Notify();
	}
	return true;
}

void AnimationThread::OnAnimationStopped(const Control& source)
{
	AppLog("OnAnimationStopped");
	if(myAnimation)
		myAnimation->Play();
}
/*
TimerThread::TimerThread(void) : __pTimer(null), myProgressPopup(null) { }

TimerThread::~TimerThread(void) { }

result TimerThread::Construct(Tizen::Ui::Controls::Popup*	pProgressPopup){
	myProgressPopup=pProgressPopup;
	return Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
//	return Thread::Construct(THREAD_TYPE_WORKER);

}

bool TimerThread::OnStart(void){
	AppLog("ZLbadaProgressDialog::OnStart()");

	count =0;

	ConstructAnimationFrameList();
	Rectangle popupFormArea = myProgressPopup->GetClientAreaBounds();

	__pAnimation = new Animation();

	if (__pAnimation == null)AppLog("__pAnimation = null ");
	__pAnimation->Construct(Rectangle(popupFormArea.width/2-50, 20, 120, 120), *__pAnimationFrameList);
	AppLog("Construct ");
	__pAnimation->AddAnimationEventListener(*this);
	__pAnimation->SetRepeatCount(10000);

	myProgressPopup->AddControl(*__pAnimation);

	 __pAnimation->Play();
	return true;
}

void TimerThread::GopStop(void){
	AppLog("ZLbadaProgressDialog::OnStop()");
//	__pTimer->Cancel();
//	delete __pTimer;
	AppLog("fgdfgdf ");
	if (__pAnimation == null)AppLog("__pAnimation = null ");
	__pAnimation->Stop();
	AppLog("fgdfgdf 1");
	__pAnimationFrameList->RemoveAll(true);
	AppLog("fgdfgdf 2");
	__pAnimation->RemoveAnimationEventListener(*this);
	AppLog("fgdfgdf 3");
	__pAnimationFrameList->RemoveAll(true);

	delete __pAnimationFrameList;
//	__pAnimationFrameList = null;
	myProgressPopup->RemoveControl(*__pAnimation);
//	delete __pAnimation;
	AppLog("fgdfgdf ");
//	__pAnimation = null;
}
/*
Tizen::Base::Object* TimerThread::Run(void){
	AppLog("TimerThread run");
	for (int i = 0; i<20;i++)
	{
		Tizen::Graphics::Canvas canvas;
		canvas.Construct();
		//canvas.DrawLine(Point(100,100),Point(300,300+10*count++));
		canvas.DrawArc(Rectangle(250,300,60,60), 0,20*i ,ARC_STYLE_FILLED_PIE);
		canvas.Show();
		AppLog("TimerThread i=%d",i);
		Sleep(1000);
	}
}

void TimerThread::OnTimerExpired(Tizen::Base::Runtime::Timer& timer){
	AppLog("ZLbadaProgressDialog::OnTimerExpired %d", count);
	//Tizen::Graphics::Canvas canvas;
	//canvas.Construct();
	//canvas.DrawLine(Point(100,100),Point(300,300+10*count++));
	//canvas.DrawArc(Rectangle(200,310,80,80), 0, 10*count++ ,ARC_STYLE_FILLED_PIE);
	//canvas.Show();
//	__pTimer->Start(300);
}
*/
Tizen::Base::Object* ZLbadaProgressDialog::Run(void){
	AppLog("ZLbadaProgressDialog RRRun");
	myRunnable->run();
	__pProgressPopup->EndModal(1);
	__pMonitor->Notify();
	AppLog("ZLbadaProgressDialog RRRun end");
	return null;
}

void ZLbadaProgressDialog::run(ZLRunnable &runnable) {
	AppLog("ZLbadaProgressDialog run");
	myRunnable = &runnable;

	if (__pProgressPopup) {
		    __pMonitor = new Monitor;
	    	__pMonitor->Construct();

		    AppLog("ConstructAnimationFrameList");
			ConstructAnimationFrameList();
			Rectangle popupFormArea = __pProgressPopup->GetClientAreaBounds();
			AnimationThread* aniTread = new AnimationThread;
    		aniTread->Construct(__pAnimationFrameList);
    		aniTread->myMonitor = __pMonitor;
    		aniTread->myProgressPopup = __pProgressPopup;
			aniTread->Start();
			result r;
			__pMonitor->Enter();
			AppLog("Animation Monitor");
			//runnable.run();

			__pMonitor->Wait();

			__pMonitor->Exit();

			//__pTimerThread = new TimerThread;
			//r = __pTimerThread->Construct(__pProgressPopup);
			//if (r == E_SUCCESS) AppLog("Construct E_SUCCESS");
			//if (__pTimerThread->Start() == E_SUCCESS) AppLog("Start E_SUCCESS");

			Thread* runTread = new Thread;
			runTread->Construct(*this);
			runTread->Start();

			__pMonitor->Enter();
			AppLog("Thread Start()");
			//runnable.run();
			r = __pProgressPopup->DoModal(modalResult);
				AppLog("after doModal r = %d",r);
		//	__pMonitor->Wait();

			__pMonitor->Exit();
			AppLog("_pMonitor->Exit())");
			//__pTimerThread->Stop();
			//__pTimerThread->GopStop();
			aniTread->Stop();
			aniTread->myAnimation->Stop();

			AppLog("fgdfgdf 1");
			//__pAnimationFrameList->RemoveAll(true);
			AppLog("fgdfgdf 2");
			//delete __pAnimationFrameList;
		//	__pAnimationFrameList = null;
			__pProgressPopup->RemoveControl(*aniTread->myAnimation);
			AppLog("__pTimerThread->Stop()");
			//pTread->Stop();
			delete aniTread;
			delete runTread;
			AppLog("delete runTread");
			//delete __pTimerThread;
			AppLog("delete __pTimerThread");
			delete __pMonitor;
			AppLog("delete __pMonitor;");
			__pProgressPopup->SetShowState(false);
		//	__pProgressPopup->EndModal(0);
			AppLog("SetShowState");
			delete __pProgressPopup;
			AppLog("delete __pPopup");
	}
	else
	{
		runnable.run();
		AppLog("ZLbadaProgressDialog f");
	}

	/*if (r == E_SUCCESS) {
		__pThread = new Tizen::Base::Runtime::Thread();
			__pThread->Construct(*this);
			result r = __pThread->Start();
	}
	else
		*/



}
/*
void ZLbadaProgressDialog::run(TreeActionListener* listener) {
                if (!listener) {
                    return;
                }
                if (listener->isFinished()) {
                    qDebug() << Q_FUNC_INFO << "is finished yet!";
                    return;
                }
                ZLQtDialogManager& dialogManager = static_cast<ZLQtDialogManager&>(ZLQtDialogManager::Instance());
                myDialog = new ZLQtWaitDialog(messageText(),dialogManager.getParentWidget());

                QObject::connect(listener, SIGNAL(finishedHappened(std::string)), myDialog, SLOT(close()));
                myDialog->exec();

                delete myDialog;
                myDialog = 0;
}
*/

void ZLbadaProgressDialog::setMessage(const std::string &message) {
	AppLog("ZLbadaProgressDialog setMessage %s", message.c_str());
	/*
		if (myDialog == 0) {
				return;
		}

		myDialog->myLabel->setText(::qtString(message));

		myDialog->myLayout->invalidate();
		myDialog->repaint();
		qApp->processEvents();
		*/
}


/*

ZLQtWaitDialog::ZLQtWaitDialog(const std::string &message, QWidget* parent) : QDialog(parent) {

	   // for what reasons we use processEvents here?
	   // qApp->processEvents();

                myLayout = new QVBoxLayout;

                QHBoxLayout* layout = new QHBoxLayout;

                myLabel = new QLabel(oneWordWrapped(::qtString(message)));
                myLabel->setFont(MenuItemParameters::getWaitMessageFont());
                //myLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
		myLabel->setWordWrap(true);

                myLoadingIcon = new LoadingIcon;
                myLoadingIcon->start();

//		myProgressBar = new QProgressBar;
//		myProgressBar->setRange(0,0);
//                myProgressBar->setFixedWidth(qApp->desktop()->geometry().width()*COEF_PROGRESS_BAR_WIDTH);

                layout->setAlignment(Qt::AlignHCenter);
                layout->addWidget(myLoadingIcon);
                layout->addWidget(myLabel);
                //myLayout->addWidget(myProgressBar);
                layout->setSpacing(10);

                myLayout->addLayout(layout);
                myLayout->addSpacing(myLoadingIcon->size().height()); // to be on bottom of center line

                myLayout->setAlignment(Qt::AlignVCenter);

		this->setLayout(myLayout);

		//setWindowFlags(windowFlags() | Qt::WindowSoftkeysVisibleHint);

#ifdef __SYMBIAN__
        //setWindowFlags(windowFlags() | Qt::WindowSoftkeysVisibleHint);
        setWindowState(Qt::WindowFullScreen);
#else
        setFixedSize(360,300);
#endif

//        qApp->processEvents();
//        usleep(5000);
//        qApp->processEvents();


}

 void ZLQtWaitDialog::paintEvent(QPaintEvent *event) {
        //myLayout->invalidate();
	QDialog::paintEvent(event);
 }

 void ZLQtWaitDialog::resizeEvent(QResizeEvent *event) {
    //myProgressBar->setFixedWidth(event->size().width()*COEF_PROGRESS_BAR_WIDTH);
    QDialog::resizeEvent(event);
 }

ZLQtWaitDialog::~ZLQtWaitDialog() {
}

QString ZLQtWaitDialog::oneWordWrapped(QString string) {
    const static QString SPACE = " ";
    const static QString WRAP = "\n";
    QString result = string.trimmed();

    int index = 0;
    while ((index = result.indexOf(SPACE + SPACE)) != -1) {
        result.replace(SPACE + SPACE, SPACE);
    }

    result.replace(SPACE, WRAP);
    return result;
}
*/
