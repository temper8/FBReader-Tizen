/*
 * HttpTread.h
 *
 *  Created on: 15.01.2012
 *      Author: Alex
 */

#ifndef HTTPTREAD_H_
#define HTTPTREAD_H_

#include <FApp.h>
#include <FUi.h>
#include <FNet.h>
#include <FSystem.h>
#include <FBase.h>
#include <ZLNetworkRequest.h>


class HttpMonitor : public Tizen::Base::Runtime::Monitor
{
public:

	HttpMonitor();
	~HttpMonitor();
	int count;
	 void  AddRef(void);
	 void  DelRef(void);

private:
	 Tizen::Base::Runtime::Mutex* __pMutex;

};

class HttpThread :	public Tizen::Base::Runtime::EventDrivenThread ,
					public Tizen::Net::Http::IHttpTransactionEventListener,
					public Tizen::Base::Runtime::ITimerEventListener
{
public:
	HttpThread(HttpMonitor* pMonitor, ZLNetworkRequest &request);
	~HttpThread();
	HttpMonitor* myMonitor;
	ZLNetworkRequest* myRequest;
	// Initializes the instance of HttpThread
	result Construct();
	Tizen::Net::Http::HttpSession*	__pSession;

	// Called before the Run() method is called.
	// Can decide whether it can be run or not by returning true or false.
	// If this method returns false, the thread is terminated immediately.

	bool startRequest();
	void finishRequest();
	bool OnStart(void);
	// Called after the Run() method is called.
	void OnStop(void);
	// Called when the timer expires.
//	void OnTimerExpired(Timer& timer);

public:
	// Timer time out for the expire of timer.
	static const int	TIMER_TIMEOUT = 15000;

	void OnUserEventReceivedN (RequestId requestId, Tizen::Base::Collection::IList *pArgs);

private:
	///////////////////////////////////////////////////////////
	// IHttpTransactionEventListener
	///////////////////////////////////////////////////////////
	void OnTransactionReadyToRead(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int availableBodyLen);
	void OnTransactionAborted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, result r);
	void OnTransactionReadyToWrite(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int recommendedChunkSize);
	void OnTransactionHeaderCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, int headerLen, bool rs);
	void OnTransactionCompleted(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction);
	void OnTransactionCertVerificationRequiredN(Tizen::Net::Http::HttpSession& httpSession, Tizen::Net::Http::HttpTransaction& httpTransaction, Tizen::Base::String* pCert);
	void OnTimerExpired(Tizen::Base::Runtime::Timer& timer);
//	Tizen::Base::Runtime::Timer*		__pTimer;

	//to debag
	Tizen::Base::String fileName;
};



#endif /* HTTPTREAD_H_ */
