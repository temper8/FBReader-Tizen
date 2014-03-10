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

#ifndef ZLBADATREEDIALOG_H
#define ZLBADATREEDIALOG_H

//#include <QtCore/QAbstractItemModel>
//#include <QtCore/QWeakPointer>
//#include <QtCore/QStringList>
//#include <QtCore/QMap>
#include <FBase.h>
#include <ZLTreeDialog.h>
#include "../tree/TreeViewForm.h"

//class WaitWidget;
class TreeActionListener;
//class TreeNodeActionsMenu;

class ZLbadaTreeDialog : public ZLTreeDialog,
						 public Tizen::Base::Runtime::IRunnable
						 {


public:
	enum TreeRoles {
		SubTitleRole,// = Qt::UserRole,
		ActivatableRole,
		PageRole
	};
	
	ZLbadaTreeDialog(const ZLResource &resource);
	~ZLbadaTreeDialog();

//	static bool isAlive(ZLbadaTreeDialog *dialog);
//	void onProgressUpdated(ZLTreeNode *node);
//	void onProgressFinished(ZLTreeNode *node, const std::string &error);
	
	virtual void onNodeBeginInsert(ZLTreeNode *parent, size_t index);
	virtual void onNodeEndInsert();
	virtual void onNodeBeginRemove(ZLTreeNode *parent, size_t index);
	virtual void onNodeEndRemove();
	virtual void onNodeUpdated(ZLTreeNode *node);
	virtual void run();

	virtual void onUpdated();

	Tizen::Base::Object* Run(void);
	Tizen::Base::Runtime::Thread* __pThread;
//	virtual void onCloseRequest();
	
public: ///////; Q_SLOTS:
//	void finishLater();
	
//Q_SIGNALS:
//	void finished();
//	void progressChanged();
	virtual bool back();
	virtual bool enter(ZLTreeNode* node);
	virtual void updateNode(ZLTreeTitledNode &node, int index);
	virtual void treadTerminator();
	virtual void setShowIcons(bool value);
	//virtual bool exitThread();
private:
	bool __terminateThread;
	virtual bool exitThread();
    //WaitWidget* myWaitWidget;
 //   shared_ptr<ZLExecutionData::Listener> myWaitWidgetListener;
    TreeViewForm* myForm;
    //Tizen::Base::Runtime::Monitor* myMonitor;
    //ZLbadaTreeModel* myModel;


    //ZLTreeNode *treeNode(const size_t &index) const;
};

class TreeActionListener : public ZLExecutionData::Listener {

public:
    TreeActionListener();

public:
    void showPercent(int ready, int full);
  //  void finished(const std::string &error);

public:
    bool isFinished() const;
/*
signals:
    void percentChanged(int ready, int full);
    void finishedHappened(const std::string& error);
*/
private:
    bool myIsFinished;

};

#endif // ZLBADATREEDIALOG_H
