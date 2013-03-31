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

shared_ptr<ZLImage> NetworkCatalogNode::lastResortCoverImage() const {
	return 0;
//	return ((FBReaderNode*)parent())->image();
}

void NetworkCatalogNode::updateChildren() {
	//if (isOpen()) {
	//	open(false);
	//}
	clear();

	myChildrenItems.clear();
	LoadSubCatalogRunnable loader(item(), myChildrenItems);
	loader.executeWithUI();

	if (loader.hasErrors()) {
		loader.showErrorMessage();
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

shared_ptr<ZLImage> NetworkCatalogNode::extractCoverImage() const {
	AppLog("NetworkCatalogNode::extractCoverImage");
	return FBNode::defaultCoverImage("booktree-folder.png");
}


shared_ptr<ZLImage> NetworkCatalogNode::image() const {
	AppLog("NetworkCatalogNode::image()");
	const std::string &url = myItem->URLByType[NetworkItem::URL_COVER];
	AppLog("url=%s",url.c_str());
	if (url.empty()) {
		return lastResortCoverImage();
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
	return FBNode::defaultCoverImage("booktree-folder.png");
}

