/*
 * Copyright (C) 2009-2010 Geometer Plus <contact@geometerplus.com>
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
#include <algorithm>

#include <ZLResource.h>
#include <ZLImage.h>

#include <ZLDialogManager.h>

#include "NetworkNodes.h"
#include "NetworkView.h"
#include "NetworkNodesFactory.h"
#include "NetworkCatalogUtil.h"

#include "../fbreader/FBReader.h"

#include "../network/NetworkItems.h"
#include "../network/NetworkBookCollection.h"
#include "../network/NetworkLink.h"

#include "../network/authentication/NetworkAuthenticationManager.h"
#include "../networkActions/NetworkOperationRunnable.h"
#include "../networkActions/AuthenticationDialog.h"

class NetworkCatalogNode::OpenInBrowserAction : public ZLTreeAction {

public:
	OpenInBrowserAction(const std::string &url);
	ZLResourceKey key() const;
	void run();

private:
	const std::string myURL;
};

const ZLTypeId NetworkCatalogNode::TYPE_ID(NetworkContainerNode::TYPE_ID);

const ZLTypeId &NetworkCatalogNode::typeId() const {
	return TYPE_ID;
}

NetworkCatalogNode::NetworkCatalogNode(shared_ptr<NetworkItem> item) : myItem(item) {
	init();
}

NetworkCatalogNode::~NetworkCatalogNode() {
}

void NetworkCatalogNode::init() {
	//AppLog("init()");
	const std::string htmlUrl =
		item().URLByType[NetworkItem::URL_HTML_PAGE];
	//AppLog("htmlUrl = %s",htmlUrl.c_str());
	if (!htmlUrl.empty()) {
		registerTreeAction(new OpenInBrowserAction(htmlUrl));
	}
	registerTreeAction(new ReloadAction(*this));
}

bool NetworkCatalogNode::authorise(std::string userName, std::string password){
	AppLog("###### authorise userName = %s",userName.c_str());
	AppLog("###### authorise password = %s",password.c_str());
	const NetworkLink &link = item().Link;
	link.authenticationManager()->authoriseUser(userName,password);
	return true;
}

bool NetworkCatalogNode::needAuthenticationDialog(){
	if (item().accessibility() == NetworkCatalogItem::SIGNED_IN) {
		return	!item().Link.authenticationManager()->isAuthorised(true).Status;
	}
	return false;
}

bool NetworkCatalogNode::runAuthenticationDialog() {
	AppLog("###### runAuthenticationDialog");
	if (item().accessibility() == NetworkCatalogItem::SIGNED_IN) {
		AppLog("######  SIGNED_IN");
		const NetworkLink &link = item().Link;
		AuthenticationDialog::run(*link.authenticationManager());
		return true;
	}
	else {
		return false;
	}

}
bool NetworkCatalogNode::beforeExpandNode(){
	AppLog("###### beforeExpandNode NetworkCatalogNode ");
	if (!NetworkOperationRunnable::tryConnect()) {
		return false;
	}



	const NetworkLink &link = item().Link;
	if (!link.authenticationManager().isNull()) {
		AppLog("###### beforeExpandNode authenticationManager not Null ");

		NetworkAuthenticationManager &mgr = *link.authenticationManager();
		IsAuthorisedRunnable checker(mgr);
		checker.executeWithUI();
		if (checker.hasErrors()) {
			AppLog("###### beforeExpandNode checker.hasErrors ");
			checker.showErrorMessage();
			return false;
		}
		/*
		if (checker.result() == B3_TRUE) {
			AppLog("###### beforeExpandNode checker.result() == B3_TRUE ");
		}
		if ( mgr.needsInitialization()) {
			AppLog("###### beforeExpandNode mgr needsInitialization ");
		}*/

		if (checker.result() == B3_TRUE && mgr.needsInitialization()) {
			AppLog("###### beforeExpandNode needsInitialization ");
			std::string myErrorMessage = mgr.initialize();
			//InitializeAuthenticationManagerRunnable initializer(mgr);
			//initializer.executeWithUI();
			//if (initializer.hasErrors()) {
			if (!myErrorMessage.empty()){
				AppLog("###### beforeExpandNode !myErrorMessage.empty ");
				LogOutRunnable logout(mgr);
				logout.executeWithUI();
			}
		}
	}

