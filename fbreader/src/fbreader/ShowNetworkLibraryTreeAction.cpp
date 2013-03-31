#include "FBReaderActions.h"
//#include <ZLApplication.h>
#include "ZLDialogManager.h"

#include "../network/NetworkItems.h"
#include "../network/NetworkLinkCollection.h"
#include "../network/NetworkLink.h"

#include "../network/SearchResult.h"
#include "../networkTree/NetworkNodes.h"
#include "../networkTree/NetworkNodesFactory.h"


void ShowNetworkLibraryTreeAction::run() {
	shared_ptr<ZLTreeDialog>  myDialog = ZLDialogManager::Instance().createTreeDialog(ZLResourceKey("NetworkTreeDialog"));
	ZLTreeListener::RootNode &rootNode = myDialog->rootNode();
	NetworkLinkCollection &collection = NetworkLinkCollection::Instance();
	AppLog(" NetworkLinkCollection::Instance()");
	std::set<ZLTreeNode*> nodesToDelete;
	ZLTreeNode::List rootChildren = rootNode.children();

	ZLTreeNode::List::iterator nodeIt = rootChildren.begin();
	size_t nodeCount = 0;
	AppLog("collection.size() = %d",collection.size());
	for (size_t i = 0; i < collection.size(); ++i) {
		AppLog("i = %d",i);
		NetworkLink &link = collection.link(i);
//		if (!link.isEnabled()) {
//			continue;
//		}
		bool processed = false;
		AppLog("processed");
		while (nodeIt != rootChildren.end() &&
					 (*nodeIt)->isInstanceOf(NetworkCatalogNode::TYPE_ID)) {
			AppLog("while");
			const NetworkLink &nodeLink = ((NetworkCatalogRootNode*)*nodeIt)->link();
			if (&nodeLink == &link && nodeLink.SiteName == link.SiteName) {
				AppLog("reloadLink() 1");
				((NetworkCatalogRootNode*)*nodeIt)->reloadLink();
				++nodeIt;
				++nodeCount;
				processed = true;
				break;
			} else {
				bool found = false;
				for (size_t j = i + 1; j < collection.size(); ++j) {
					if (&nodeLink == &collection.link(j) && nodeLink.SiteName == collection.link(j).SiteName) {
						found = true;
						AppLog("reloadLink() 2");
						((NetworkCatalogRootNode*)*nodeIt)->reloadLink();
						break;
					}
				}
				if (!found) {
					nodesToDelete.insert(*nodeIt++);
					++nodeCount;
				} else {
					break;
				}
			}
		}

		if (!processed) {
			NetworkCatalogNode *ptr = new NetworkCatalogRootNode(&rootNode, link, nodeCount++);
			//ptr->item().onDisplayItem();
		}
	}

	SearchResultNode *srNode = 0;

	while (nodeIt != rootChildren.end()) {
		ZLTreeNode *node = *nodeIt++;
		++nodeCount;
		if (node->isInstanceOf(SearchResultNode::TYPE_ID)) {
			srNode = (SearchResultNode*)node;
		} else {
			nodesToDelete.insert(node);
		}
	}

	const SearchResult &searchResult = SearchResult::lastSearchResult();
	shared_ptr<NetworkBookCollection> result = searchResult.collection();
	if (result.isNull()) {
		if (srNode != 0) {
			nodesToDelete.insert(srNode);
		}
	} else if (srNode == 0 || srNode->searchResult() != result) {
		if (srNode != 0) {
			nodesToDelete.insert(srNode);
		}
		//srNode = new SearchResultNode(&rootNode, result, searchResult.summary()); // at nodeCount ??? or not???
		NetworkNodesFactory::createSubnodes(srNode, *result);
	}

	for (std::set<ZLTreeNode*>::iterator it = nodesToDelete.begin(); it != nodesToDelete.end(); ++it) {
		ZLTreeNode *node = *it;
		node->parent()->remove(node);
		delete node;
	}

//	if (srNode != 0) {
//		srNode->open(false);
//		srNode->expandOrCollapseSubtree();
//	}

	myDialog->run();
}
/*
void ShowNetworkLibraryTreeAction::makeUpToDate(){
	AppLog("makeUpToDate()");

		ZLTreeListener::RootNode &rootNode = myDialog->rootNode();
		NetworkLinkCollection &collection = NetworkLinkCollection::Instance();
		AppLog(" NetworkLinkCollection::Instance()");
		std::set<ZLTreeNode*> nodesToDelete;
		ZLTreeNode::List rootChildren = rootNode.children();

		ZLTreeNode::List::iterator nodeIt = rootChildren.begin();
		size_t nodeCount = 0;
		AppLog("collection.size() = %d",collection.size());
		for (size_t i = 0; i < collection.size(); ++i) {
			AppLog("i = %d",i);
			NetworkLink &link = collection.link(i);
	//		if (!link.isEnabled()) {
	//			continue;
	//		}
			bool processed = false;
			AppLog("processed");
			while (nodeIt != rootChildren.end() &&
						 (*nodeIt)->isInstanceOf(NetworkCatalogNode::TYPE_ID)) {
				AppLog("while");
				const NetworkLink &nodeLink = ((NetworkCatalogRootNode*)*nodeIt)->link();
				if (&nodeLink == &link && nodeLink.SiteName == link.SiteName) {
					AppLog("reloadLink() 1");
					((NetworkCatalogRootNode*)*nodeIt)->reloadLink();
					++nodeIt;
					++nodeCount;
					processed = true;
					break;
				} else {
					bool found = false;
					for (size_t j = i + 1; j < collection.size(); ++j) {
						if (&nodeLink == &collection.link(j) && nodeLink.SiteName == collection.link(j).SiteName) {
							found = true;
							AppLog("reloadLink() 2");
							((NetworkCatalogRootNode*)*nodeIt)->reloadLink();
							break;
						}
					}
					if (!found) {
						nodesToDelete.insert(*nodeIt++);
						++nodeCount;
					} else {
						break;
					}
				}
			}

			if (!processed) {
				NetworkCatalogNode *ptr = new NetworkCatalogRootNode(&rootNode, link, nodeCount++);
				//ptr->item().onDisplayItem();
			}
		}

		SearchResultNode *srNode = 0;

		while (nodeIt != rootChildren.end()) {
			ZLTreeNode *node = *nodeIt++;
			++nodeCount;
			if (node->isInstanceOf(SearchResultNode::TYPE_ID)) {
				srNode = (SearchResultNode*)node;
			} else {
				nodesToDelete.insert(node);
			}
		}

		const SearchResult &searchResult = SearchResult::lastSearchResult();
		shared_ptr<NetworkBookCollection> result = searchResult.collection();
		if (result.isNull()) {
			if (srNode != 0) {
				nodesToDelete.insert(srNode);
			}
		} else if (srNode == 0 || srNode->searchResult() != result) {
			if (srNode != 0) {
				nodesToDelete.insert(srNode);
			}
			srNode = new SearchResultNode(&rootNode, result, searchResult.summary()); // at nodeCount ??? or not???
			NetworkNodesFactory::createSubnodes(srNode, *result);
		}

		for (std::set<ZLTreeNode*>::iterator it = nodesToDelete.begin(); it != nodesToDelete.end(); ++it) {
			ZLTreeNode *node = *it;
			node->parent()->remove(node);
			delete node;
		}

	//	if (srNode != 0) {
	//		srNode->open(false);
	//		srNode->expandOrCollapseSubtree();
	//	}
}
*/
