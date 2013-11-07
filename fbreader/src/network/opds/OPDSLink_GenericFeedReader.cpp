/*
 * Copyright (C) 2008-2010 Geometer Plus <contact@geometerplus.com>
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
#include <ZLNetworkUtil.h>
#include <ZLMimeType.h>
#include <ZLExecutionData.h>
#include <ZLNetworkManager.h>

#include "OPDSLink_GenericFeedReader.h"
#include "OpenSearchXMLReader.h"

OPDSLink::GenericFeedReader::GenericFeedReader(
	std::vector<shared_ptr<NetworkLink> >& links
) :
	myLinks(links) {
}

void OPDSLink::GenericFeedReader::processFeedStart() {
}

void OPDSLink::GenericFeedReader::processFeedMetadata(shared_ptr<OPDSFeedMetadata>) {
	AppLog("####### processFeedMetadata");
}


void OPDSLink::GenericFeedReader::processFeedEnd() {
}

void OPDSLink::GenericFeedReader::processFeedEntry(shared_ptr<OPDSEntry> entry) {
	AppLog("####### GenericFeedReader::processFeedEntry");
	std::map<std::string,std::string> links;
	std::string iconURL;
	for (size_t i = 0; i < entry->links().size(); ++i) {
		ATOMLink &link = *(entry->links()[i]);
		const std::string &href = link.href();
		const std::string &rel = link.rel();
	AppLog("####### href = %s",href.c_str());
	AppLog("####### rel = %s",rel.c_str());
		if (rel == "search") {
			links[rel] = OpenSearchXMLReader::convertOpenSearchURL(href);
		} else if (rel == "") {
			links[NetworkLink::URL_MAIN] = href;
		} else if (rel == "http://data.fbreader.org/catalog/sign-in") {
			links["signIn"] = href;
		} else if (rel == "http://data.fbreader.org/catalog/sign-out") {
			links["signOut"] = href;
		} else if (rel == "http://data.fbreader.org/catalog/refill-account") {
			links["refillAccount"] = href;
		} else if (rel == "http://data.fbreader.org/catalog/recover-password") {
			links["recoverPassword"] = href;
		} else if (rel == "http://opds-spec.org/thumbnail") {
			iconURL = href;
		} else {
			links[rel] = href;
		}
	}
	if (entry->title().empty() || links[NetworkLink::URL_MAIN].empty()) {
		return;
	}
	AppLog("entry->title().empty()");
	if (entry->id() == 0) {
		return;
	}
	//AppLog("entry->id() == 0");
	std::string id = entry->id()->uri();
	std::string summary = entry->summary();
	AppLog("####### OPDSLink id = %s",id.c_str());
	AppLog("####### OPDSLink summary = %s",summary.c_str());
	shared_ptr<NetworkLink> link = new OPDSLink(id.substr(25, -1));
	AppLog("####### OPDSLink new");
	link->setTitle(entry->title());
	link->setSummary(summary);
	link->setIcon(iconURL);
	link->setLinks(links);
	link->setPredefinedId(id);
	link->setUpdated(entry->updated());
	link->init();
	myLinks.push_back(link);
	AppLog("####### OPDSLink size =%d",myLinks.size());
	AppLog("####### OPDSLink title =%s",entry->title().c_str());
}


