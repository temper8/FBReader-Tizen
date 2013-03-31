/*
 * HttpTread.cpp
 *
 *  Created on: 15.01.2012
 *      Author: Alex
 */

#include "HttpThread.h"


using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Graphics;
using namespace Tizen::System;
using namespace Tizen::App;
using namespace Tizen::Ui::Controls;
using namespace Tizen::Net::Http;


HttpMonitor::HttpMonitor(): count(0){
	__pMutex = new Mutex;
	__pMutex->Create();
}

HttpMonitor::~HttpMonitor(){

}

void  HttpMonitor::AddRef(void)
  {
  __pMutex->Acquire();

  count++;

  __pMutex->Release();
  }

void  HttpMonitor::DelRef(void)
  {
  __pMutex->Acquire ();

  count--;

  __pMutex->Release();
  }

HttpThread::HttpThread(HttpMonitor* pMonitor, ZLNetworkRequest &request):myMonitor(pMonitor), myRequest(&request),__pSession(null) {

}

HttpThread::~HttpThread(){

}
result HttpThread::Construct()
{
	result r = E_SUCCESS;
	r = Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
	//r = Thread::Construct(THREAD_TYPE_WORKER);
	myMonitor->AddRef();
	return r;
}

bool HttpThread::OnStart(void){
	AppLog("HttpThread::OnStart()");
	__pTimer = new Timer;

	__pTimer->Construct(*this);
	__pTimer->Start(TIMER_TIMEOUT);
	AppLog(" new Timer;");
	result r = E_SUCCESS;
	HttpTransaction* pTransaction = null;
	HttpRequest* pRequest = null;

	String hostAddr(myRequest->url().c_str());

	if(__pSession == null)
	{
		__pSession = new HttpSession();
		if(__pSession == null)
			goto CATCH;

		r = __pSession->Construct(NET_HTTP_SESSION_MODE_NORMAL, null, hostAddr, null);
		if (IsFailed(r))
			goto CATCH;
	}
	AppLog("new HttpSession");

	pTransaction = __pSession->OpenTransactionN();
	if (null == pTransaction)
	{
		r = GetLastResult();
		goto CATCH;
	}
	AppLog("OpenTransactionN");

	r = pTransaction->AddHttpTransactionListener(*this);
	if (IsFailed(r))
		goto CATCH;

	pRequest = const_cast<HttpRequest*>(pTransaction->GetRequest());
	if(pRequest == null)
	{
		r = GetLastResult();
		goto CATCH;
	}

	r = pRequest->SetUri(myRequest->url().c_str());
	if(IsFailed(r))
		goto CATCH;

	r = pRequest->SetMethod(NET_HTTP_METHOD_GET);
	if(IsFailed(r))
		goto CATCH;
	AppLog("Before Submit");
	r = pTransaction->Submit();
	AppLog("After Submit r=%s",GetErrorMessage(r));
	if(IsFailed(r))
		goto CATCH;
	AppLog("return true;");
	return true;
	//return r;

CATCH:
	if(pTransaction != null)
	{
		delete pTransaction;
		pTransaction = null;
	}
	AppLog("HttpClient::TestHttpGet() failed. (%s)", GetErrorMessage(r));
	//return r;
	AppLog("return false;");
	return false;

}

void HttpThread::OnStop(void){
	AppLog("HttpThread::OnStop()");

	if(__pSession != null)
		{
		delete __pSession;
		__pSession = null;
		}

	AppLog("delete __pTimer");
	if (__pTimer)
		{
		__pTimer->Cancel();
		delete __pTimer;
		__pTimer = null;
		}
	myMonitor->DelRef();
	if(myMonitor != null) 	myMonitor->Notify();
	AppLog("HttpThread::OnStop() end");
}

void HttpThread::OnUserEventReceivedN (RequestId requestId, Tizen::Base::Collection::IList *pArgs)
{

}

void HttpThread::OnTimerExpired(Timer& timer)
{
	AppLog("####### OnTimerExpired! #######");
	Thread::Stop();
	if (__pTimer)
	{
		//__pTimer->Start(TIMER_TIMEOUT);
	}

}


static size_t handleHeader(void *ptr, size_t size, size_t nmemb, ZLNetworkRequest *request) {
	const size_t dataSize = size * nmemb;
	return (request->handleHeader(ptr, dataSize)) ? dataSize : 0;
}

static size_t handleContent(void *ptr, size_t size, size_t nmemb, ZLNetworkRequest *request) {
	const size_t dataSize = size * nmemb;
	return (request->handleContent(ptr, dataSize)) ? dataSize : 0;
}

void HttpThread::OnTransactionReadyToRead(HttpSession& httpSession, HttpTransaction& httpTransaction, int availableBodyLen)
{
	AppLog("####### OnTransactionReadyToRead! #######");
	AppLog("Read Body Length: %d", availableBodyLen);
	HttpResponse* pHttpResponse = httpTransaction.GetResponse();
	if(pHttpResponse == null) return;
	AppLog("####### pHttpResponse != null #######");
	AppLog("####### HttpStatusCode %d",pHttpResponse->GetStatusCode());
	if (pHttpResponse->GetStatusCode() == E_SUCCESS)
	{
		AppLog("####### GetHttpStatusCode() == HTTP_STATUS_OK #######");
		HttpHeader* pHttpHeader = pHttpResponse->GetHeader();
		if(pHttpHeader != null)
		{
			String* tempHeaderString = pHttpHeader->GetRawHeaderN();
			//AppLog("tempHeaderString %s",tempHeaderString->GetPointer());
			ByteBuffer* pBuffer = pHttpResponse->ReadBodyN();
			AppLog("pBuffer->GetLimit() %d",pBuffer->GetLimit());
			//pBuffer->SetByte(pBuffer->GetLimit()-1 ,'\0');
			const byte* pArray = pBuffer->GetPointer();
			myRequest->handleContent(pArray, (size_t)availableBodyLen);
			//String text(L"Read Body Length: ");
			//text.Append(availableBodyLen);


			delete tempHeaderString;
			delete pBuffer;
		}
	}
	Thread::Stop();
}

void HttpThread::OnTransactionAborted(HttpSession& httpSession, HttpTransaction& httpTransaction, result r)
{
	AppLog("####### OnTransactionAborted! (%s)#######", GetErrorMessage(r));

	delete &httpTransaction;
}

void HttpThread::OnTransactionReadyToWrite(HttpSession& httpSession, HttpTransaction& httpTransaction, int recommendedChunkSize)
{
	AppLog("####### OnTransactionReadyToWrite! #######");
}

void HttpThread::OnTransactionHeaderCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction, int headerLen, bool rs)
{
	AppLog("####### OnTransactionHeaderCompleted! #######");
}



void HttpThread::OnTransactionCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction)
{
	AppLog("####### OnTransactionCompleted! #######");

	delete &httpTransaction;

	Thread::Stop();
}

void HttpThread::OnTransactionCertVerificationRequiredN(HttpSession& httpSession, HttpTransaction& httpTransaction, Tizen::Base::String* pCert)
{
	AppLog("####### OnTransactionCertVerificationRequiredN! #######");
}
