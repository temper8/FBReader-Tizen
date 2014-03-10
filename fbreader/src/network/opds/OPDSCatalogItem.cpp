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
#include <ZLExecutionData.h>
#include <ZLNetworkManager.h>
#include <ZLTimeManager.h>

#include "OPDSCatalogItem.h"
#include "OPDSLink.h"
#include "OPDSXMLParser.h"
#include "NetworkOPDSFeedReader.h"


OPDSCatalogItemLoader::OPDSCatalogItemLoader(const OPDSLink &link, const std::string &url,
                                 NetworkItem::List &children, shared_ptr<ZLExecutionData::Listener> listener)
    : myLink(link), myChildren(children), myData(myLink), myListener(listener), myHolder(this) {
	AppLog("OPDSCatalogItemLoader");
	shared_ptr<ZLExecutionData> networkData = myLink.createNetworkData(url, myData);
	AppLog("createNetworkData");
	networkData->setListener(myHolder);
	AppLog("setListener");
	ZLNetworkManager::Instance().perform(networkData);
}

OPDSCatalogItemLoader::~OPDSCatalogItemLoader() {
}

void OPDSCatalogItemLoader::showPercent(int ready, int full) {
	myListener->showPercent(ready, full);
}

void OPDSCatalogItemLoader::finished(const std::string &error) {
	if (!error.empty()) {
	//	myListener->finished(error);
	//	ZLTimeManager::deleteLater(myHolder);
		myHolder.reset();
		return;
	}
	myChildren.insert(myChildren.end(), myData.Items.begin(), myData.Items.end());
	shared_ptr<ZLExecutionData> networkData = myData.resume();
	if (networkData.isNull()) {
//		myListener->finished();
	//	ZLTimeManager::deleteLater(myHolder);
		myHolder.reset();
	} else {
		networkData->setListener(myHolder);
		ZLNetworkManager::Instance().perform(networkData);
	}
}

OPDSCatalogItem::OPDSCatalogItem(
	const OPDSLink &link,
	const std::string &title,
	const std::string &summary,
	const std::map<URLType,std::string> &urlByType,
	VisibilityType visibility,
	CatalogType catalogType
) : NetworkCatalogItem(link, title, summary, urlByType, visibility, catalogType) {
	myNetData = new NetworkOperationData(Link);
}

std::string OPDSCatalogItem::loadChildren(NetworkItem::List &children) {
	AppLog("####### OPDSCatalogItem::loadChildren");
	myLoadedChildren = &children;
	//NetworkOperationData data(Link);
	myNetData->myChildrenReceiveListner = new OPDSCatalogChildrenReceiveListner(this);
	AppLog("####### OPDS Link SiteName = %s", Link.SiteName.c_str());
	AppLog("####### OPDS Link title= %s", Link.getTitle().c_str());
	shared_ptr<ZLExecutionData> networkData =
		((OPDSLink&)Link).createNetworkData(URLByType[URL_CATALOG], *myNetData);

	//while (!networkData.isNull()) { делаю бяку, чтоб не показывались следующие страницы, если список книг длинный.
	if (!networkData.isNull()) {
		std::string error = ZLNetworkManager::Instance().perform(networkData);
		if (!error.empty()) {
			return error;
		}
		AppLog("####### OPDSCatalogItem::loadChildren perform(networkData");
		//children.insert(children.end(), data.Items.begin(), data.Items.end());
		networkData = myNetData->resume();
	}

	return "";
}

void OPDSCatalogItem::onChildrenReceived(){
	AppLog("####### OPDSCatalogItem::onChildrenReceived");

	myLoadedChildren->insert(myLoadedChildren->end(), myNetData->Items.begin(), myNetData->Items.end());
	myNetData->Items.clear();
	if (myChildrenReceiveListner) myChildrenReceiveListner->run();
}
