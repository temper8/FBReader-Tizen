/*
 * HttpTread.cpp
 *
 *  Created on: 15.01.2012
 *      Author: Alex
 */

#include "HttpThread.h"

#include <FBase.h>
#include <FIo.h>
#include <FBaseUtilTypes.h>
#include <FBaseUtilInflator.h>

using namespace Tizen::Base;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Base::Utility;
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

  AppLog("HttpMonitor::DelRef %d",count);

  count--;

  __pMutex->Release();
  }

HttpThread::HttpThread(HttpMonitor* pMonitor, ZLNetworkRequest &request):myMonitor(pMonitor), myRequest(&request),__pSession(null) {

}

HttpThread::~HttpThread(){
	AppLog("~HttpThread");
}
result HttpThread::Construct()
{
	result r = E_SUCCESS;
	//r = Thread::Construct(THREAD_TYPE_EVENT_DRIVEN);
	r = EventDrivenThread::Construct();
	myMonitor->AddRef();
	return r;
}

bool HttpThread::newRequest(Tizen::Base::String &url){

	AppLog("new startRequest");

	result r = E_SUCCESS;
	HttpTransaction* pTransaction = null;
	HttpRequest* pRequest = null;

	String hostAddr = url;
	AppLog("new  startRequest 2");

	hostAddr.Replace("&#38;","&");


	fileName = hostAddr;
	fileName.Replace("/","_");
	fileName.Replace(":","_");
	AppLog("new  startRequest 3");
	if(__pSession == null)	{
		__pSession = new HttpSession();
		AppLog("new  startRequest 4");
		if(__pSession == null)	goto CATCH;

		r = __pSession->Construct(NET_HTTP_SESSION_MODE_MULTIPLE_HOST , null, hostAddr, null);
		if (IsFailed(r))  goto CATCH;
	}
	AppLog("new HttpSession");

	pTransaction = __pSession->OpenTransactionN();
	if (null == pTransaction)	{
		r = GetLastResult();
		goto CATCH;
	}
	AppLog("new OpenTransactionN");

	r = pTransaction->AddHttpTransactionListener(*this);
	if (IsFailed(r)) goto CATCH;

	pRequest = const_cast<HttpRequest*>(pTransaction->GetRequest());
	if(pRequest == null)	{
		r = GetLastResult();
		goto CATCH;
	}
	//r = pRequest->SetUri(myRequest->url().c_str());
	r = pRequest->SetUri(hostAddr);

	if(IsFailed(r))
		goto CATCH;

	r = pRequest->SetMethod(NET_HTTP_METHOD_GET);
	if(IsFailed(r))	goto CATCH;

	AppLog("new Before Submit");
	r = pTransaction->Submit();
	AppLog("new After Submit r=%s",GetErrorMessage(r));

	if(IsFailed(r))	goto CATCH;
	AppLog("new return true;");
	return true;

	CATCH:
		if(pTransaction != null){
			delete pTransaction;
			pTransaction = null;
		}
		AppLog("new HttpClient::TestHttpGet() failed. (%s)", GetErrorMessage(r));
		//return r;
		AppLog("new return false;");
		return false;

}
bool HttpThread::startRequest(){
	//	__pTimer = new Timer;

	//	__pTimer->Construct(*this);
	//	__pTimer->Start(TIMER_TIMEOUT);
	AppLog(" startRequest");

	result r = E_SUCCESS;
	HttpTransaction* pTransaction = null;
	HttpRequest* pRequest = null;

	String hostAddr(myRequest->url().c_str());
	AppLog(" startRequest 2");


	// если это литрес  по https
	if (hostAddr.Contains("https")) {
		hostAddr.Replace("https","http");
		hostAddr.Replace("&#38;lfrom=51","");
		ByteBuffer* bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(hostAddr);
		AppLog("####### hostAddr %s",bb->GetPointer());
	}
	hostAddr.Replace("&#38;","&");
	fileName = hostAddr;
	fileName.Replace("/","_");
	fileName.Replace(":","_");
	AppLog(" startRequest 3");
	if(__pSession == null)	{
		__pSession = new HttpSession();
		AppLog(" startRequest 4");
		if(__pSession == null)	goto CATCH;

		r = __pSession->Construct(NET_HTTP_SESSION_MODE_MULTIPLE_HOST , null, hostAddr, null);
		if (IsFailed(r))  goto CATCH;
	}
	AppLog("new HttpSession");

	pTransaction = __pSession->OpenTransactionN();
	if (null == pTransaction)	{
		r = GetLastResult();
		goto CATCH;
	}
	AppLog("OpenTransactionN");

	r = pTransaction->AddHttpTransactionListener(*this);
	if (IsFailed(r)) goto CATCH;

	pRequest = const_cast<HttpRequest*>(pTransaction->GetRequest());
	if(pRequest == null)	{
		r = GetLastResult();
		goto CATCH;
	}
	//r = pRequest->SetUri(myRequest->url().c_str());
	r = pRequest->SetUri(hostAddr);

	if(IsFailed(r))
		goto CATCH;

	r = pRequest->SetMethod(NET_HTTP_METHOD_GET);
	if(IsFailed(r))	goto CATCH;

	AppLog("Before Submit");
	r = pTransaction->Submit();
	AppLog("After Submit r=%s",GetErrorMessage(r));

	if(IsFailed(r))	goto CATCH;
	AppLog("return true;");
	return true;

	CATCH:
		if(pTransaction != null){
			delete pTransaction;
			pTransaction = null;
		}
		AppLog("HttpClient::TestHttpGet() failed. (%s)", GetErrorMessage(r));
		//return r;
		AppLog("return false;");
		return false;

}

