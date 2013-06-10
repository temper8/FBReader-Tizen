/*
 * Copyright (C) 2004-2011 Geometer Plus <contact@geometerplus.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 * 02110-1301, USA.
 */

#include <FBase.h>
//#include <QtCore/QEventLoop>
//#include <QtCore/QCoreApplication>
//#include <QtCore/QDebug>
//#include "ZLQmlDialogContent.h"
#include <ZLTreeActionNode.h>
#include <ZLTreePageNode.h>
#include <ZLTimeManager.h>
#include "ZLbadaTreeDialog.h"
//#include <QtCore/QTimer>

using namespace Tizen::App;
using namespace Tizen::Base;
using namespace Tizen::Base::Collection;
using namespace Tizen::Base::Runtime;
using namespace Tizen::Ui;
using namespace Tizen::Ui::Controls;



ZLbadaTreeDialog::ZLbadaTreeDialog(const ZLResource &resource) : ZLTreeDialog(resource), __pThread(null)
{
	AppLog("ZLbadaTreeDialog::ZLbadaTreeDialog()");

	result r = E_SUCCESS;
	AppLog("new TreeViewForm");
   	Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	myForm = new TreeViewForm;
	AppLog("new ZLbadaTreeModel");
	//myRootNode = ;
	myCurrentNode = &rootNode();
	myForm->SetPreviousForm(pFrame->GetCurrentForm());
	//myForm->Initialize(resource["title"].value().c_str());
	myForm->Initialize(this);
	AppLog("ZLbadaTreeDialog->Initialize()");
	r = pFrame->AddControl(*myForm);
	r = pFrame->SetCurrentForm(*myForm);
	//myForm->SetPreviousForm(PreviousForm);
     //   myView->setItemDelegate(new SubtitleDelegate);
}

ZLbadaTreeDialog::~ZLbadaTreeDialog() {
	AppLog("ZLbadaTreeDialog::~ZLbadaTreeDialog()");
//	delete myForm;
//	aliveTrees()->remove(this);
}

void ZLbadaTreeDialog::setShowIcons(bool value){
	showIcons =  value;
	if (myForm) myForm->showIcons =  value;
}

Object* ZLbadaTreeDialog::Run(void){
	AppLog("__pThread Run");
//	loadCovers();
	AppLog("__pThread Run end");
	return null;
}

bool ZLbadaTreeDialog::exitThread(){
	//int exitCode = 0;
	//__pThread->GetExitCode(exitCode);
	//bool exit;
	//AppLog("exitCode %d",exitCode );
	//__pMonitor->Enter();
	//__pMonitor->Wait();
	//__pMonitor->Exit();
	return __terminateThread;
}

bool ZLbadaTreeDialog::back() {
	AppLog("ZLbadaTreeDialog::back()");
	if (__pThread) {
		AppLog("wait terminateThread ");
		__terminateThread = true;
		//__pThread->Exit(1);
		__pThread->Join();
		AppLog("Join");
		delete __pThread;
		__pThread = null;
	}
	if (myCurrentNode == &rootNode()) {
		return false;
	}
	myCurrentNode = myCurrentNode->parent();
	myForm->UpdateContent();
	 AppLog("UpdateContent finish back");
	 if (showIcons){
		 __pThread = new Thread();
		 __pThread->Construct(*this);
		 //pHeader->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_TITLE);
		 //__pListView->SetTextOfEmptyList(L"Loading...");
		 __terminateThread = false;
		 __pThread->Start();
	 }
	return true;
}

void ZLbadaTreeDialog::treadTerminator(){
	if (__pThread) {
		__terminateThread = true;
		//__pThread->Exit(1);
		__pThread->Join();
		 AppLog("Join");
		delete __pThread;
		__pThread = null;
	}
}


