#include <FBase.h>
#include "ZLTreeDialog.h"
#include "ZLTreeTitledNode.h"
#include "ZLTimeManager.h"
#include "../../../../fbreader/src/networkActions/NetworkOperationRunnable.h"

/*
const ZLTypeId ZLTreeDialog::TYPE_ID(ZLObjectWithRTTI::TYPE_ID);

const ZLTypeId &ZLTreeDialog::typeId() const {
	return TYPE_ID;
}
*/


class CoverUpdater : public NetworkOperationRunnable {

private:
	//static volatile int Counter;
	static int Counter;

public:
	static shared_ptr<CoverUpdater> create();

private:
	CoverUpdater();

public:
	~CoverUpdater();

	void addTask(shared_ptr<ZLExecutionData> data);
	bool hasTasks() const;

//private:
	void run();

private:
	ZLExecutionData::Vector myDataVector;
};

class CoverUpdaterRunner : public ZLRunnable {

public:
	CoverUpdaterRunner(shared_ptr<CoverUpdater> updater);

private:
	void run();

private:
	shared_ptr<CoverUpdater> myUpdater;
};

//volatile int CoverUpdater::Counter = 0;
int CoverUpdater::Counter = 0;

shared_ptr<CoverUpdater> CoverUpdater::create() {
	AppLog("Counter = %d",Counter);
	return Counter == 0 ? new CoverUpdater() : 0;
}

//CoverUpdater::CoverUpdater() : NetworkOperationRunnable("downloadImages") {
CoverUpdater::CoverUpdater() : NetworkOperationRunnable() {
	++Counter;
}

CoverUpdater::~CoverUpdater() {
	AppLog("~CoverUpdater");
	--Counter;
}

void CoverUpdater::addTask(shared_ptr<ZLExecutionData> data) {
	myDataVector.clear();
	if (!data.isNull()) {
		myDataVector.push_back(data);
	}
}

bool CoverUpdater::hasTasks() const {
	return !myDataVector.empty();
}

void CoverUpdater::run() {
	AppLog("CoverUpdater::run()");
	ZLExecutionData::perform(myDataVector);
}

CoverUpdaterRunner::CoverUpdaterRunner(shared_ptr<CoverUpdater> updater) : myUpdater(updater) {
}

void CoverUpdaterRunner::run() {
	AppLog("CoverUpdaterRunner::run");
	if (myUpdater->hasTasks()) {
		AppLog("myUpdater->hasTasks()");
		myUpdater->run();
		//myUpdater->executeWithUI();
		//FBReader::Instance().refreshWindow();
	}
}

ZLTreeDialog::ZLTreeDialog(const ZLResource &resource):myResource(resource),showIcons(true) {
}

ZLTreeDialog::~ZLTreeDialog() {
}



/*
bool ZLTreeDialog::enter(ZLTreeNode* node) {
	 myCurrentNode = node;
	 myCurrentNode->requestChildren(myListener);
	return true;
}
*/
void ZLTreeDialog::update() {
 //   emit layoutChanged();
}

void ZLTreeDialog::loadCovers() {
	AppLog("loadCovers");
	//shared_ptr<CoverUpdater> updater = new CoverUpdater;//::create();
	shared_ptr<CoverUpdater> updater = CoverUpdater::create();
	if (!updater.isNull())	{
		AppLog("!updater.isNull");
		const ZLTreeNode::List &nodes = myCurrentNode->children();
		int index =0;
		for (ZLTreeNode::List::const_iterator it = nodes.begin(); it != nodes.end(); ++it) {
			//if (terminateThread) {
			//	AppLog("terminateThread 1");
			//	break;
			//}
			ZLTreeTitledNode &node = *(ZLTreeTitledNode*)*it;
			AppLog("ZLTreeTitledNode");
			shared_ptr<ZLImage> coverImage = node.image();
			//if (terminateThread) {
			//	AppLog("terminateThread 2");
			//	break;
			//}
			if (!coverImage.isNull()) {
					AppLog("addTask");
					shared_ptr<ZLExecutionData> exe = coverImage->synchronizationData();
					//if (!exe.isNull()) {AppLog("exe not null");ZLExecutionData::perform(exe);}
					//else {AppLog("exe = null");}
					if (!exe.isNull()) {
						AppLog("exe not null");
						updater->addTask(exe);
						if (updater->hasTasks()) updater->run();

						}
					//ZLExecutionData::perform(coverImage->synchronizationData());
					updateNode(node,index);
				}


			index++;
			if (exitThread()) {
					AppLog("terminateThread 3");
					break;
				}
			}
		/*
		if (updater->hasTasks()) {
				AppLog("hasTasks");
				updater->run();
				//ZLTimeManager::Instance().addAutoRemovableTask(new CoverUpdaterRunner(updater));
			}*/
		}


	AppLog("loadCovers end");
}