bool HttpThread::OnStart(void){
	AppLog("HttpThread::OnStart()");

	return startRequest();
}

void HttpThread::finishRequest(){
	AppLog("finishRequest");
	myMonitor->DelRef();
	if(myMonitor != null) 	myMonitor->Notify();
	AppLog("finishRequest after Notify");

	if(__pSession != null)
		{
		delete __pSession;
		__pSession = null;
		}

	AppLog("finishRequest end");
}

void HttpThread::OnStop(void){
	AppLog("HttpThread::OnStop()");
	finishRequest();

/*	if (__pTimer)
		{
		__pTimer->Cancel();
		delete __pTimer;
		__pTimer = null;
		}*/

}

void HttpThread::OnUserEventReceivedN (RequestId requestId, Tizen::Base::Collection::IList *pArgs)
{

}

void HttpThread::OnTimerExpired(Timer& timer)
{
	AppLog("####### OnTimerExpired! #######");
	Thread::Stop();
//	if (__pTimer)
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

void HttpThread::OnTransactionHeaderCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction, int headerLen, bool rs)
{
	AppLog("####### OnTransactionHeaderCompleted! #######");
	HttpResponse* pHttpResponse = httpTransaction.GetResponse();
	if(pHttpResponse == null) return;
	HttpHeader* pHttpHeader = pHttpResponse->GetHeader();
	if(pHttpHeader != null)
		{
			String* rawHttpHeader = pHttpHeader->GetRawHeaderN();
			//AppLog("####### tempHeaderString %s",tempHeaderString->GetPointer());
			AppLog("####### header->GetLength() %d",rawHttpHeader->GetLength());
			AppLog("####### headerLen %d", headerLen);
			if (rawHttpHeader->Contains("Content-Encoding: gzip")) {
						AppLog("####### header Content-Encoding: gzip");
			}

			 ByteBuffer* bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(*rawHttpHeader);
			 byte* pArray = (byte*)bb->GetPointer();
			AppLog("####### header GetCapacity %d", bb->GetCapacity());
			myRequest->handleHeader(pArray, (size_t)headerLen);
		}
}

