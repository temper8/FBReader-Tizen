#ifndef __ZLBADAPROGRESSDIALOG_H__
#define __ZLBADAPROGRESSDIALOG_H__



#include <ZLProgressDialog.h>
#include <ZLRunnable.h>

#include <FBase.h>
#include <FUi.h>


//#include "ZLQtTreeDialog.h"
/*
class LoadingIcon : public QLabel {
    Q_OBJECT
public:
    LoadingIcon(QWidget* parent=0);
    void moveToPosition(QSize size);
public slots:
    void start();
    void finish();
private slots:
    void rotate();
private:
    int myAngle;
    QPixmap myPixmap;
    QTimer* myTimer;
};

class ZLQtWaitDialog : public QDialog {

public:
                ZLQtWaitDialog(const std::string &message, QWidget* parent=0);
		~ZLQtWaitDialog();
		void paintEvent(QPaintEvent *event);
                void resizeEvent(QResizeEvent *event);

private:
                static QString oneWordWrapped(QString string);

private:
                QVBoxLayout* myLayout;
		QLabel* myLabel;
                LoadingIcon* myLoadingIcon;
                //QProgressBar* myProgressBar;

friend class ZLbadaProgressDialog;
};

*/

//using namespace  Tizen::Base::Runtime;
class AnimationThread:  public Tizen::Base::Runtime::Thread,
						public Tizen::Ui::IAnimationEventListener {
public:
	AnimationThread(void);
	~AnimationThread(void);
	result Construct(Tizen::Ui::Controls::Animation* 		__pAnimation);
	result Construct(Tizen::Base::Collection::ArrayList* 	__pAnimationFrameList);
	bool OnStart(void);
	Tizen::Ui::Controls::Animation* 		myAnimation;
	Tizen::Ui::Controls::Popup*			myProgressPopup;
 	Tizen::Base::Runtime::Monitor*        myMonitor;
private:
//	void ConstructAnimationFrameList(void);
	Tizen::Base::Collection::ArrayList* 	myAnimationFrameList;
	virtual void OnAnimationStopped(const Tizen::Ui::Control& source);

};
/*
class TimerThread: public Tizen::Base::Runtime::ITimerEventListener,
				  // public Tizen::Base::Runtime::IRunnable,
				   public Tizen::Ui::IAnimationEventListener,
				   public Tizen::Base::Runtime::Thread {
public:
	TimerThread(void);
	~TimerThread(void);
	result Construct(Tizen::Ui::Controls::Popup*	pProgressPopup);

public:

	bool OnStart(void);
	void GopStop(void);

public:
	void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);

private:
	Tizen::Ui::Controls::Popup*	myProgressPopup;
	int count;
	Tizen::Base::Runtime::Timer* __pTimer;
	void ConstructAnimationFrameList(void);
	Tizen::Ui::Controls::Animation* 		__pAnimation;
	 Tizen::Base::Collection::ArrayList* 	__pAnimationFrameList;
	virtual void OnAnimationStopped(const Tizen::Ui::Control& source);
	//Tizen::Base::Object* Run(void);
};
*/
class ZLbadaProgressDialog : public ZLProgressDialog,

							// public Tizen::Base::Runtime::Thread,
							// public Tizen::Base::Runtime::ITimerEventListener
							public Tizen::Base::Runtime::IRunnable
							 {
public:
		ZLbadaProgressDialog(const ZLResourceKey &key);

        void run(ZLRunnable &runnable);
               // void run(TreeActionListener* listener); // for wait dialog while loading book

		void setMessage(const std::string &message);

private:


		ZLRunnable* myRunnable;

		void ConstructAnimationFrameList(void);
		static Tizen::Base::Collection::ArrayList* 	__pAnimationFrameList;
	 	Tizen::Ui::Controls::Popup*			__pProgressPopup;
	 	int   modalResult;
	    //Tizen::Base::Runtime::Thread* 		__pThread;
	 	Tizen::Base::Runtime::Monitor*        __pMonitor;
	 //   TimerThread*  __pTimerThread;
		//Tizen::Ui::Controls::Animation* 		__pAnimation;
		//Tizen::Base::Collection::ArrayList* 	__pAnimationFrameList;
	//    Tizen::Base::Runtime::Timer* __pTimer;
	//    void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);
	//	bool OnStart(void);
		void OnStop(void);
		Tizen::Base::Object* Run(void);
};

/*
class ThreadRunnable : public QThread  {
 public:
		ThreadRunnable(ZLRunnable* runnable): QThread(0), myRunnable(runnable) { }
		void run() {
			myRunnable->run();
		}
private:
	ZLRunnable* myRunnable;

};

*/

#endif // __ZLBADAPROGRESSDIALOG_H__