bool ZLbadaTreeDialog::enter(ZLTreeNode* node) {
	 AppLog("enter node");
	if (__pThread) {
		 AppLog("wait terminateThread ");
		__terminateThread = true;
		//__pThread->Exit(1);
		__pThread->Join();
		 AppLog("Join");
		delete __pThread;
		__pThread = null;
	}
	 AppLog("__pThread kill????");
	 myCurrentNode = node;
	 AppLog("enter node 1");
	 myCurrentNode->requestChildren(0);
	 AppLog("enter node 2");
	 myForm->UpdateContent();

	 AppLog("UpdateContent finish enter");
	 if (showIcons){
		// __pThread = new Thread();
		// __pThread->Construct(*this);
		//__terminateThread = false;
		// __pThread->Start();
	 }
	/* result r;
		AppLog("GetFrame");
		Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
		r = pFrame->Draw();
		AppLog("pFrame->Draw();");
		r = pFrame->Show();
		AppLog("pFrame->Show()");*/
	return true;
}

void ZLbadaTreeDialog::updateNode(ZLTreeTitledNode &node, int index){
	AppLog("updateNode %d", index);
	myForm->updateItem(node, index);
}
/*
bool ZLbadaTreeDialog::isAlive(ZLbadaTreeDialog *dialog) {
	return true;//aliveTrees()->contains(dialog);
}
*/
void ZLbadaTreeDialog::run() {
	AppLog("ZLbadaTreeDialog::run");
//	Tizen::Base::Runtime::Monitor* pMonitor = new Tizen::Base::Runtime::Monitor;
//	pMonitor->Construct();
//	myForm->myMonitor = pMonitor;

	result r = E_SUCCESS;
	//myForm->UpdateContent();
/*
	if (__pThread) {
		__terminateThread = true;
		__pThread->Exit(1);
		__pThread->Join();
		 AppLog("Join");
		delete __pThread;
		__pThread = null;
	}
	*/
	 //myCurrentNode = node;
	// myCurrentNode->requestChildren(myWaitWidgetListener);
	 myForm->UpdateContent();

	 AppLog("UpdateContent finish run");
	 if (showIcons){
			__pThread = new Thread();
			__pThread->Construct(*this);
				//pHeader->PlayWaitingAnimation(HEADER_ANIMATION_POSITION_TITLE);
				//__pListView->SetTextOfEmptyList(L"Loading...");
			__terminateThread = false;
			__pThread->Start();
		 }
	AppLog("GetFrame");
	//Frame *pFrame = Application::GetInstance()->GetAppFrame()->GetFrame();
	//r = pFrame->Draw();
	AppLog("pFrame->Draw();");
	//r = pFrame->Show();
	AppLog("pFrame->Show()");
	//myForm->Start();
	//pMonitor->Enter();
	//AppLog("Enter");
	//pMonitor->Wait();
	//AppLog("doAfter");
	//pMonitor->Exit();

}


void ZLbadaTreeDialog::onNodeBeginInsert(ZLTreeNode *parent, size_t index) {
	AppLog("ZLbadaTreeDialog::onNodeBeginInsert");
     //   myModel->onNodeBeginInsert(parent,index);
}

void ZLbadaTreeDialog::onNodeEndInsert() {
	AppLog("ZLbadaTreeDialog::onNodeEndInsert");
    //    myModel->onNodeEndInsert();
}

void ZLbadaTreeDialog::onNodeBeginRemove(ZLTreeNode *parent, size_t index) {
	AppLog("ZLbadaTreeDialog::onNodeBeginRemove");
     //   myModel->onNodeBeginRemove(parent,index);
}
void ZLbadaTreeDialog::onNodeEndRemove() {
	AppLog("ZLbadaTreeDialog::onNodeEndRemove");
    //    myModel->onNodeEndRemove();
}


void ZLbadaTreeDialog::onNodeUpdated(ZLTreeNode *node) {
	AppLog("ZLbadaTreeDialog::onNodeUpdated");
   // myModel->onNodeUpdated(node);
}


TreeActionListener::TreeActionListener() : myIsFinished(false) {

}