void HttpThread::OnTransactionReadyToRead(HttpSession& httpSession, HttpTransaction& httpTransaction, int availableBodyLen)
{
	AppLog("####### OnTransactionReadyToRead! #######");
	AppLog("Read Body Length: %d", availableBodyLen);
	HttpResponse* pHttpResponse = httpTransaction.GetResponse();
	if(pHttpResponse == null) return;
	AppLog("####### pHttpResponse != null #######");
	AppLog("####### HttpStatusCode %d",pHttpResponse->GetHttpStatusCode());
	//if (pHttpResponse->GetStatusCode() == E_SUCCESS)HTTP_STATUS_OK
	if (pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_OK)
	{
		AppLog("####### GetHttpStatusCode() == HTTP_STATUS_OK #######");
	/*	HttpHeader* pHttpHeader = pHttpResponse->GetHeader();
		if(pHttpHeader != null)
		{
			String* rawHttpHeader = pHttpHeader->GetRawHeaderN();
			//AppLog("####### tempHeaderString %s",tempHeaderString->GetPointer());

			AppLog("####### pBuffer->GetLimit() %d",pBuffer->GetLimit());
			//pBuffer->SetByte(pBuffer->GetLimit()-1 ,'\0');

			//String text(L"Read Body Length: ");
			//text.Append(availableBodyLen);
			//ByteBuffer* bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(*rawHttpHeader);
			//AppLog( "####### rawHttpHeader = %s",(char *)bb->GetPointer());

			if (rawHttpHeader->Contains("Content-Encoding: gzip")) {
				AppLog("####### Content-Encoding: gzip");
				ByteBuffer* pBuf1 = null;
				pBuf1 = Tizen::Base::Utility::Inflator::InflateN(*pBuffer,availableBodyLen);
				if (null != pBuf1)
						   {AppLog("####### null != pBuf1");
								Tizen::Io::File file;
							//	file.Construct("/mnt/mmc/FBReaderWrite/" + fileName, "w");
								file.Construct("/mnt/ums/Downloads/buffer.zip", "w");
								file.Write(*pBuf1);
								//const byte* pArray = pBuf1->GetPointer();
								//myRequest->handleContent(pArray, (size_t)pBuf1->GetCapacity());
								//delete pBuf1;
							    }

			}
			else {
				const byte* pArray = pBuffer->GetPointer();
				myRequest->handleContent(pArray, (size_t)availableBodyLen);
			}
*/
		ByteBuffer* pBuffer = pHttpResponse->ReadBodyN();
		const byte* pArray = pBuffer->GetPointer();
		myRequest->handleContent(pArray, (size_t)availableBodyLen);

			//Tizen::Io::File file;
		//	file.Construct("/mnt/mmc/FBReaderWrite/" + fileName, "w");
			//file.Construct("/mnt/ums/Downloads/" + fileName, "w");
			//file.Write(*pBuffer);
			//file.Write(*rawHttpHeader);
			//delete rawHttpHeader;
			delete pBuffer;

	}
	else {
	//	AppLog("####### HttpStatusCode %d",pHttpResponse->GetHttpStatusCode());
	}
//	Thread::Stop();
}

void HttpThread::OnTransactionAborted(HttpSession& httpSession, HttpTransaction& httpTransaction, result r)
{
	AppLog("####### OnTransactionAborted! (%s)#######", GetErrorMessage(r));

	delete &httpTransaction;
	Quit();
	//finishRequest();
}

void HttpThread::OnTransactionReadyToWrite(HttpSession& httpSession, HttpTransaction& httpTransaction, int recommendedChunkSize)
{
	AppLog("####### OnTransactionReadyToWrite! #######");
}




void HttpThread::OnTransactionCompleted(HttpSession& httpSession, HttpTransaction& httpTransaction)
{
	AppLog("####### OnTransactionCompleted! #######");
	HttpResponse* pHttpResponse = httpTransaction.GetResponse();
	if(pHttpResponse == null)
		AppLog("####### pHttpResponse == null #######");
	else
		AppLog("####### pHttpResponse != null #######");
	AppLog("####### HttpStatusCode %d",pHttpResponse->GetHttpStatusCode());
	//if (pHttpResponse->GetStatusCode() == E_SUCCESS)HTTP_STATUS_OK

	if (pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_OK)
	{
		AppLog("####### GetHttpStatusCode() == HTTP_STATUS_OK #######");
	}
	if (pHttpResponse->GetHttpStatusCode() == HTTP_STATUS_FOUND)
		{
			AppLog("####### GetHttpStatusCode() == HTTP_STATUS_FOUND #######");
			HttpHeader* pHttpHeader = pHttpResponse->GetHeader();
			if(pHttpHeader != null)
					{
						String* rawHttpHeader = pHttpHeader->GetRawHeaderN();
						if (rawHttpHeader->Contains("Location:")) {
							//AppLog("####### tempHeaderString %s",tempHeaderString->GetPointer());
							//Tizen::Base::Collection::IEnumerator* fieldValues = pHttpHeader->GetFieldValuesN("Location");
							AppLog("####### GetFieldValuesN");
							String location;
							int indexOfN;
							rawHttpHeader->IndexOf("\n",0,indexOfN);
							rawHttpHeader->SubString(10,indexOfN-11,location);
							AppLog("####### GetCurrent");
							ByteBuffer* bb = Tizen::Base::Utility::StringUtil::StringToUtf8N(*rawHttpHeader);
							AppLog( "####### rawHttpHeader = %s",(char *)bb->GetPointer());
							ByteBuffer* bb2 = Tizen::Base::Utility::StringUtil::StringToUtf8N(location);
							AppLog( "####### location = %s",(char *)bb2->GetPointer());
							delete &httpTransaction;
							newRequest(location);
						}

					}
		}
	else {
		Quit();
		delete &httpTransaction;
	}


	//finishRequest();


//    OnStop();
//	Thread::Stop();
}

void HttpThread::OnTransactionCertVerificationRequiredN(HttpSession& httpSession, HttpTransaction& httpTransaction, Tizen::Base::String* pCert)
{
	AppLog("####### OnTransactionCertVerificationRequiredN! #######");
}
