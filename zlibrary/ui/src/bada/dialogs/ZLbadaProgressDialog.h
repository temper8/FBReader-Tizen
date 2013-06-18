#ifndef __ZLBADAPROGRESSDIALOG_H__
#define __ZLBADAPROGRESSDIALOG_H__



#include <ZLProgressDialog.h>
#include <ZLRunnable.h>

#include <FBase.h>
#include <FUi.h>


//using namespace  Tizen::Base::Runtime;


class ZLbadaProgressDialog : public ZLProgressDialog,
							 public Tizen::Base::Runtime::IRunnable,
							 Tizen::Ui::IProgressPopupEventListener
							 {
public:
		ZLbadaProgressDialog(const ZLResourceKey &key);

        void run(ZLRunnable &runnable);
               // void run(TreeActionListener* listener); // for wait dialog while loading book

		void setMessage(const std::string &message);
		//IProgressPopupEventListener
		virtual void OnProgressPopupCanceled(void);
private:

		bool theWorkIsDone;
		bool showProgress;
		ZLRunnable* myRunnable;

	    Tizen::Ui::Controls::ProgressPopup*			__pProgressPopup;
	 	int   modalResult;
	 	Tizen::Base::Runtime::Monitor*        __pMonitor;

		void OnStop(void);
		Tizen::Base::Object* Run(void);
};


#endif // __ZLBADAPROGRESSDIALOG_H__
