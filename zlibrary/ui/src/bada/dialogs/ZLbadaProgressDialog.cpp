#include <unistd.h>

#include <ZLibrary.h>
#include <ZLTimeManager.h>

#include "ZLbadaProgressDialog.h"

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




ZLbadaProgressDialog::ZLbadaProgressDialog(const ZLResourceKey &key) : ZLProgressDialog(key), myRunnable(null) {

	AppLog("ZLbadaProgressDialog  = %s",messageText().c_str());


	__pProgressPopup  = new Tizen::Ui::Controls::ProgressPopup();
	if (__pProgressPopup) {


			result r;
			//__pProgressPopup = new (std::nothrow) ProgressPopup();

			/*r = __pProgressPopup->Construct(true, Tizen::Graphics::Dimension(500,300));
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
				}*/
			}


}

static const double COEF_PROGRESS_BAR_WIDTH = 0.75;


void ZLbadaProgressDialog::OnProgressPopupCanceled(void)
{
	__pProgressPopup->SetShowState(false);
	//Invalidate(true);
}

Tizen::Base::Object* ZLbadaProgressDialog::Run(void){
	AppLog("ZLbadaProgressDialog RRRun");

	myRunnable->run();
	theWorkIsDone = true;
	if (showProgress)	__pProgressPopup->EndModal(0);

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
			theWorkIsDone = false;
			showProgress = false;
			Thread* runTread = new Thread;
			runTread->Construct(*this);
			runTread->Start();
			__pProgressPopup->Construct(false,false);
			__pProgressPopup->SetTitleText(messageText().c_str());
			__pProgressPopup->SetBounds(260,260,200,500);
			__pProgressPopup->AddProgressPopupEventListener(*this);
			__pProgressPopup->SetShowState(true);
			AppLog("Thread Start()");
            if (!theWorkIsDone) {
            	showProgress = true;
    			 __pProgressPopup->DoModal(modalResult);
    			__pProgressPopup->SetShowState(false);
            }

			delete runTread;
			AppLog("delete runTread");
			delete __pMonitor;
			AppLog("delete __pMonitor;");
			delete __pProgressPopup;
			AppLog("delete __pPopup");
	}
	else
	{
		runnable.run();
		AppLog("ZLbadaProgressDialog f");
	}

}


void ZLbadaProgressDialog::setMessage(const std::string &message) {
	AppLog("ZLbadaProgressDialog setMessage %s", message.c_str());

}