bool TreeActionListener::isFinished() const {
    return myIsFinished;
}


void TreeActionListener::showPercent(int ready, int full) {
  //  emit percentChanged(ready,full);
}
/*
void TreeActionListener::finished(const std::string &error) {
    myIsFinished = true;
 //   emit finishedHappened(error);
}

/*
void ZLbadaTreeDialog::run(const QModelIndex &index, int action) {


	ZLTreeNode *node = treeNode(index);
	const ActionVector &actions = node->actions();
	if (action >= 0 && uint(action) < actions.size()) {
		shared_ptr<ZLTreeAction> runnable = actions.at(action);
		shared_ptr<ZLExecutionData::Listener> listener = new ZLQmlActionListener(node, this);
		myListeners.insert(node, listener);
		runnable->setListener(listener);
		ZLTimeManager::Instance().addAutoRemovableTask(new ZLQmlRunnableHelper(runnable));
		emit progressChanged();
	}

}
*/

/*

QModelIndex ZLbadaTreeDialog::index(int row, int column, const QModelIndex &parent) const {
	Q_UNUSED(column);
	ZLTreeNode *node = treeNode(parent);
	if (row < 0 || uint(row) >= node->children().size())
		return QModelIndex();
	return createIndex(node->children().at(row));
}

QModelIndex ZLbadaTreeDialog::parent(const QModelIndex &child) const {
	ZLTreeNode *node = treeNode(child);
	if (node->parent())
		return createIndex(node->parent());
	else
		return QModelIndex();
}

int ZLbadaTreeDialog::rowCount(const QModelIndex &parent) const {
	ZLTreeNode *node = treeNode(parent);
//	qDebug() << Q_FUNC_INFO << &const_cast<ZLbadaTreeDialog*>(this)->rootNode()
//	         << parent << node << node->children().size();
	return node->children().size();
}

int ZLbadaTreeDialog::columnCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return 1;
}

//bool ZLbadaTreeDialog::hasChildren(const QModelIndex &parent) const {
//	ZLTreeNode *node = treeNode(parent);
//	return zlobject_cast<ZLTreeActionNode*>(node) == NULL;
//}

QVariant ZLbadaTreeDialog::data(const QModelIndex &index, int role) const {
	ZLTreeNode *node = treeNode(index);
	if (!node)
		return QVariant();
	
	switch (role) {
	case Qt::DisplayRole:
		if (ZLTreeTitledNode *titledNode = zlobject_cast<ZLTreeTitledNode*>(node))
			return QString::fromStdString(titledNode->title());
		else
			return QString("No title");
	case Qt::DecorationRole:
		if (ZLTreeTitledNode *titledNode = zlobject_cast<ZLTreeTitledNode*>(node)) {
			QString url = QString::fromStdString(titledNode->imageUrl());
			if (url.isEmpty()) {
				url.reserve(45);
				url = QLatin1String("image://tree/");
				url += QString::number(reinterpret_cast<qptrdiff>(this), 16);
				url += QLatin1Char('$');
				url += QString::number(reinterpret_cast<qptrdiff>(node), 16);
			}
			return url;
		} else {
			return QString();
		}
	case SubTitleRole:
		if (ZLTreeTitledNode *titledNode = zlobject_cast<ZLTreeTitledNode*>(node)) {
			QString subtitle = QString::fromStdString(titledNode->subtitle());
			int index = subtitle.indexOf('\n');
			if (index > 0)
				subtitle.resize(index);
			index = subtitle.indexOf(QLatin1String("</p>"));
			if (index > 0)
				subtitle.resize(index + 4);
			return subtitle;
		} else {
			return QString("No subtitle");
		}
	case ActivatableRole:
		return zlobject_cast<ZLTreeActionNode*>(node) != NULL;
	case PageRole:
		return zlobject_cast<ZLTreePageNode*>(node) != NULL;
	default:
		return QVariant();
	}
}

void ZLbadaTreeDialog::fetchChildren(const QModelIndex &index) {
	ZLTreeNode *node = treeNode(index);
	qDebug() << Q_FUNC_INFO << node;
	if (!myListeners.contains(node)) {
		shared_ptr<ZLExecutionData::Listener> listener = new ZLQmlActionListener(node, this);
		myListeners.insert(node, listener);
		node->requestChildren(listener);
		emit progressChanged();
	}
}

QVariant ZLbadaTreeDialog::progressData(const QModelIndex &index) {
	ZLTreeNode *node = treeNode(index);
	shared_ptr<ZLExecutionData::Listener> listenerPointer = myListeners.value(node);
	if (!listenerPointer.isNull()) {
		ZLQmlActionListener *listener = static_cast<ZLQmlActionListener*>(&*listenerPointer);
		QVariantMap data;
		data.insert(QLatin1String("infinite"), listener->isInfinite());
		if (!listener->isInfinite()) {
			data.insert(QLatin1String("value"), listener->value());
			data.insert(QLatin1String("maximumValue"), listener->maximumValue());
		}
		return data;
	}
	return QVariant();
}

bool ZLbadaTreeDialog::activate(const QModelIndex &index) {
	// FIXME: activate shouldn't be run from QtDeclarative
//	if (ZLTreeActionNode *node = zlobject_cast<ZLTreeActionNode*>(treeNode(index)))
//		return node->activate();
	return false;
}

typedef std::vector<shared_ptr<ZLTreeAction> > ActionVector;

QStringList ZLbadaTreeDialog::actions(const QModelIndex &index) {
	QStringList result;
	ZLTreeNode *node = treeNode(index);
	const ActionVector &actions = node->actions();
	for (ActionVector::const_iterator it = actions.begin(); it != actions.end(); ++it) {
		result << QString::fromStdString(node->actionText(*it));
	}
	return result;
}

bool ZLbadaTreeDialog::isVisibleAction(const QModelIndex &index, int action) {
	ZLTreeNode *node = treeNode(index);
	const ActionVector &actions = node->actions();
	if (action < 0 || action >= actions.size())
		return true;
	return actions.at(action)->makesSense();
}

QObject *ZLbadaTreeDialog::createPageContent(const QModelIndex &index) {
	if (ZLTreePageNode *pageNode = zlobject_cast<ZLTreePageNode*>(treeNode(index))) {
		shared_ptr<ZLDialogContent> content = pageNode->content();
		if (content.isNull())
			return 0;
		return &static_cast<ZLQmlDialogContent&>(*content);
	}
	return 0;
}

class ZLQmlRunnableHelper : public ZLRunnable {
public:
	ZLQmlRunnableHelper(shared_ptr<ZLTreeAction> action) : myAction(action) {}
	~ZLQmlRunnableHelper() {}
	
	void run() { myAction->run(); }
	
private:
	shared_ptr<ZLTreeAction> myAction;
};

void ZLbadaTreeDialog::onProgressUpdated(ZLTreeNode *node) {
	Q_UNUSED(node);
	emit progressChanged();
}

void ZLbadaTreeDialog::onProgressFinished(ZLTreeNode *node, const std::string &error) {
	Q_UNUSED(error);
	if (myListeners.remove(node) > 0)
		emit progressChanged();
}

void ZLbadaTreeDialog::finish() {
//	emit finished();
}

void ZLbadaTreeDialog::onCloseRequest() {
//	QTimer::singleShot(0, this, SLOT(finishLater()));
}

void ZLbadaTreeDialog::finishLater() {
//	finish();
}

QModelIndex ZLbadaTreeDialog::createIndex(ZLTreeNode *node) const {
	if (!node || !node->parent())
		return QModelIndex();
	return QAbstractItemModel::createIndex(node->childIndex(), 0, node);
}

ZLTreeNode *ZLbadaTreeDialog::treeNode(const QModelIndex &index) const {
	if (!index.isValid())
		return &const_cast<ZLbadaTreeDialog*>(this)->rootNode();
	else
		return reinterpret_cast<ZLTreeNode*>(index.internalPointer());
}

ZLbadaDataModel::ZLbadaDataModel() {
}

ZLbadaDataModel::~ZLbadaDataModel() {
}

QObject *ZLbadaDataModel::model() const {
	return myModel.data();
}

void ZLbadaDataModel::setModel(QObject *model) {
	if (model == myModel.data())
		return;
	beginResetModel();
	doSetModel(qobject_cast<QAbstractItemModel*>(model));
	myIndex = QModelIndex();
	emit rootIndexChanged(myIndex);
	endResetModel();
}

void ZLbadaDataModel::doSetModel(QAbstractItemModel *model) {
	if (myModel.data() == model)
		return;
	myModel = model;
	connect(model, SIGNAL(rowsAboutToBeInserted(QModelIndex,int,int)),
	        SLOT(onRowsAboutToBeInserted(QModelIndex,int,int)));
	connect(model, SIGNAL(rowsInserted(QModelIndex,int,int)),
	        SLOT(onRowsInserted(QModelIndex,int,int)));
	connect(model, SIGNAL(rowsAboutToBeRemoved(QModelIndex,int,int)),
	        SLOT(onRowsAboutToBeInserted(QModelIndex,int,int)));
	connect(model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
	        SLOT(onRowsRemoved(QModelIndex,int,int)));
	connect(model, SIGNAL(dataChanged(QModelIndex,QModelIndex)),
	        SLOT(onDataChanged(QModelIndex,QModelIndex)));
	emit modelChanged(myModel.data());
}

QModelIndex ZLbadaDataModel::rootIndex() const {
	return myIndex;
}

void ZLbadaDataModel::setRootIndex(const QModelIndex &index) {
	if (myIndex == index)
		return;
	beginResetModel();
	myIndex = index;
	if (index.model())
		doSetModel(const_cast<QAbstractItemModel*>(myIndex.model()));
	emit rootIndexChanged(myIndex);
	endResetModel();
}

QModelIndex ZLbadaDataModel::modelIndex(int index) const {
	return myIndex.child(index, 0);
}

int ZLbadaDataModel::rowCount(const QModelIndex &parent) const {
	Q_UNUSED(parent);
	return myIndex.row();
}

QVariant ZLbadaDataModel::data(const QModelIndex &index, int role) const {
	QModelIndex mappedIndex = myIndex.child(index.row(), 0);
	if (mappedIndex.isValid())
		return mappedIndex.data(role);
	else
		return QVariant();
}

void ZLbadaDataModel::onRowsAboutToBeInserted(const QModelIndex &parent, int first, int last) {
	if (parent == myIndex)
		beginInsertRows(QModelIndex(), first, last);
}

void ZLbadaDataModel::onRowsInserted(const QModelIndex &parent, int first, int last) {
	Q_UNUSED(first);
	Q_UNUSED(last);
	if (parent == myIndex)
		endInsertRows();
}

void ZLbadaDataModel::onRowsAboutToBeRemoved(const QModelIndex &parent, int first, int last) {
	if (parent == myIndex)
		beginRemoveRows(QModelIndex(), first, last);
}

void ZLbadaDataModel::onRowsRemoved(const QModelIndex &parent, int first, int last) {
	Q_UNUSED(first);
	Q_UNUSED(last);
	if (parent == myIndex)
		endRemoveRows();
}

void ZLbadaDataModel::onDataChanged(const QModelIndex &topLeft, const QModelIndex &bottomRight) {
	if (topLeft.parent() == myIndex || bottomRight.parent() == myIndex) {
		QModelIndex left = createIndex(qMin(topLeft.row(), bottomRight.row()), 0, 0);
		QModelIndex right = createIndex(qMax(topLeft.row(), bottomRight.row()), 0, 0);
		emit dataChanged(left, right);
	}
}
*/