//	if (myNode.myChildrenItems.empty()) {
//		myNode.updateChildren();
//	}
//	myNode.expandOrCollapseSubtree();
//	FBReader::Instance().refreshWindow();
	AppLog("###### beforeExpandNode return true ");
	return true;
}
void NetworkCatalogNode::requestChildren(shared_ptr<ZLExecutionData::Listener> listener) {
	if (children().empty())
		updateChildren();
	//else
	//	listener->finished();
}

NetworkCatalogItem &NetworkCatalogNode::item() {
//	AppLog("item()");
	return (NetworkCatalogItem&)*myItem;
}

const NetworkItem::List &NetworkCatalogNode::childrenItems() {
	return myChildrenItems;
}


const ZLResource &NetworkCatalogNode::resource() const {
	return ZLResource::resource("networkView")["libraryItemNode"];
}

std::string NetworkCatalogNode::title() const {
	return myItem->Title;
}

std::string NetworkCatalogNode::subtitle() const {
	return ((const NetworkCatalogItem&)*myItem).Summary;
}



std::string NetworkCatalogNode::imageUrl() const {
	const std::string &url = myItem->URLByType[NetworkItem::URL_COVER];
	if (url.empty()) {
		if (ZLTreeTitledNode *node = zlobject_cast<ZLTreeTitledNode*>(parent()))
			return node->imageUrl();
	} else if (url.find(':') == std::string::npos) {
		return FBNode::defaultImageUrl(url);
	}
	return url;
}


void NetworkCatalogNode::updateChildren() {
	//if (isOpen()) {
	//	open(false);
	//}
	clear();

	myChildrenItems.clear();
	//LoadSubCatalogRunnable loader(item(), myChildrenItems);
	//loader.executeWithUI();
	item().setChildrenReceiveListner(new NetworkChildrenReceiveListner(this));
	std::string myErrorMessage = item().loadChildren(myChildrenItems);


/*
	//if (loader.hasErrors()) {
	if (!myErrorMessage.empty()) {
		//showErrorMessage(myErrorMessage);
		//loader.showErrorMessage();
	} else if (myChildrenItems.empty()) {
		ZLDialogManager::Instance().informationBox(ZLResourceKey("emptyCatalogBox"));
	}

	bool hasSubcatalogs = false;
	for (NetworkItem::List::iterator it = myChildrenItems.begin(); it != myChildrenItems.end(); ++it) {
		if ((*it)->typeId() == NetworkCatalogItem::TYPE_ID) {
			hasSubcatalogs = true;
			break;
		}
	}

	if (hasSubcatalogs) {
		for (NetworkItem::List::iterator it = myChildrenItems.begin(); it != myChildrenItems.end(); ++it) {
			NetworkNodesFactory::createNetworkNode(this, *it);
		}
	} else {
		NetworkNodesFactory::fillAuthorNode(this, myChildrenItems);
	}*/
	FBReader::Instance().invalidateAccountDependents();


}

void NetworkCatalogNode::onChildrenReceived() {
	AppLog("###### NetworkCatalogNode::onChildrenReceived");
	if (myChildrenItems.empty()) return;
	AppLog("###### add children");
	bool hasSubcatalogs = false;
	for (NetworkItem::List::iterator it = myChildrenItems.begin(); it != myChildrenItems.end(); ++it) {
		if ((*it)->typeId() == NetworkCatalogItem::TYPE_ID) {
			hasSubcatalogs = true;
			break;
		}
	}
	//TODO ????возможны проблемы если CatalogItem смешаны с Аuthor????
	if (hasSubcatalogs) {
		for (NetworkItem::List::iterator it = myChildrenItems.begin(); it != myChildrenItems.end(); ++it) {
			NetworkNodesFactory::createNetworkNode(this, *it);
		}
	} else {
		NetworkNodesFactory::fillAuthorNode(this, myChildrenItems);
	}

	myChildrenItems.clear();

	if (myChildrenUpdateListner) myChildrenUpdateListner->run();
}
/*
void NetworkCatalogNode::updateChildren(shared_ptr<ZLExecutionData::Listener> listener) {
	AppLog("NetworkCatalogNode::updateChildren");
	//AppLog("NetworkCatalogRootNode");
		AppLog("title %s", item().Title.c_str());
		AppLog("Summary %s", item().Summary.c_str());
	myListeners.push_back(listener);
	if (myListeners.size() == 1) {
	//	AppLog("title %s", item().Title.c_str());
	//	AppLog("Summary %s", this->item().Summary.c_str());
		LoadSubCatalogRunnable* r = new LoadSubCatalogRunnable(this);
	}
}
*/
/*
void NetworkCatalogNode::onChildrenReceived(LoadSubCatalogRunnable *runnable) {
	AppLog("NetworkCatalogNode::onChildrenReceived");
	clear();
	myChildrenItems = runnable->children();

	if (runnable->hasErrors()) {
		runnable->showErrorMessage();
	} else if (myChildrenItems.empty()) {
		ZLDialogManager::Instance().informationBox(ZLResourceKey("emptyCatalogBox"));
	}

	bool hasSubcatalogs = false;
	for (NetworkItem::List::iterator it = myChildrenItems.begin(); it != myChildrenItems.end(); ++it) {
		if ((*it)->typeId() == NetworkCatalogItem::TYPE_ID) {
			hasSubcatalogs = true;
			break;
		}
	}

	if (hasSubcatalogs) {
		for (NetworkItem::List::iterator it = myChildrenItems.begin(); it != myChildrenItems.end(); ++it) {
			NetworkNodesFactory::createNetworkNode(this, *it);
		}
	} else {
		NetworkNodesFactory::fillAuthorNode(this, myChildrenItems);
	}
	FBReader::Instance().invalidateAccountDependents();
	for (int i = 0; i < myListeners.size(); ++i) {
		//if (!myListeners.at(i).isNull())
		//	myListeners.at(i)->finished(runnable->errorMessage());
	}
	myListeners.clear();
}
*/
NetworkCatalogNode::OpenInBrowserAction::OpenInBrowserAction(const std::string &url) : myURL(url) {
}

ZLResourceKey NetworkCatalogNode::OpenInBrowserAction::key() const {
	return ZLResourceKey("openInBrowser");
}

void NetworkCatalogNode::OpenInBrowserAction::run() {
	FBReader::Instance().openLinkInBrowser(myURL);
//	finished(std::string());
}

NetworkCatalogNode::ReloadAction::ReloadAction(NetworkCatalogNode &node) : myNode(node) {
}

ZLResourceKey NetworkCatalogNode::ReloadAction::key() const {
	return ZLResourceKey("reload");
}

bool NetworkCatalogNode::ReloadAction::makesSense() const {
//	return myNode.isOpen();
	return true;
}

void NetworkCatalogNode::ReloadAction::run() {
	if (!NetworkOperationRunnable::tryConnect()) {
	//	finished(std::string());
		return;
	}

	myNode.updateChildren();
	myNode.updated();
//	finished(std::string());
//	myNode.expandOrCollapseSubtree();
//	FBReader::Instance().refreshWindow();
}

void NetworkCatalogNode::reloadItem(shared_ptr<NetworkItem> item) {
	myItem = item;
	updated();
}

shared_ptr<ZLImage> NetworkCatalogNode::lastResortCoverImage() const {
	return 0;
//	return ((FBReaderNode*)parent())->image();
}

shared_ptr<ZLImage> NetworkCatalogNode::extractCoverImage() const {
	AppLog("NetworkCatalogNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-books.png");
}

bool NetworkCatalogNode::imageIsUploaded() const{
	return true;
}

shared_ptr<ZLImage> NetworkCatalogNode::image() const {
	AppLog("NetworkCatalogNode::image()");
	const std::string &url = myItem->URLByType[NetworkItem::URL_COVER];
	AppLog("NetworkCatalogNode::image url=%s",url.c_str());
	if (url.empty()) {
		return FBNode::defaultCoverImage("booktree-books.png");
		//return lastResortCoverImage();
	}
	AppLog("getImageByUrl");
	shared_ptr<ZLImage> image = NetworkCatalogUtil::getImageByUrl(url);
	if (!image.isNull()) {
		return image;
	}
	AppLog("FBNode::defaultCoverImage");
//	if (url.find(':') == std::string::npos) {
//		return defaultCoverImage(url);
//	}

//	return lastResortCoverImage();
	//return shared_ptr<ZLImage>();
	return FBNode::defaultCoverImage("booktree-books.png");
}

