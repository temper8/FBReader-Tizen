/*
 * NetworkBookPreviewDialog.cpp
 *
 *  Created on: 29.01.2012
 *      Author: Alex
 */
#include <algorithm>

#include <ZLDialogManager.h>
#include <ZLOptionsDialog.h>
#include <ZLOptionEntry.h>
#include <ZLFile.h>
#include <ZLLanguageList.h>
#include <ZLStringUtil.h>

#include <optionEntries/ZLStringInfoEntry.h>
#include <optionEntries/ZLSimpleOptionEntry.h>
#include <optionEntries/ZLLanguageOptionEntry.h>

#include "BookInfoDialog.h"

#include "../../library/Library.h"
#include "../../encodingOption/EncodingOptionEntry.h"
#include "../../library/Book.h"
#include "../../library/Tag.h"
#include "../../library/Author.h"
#include "BookPreviewDialog.h"
#include <FBase.h>
#include "../../tree/FBNode.h"
#include "../../fbreader/FBReader.h"
#include "../../formats/FormatPlugin.h"

#include "NetworkBookPreviewDialog.h"
#include "../../networkActions/NetworkActions.h"
#include "PreviewEntries.h"


class NetworkBookMenuEntry : public ZLMenuOptionEntry {

public:
	NetworkBookMenuEntry(NetworkBookNode* node);

	const std::string &initialValue() const;
	void onAccept(const std::string &value);
};

NetworkBookMenuEntry::NetworkBookMenuEntry(NetworkBookNode* node) : ZLMenuOptionEntry(node->actions()) {
}

const std::string &NetworkBookMenuEntry::initialValue() const {
	return std::string();
}

void NetworkBookMenuEntry::onAccept(const std::string &value) {
	//myPreviewDialog.myBook->setTitle(value);
}



class NetworkBookPictureEntry : public ZLPictureOptionEntry {

public:
	NetworkBookPictureEntry(NetworkBookNode* node);

	const std::string &initialValue() const;
	void onAccept(const std::string &value);
};

NetworkBookPictureEntry::NetworkBookPictureEntry(NetworkBookNode* node) : ZLPictureOptionEntry(node->image(),node->actions()) {
}

const std::string &NetworkBookPictureEntry::initialValue() const {
	return std::string();
}

void NetworkBookPictureEntry::onAccept(const std::string &value) {
	//myPreviewDialog.myBook->setTitle(value);
}


NetworkBookPreviewDialog::NetworkBookPreviewDialog(NetworkBookNode *node): myNode(node) {
	// TODO Auto-generated constructor stub
	//myDialog = ZLDialogManager::Instance().createOptionsDialog(ZLResourceKey("InfoDialog"), new BookOpenAction(myBook));
	myDialog = ZLDialogManager::Instance().createOptionsDialog(ZLResourceKey("InfoDialog"),0, true);


	AppLog("myDialog->createTab");
	const NetworkBookItem &book = node->book();

	if (!myNode->myIsInitialized) {
		myNode->init();
		myNode->myIsInitialized = true;
		}
	myDialog->setMenuEntry( new NetworkBookMenuEntry(myNode));

	ZLDialogContent &commonTab = myDialog->createTab(ZLResourceKey("Cover"));

	commonTab.addOption(ZLResourceKey("cover"), new NetworkBookPictureEntry(myNode));
	//commonTab.addOption(ZLResourceKey("title"), new BookPreviewTitleEntry(*this));
	ZLDialogContent &BookInfoTab = myDialog->createTab(ZLResourceKey("BookInfo"));
	BookInfoTab.addOption(ZLResourceKey("title"), new StaticTextEntry(node->title()));
	BookInfoTab.addOption(ZLResourceKey("authors"), new StaticTextEntry(node->subtitle()));
	BookInfoTab.addOption(ZLResourceKey("seriesTitle"), new StaticTextEntry(book.SeriesTitle));

	AppLog("commonTab.addOption title");

	std::string text = "Price";

	shared_ptr<BookReference> reference = book.reference(BookReference::BUY);
	if (!reference.isNull()) {
		text = text + ((BuyBookReference&)*reference).Price;
	//	BookInfoTab.addOption(ZLResourceKey("price"), new ButtonEntry(new NetworkBookBuyDirectlyAction(myNode, book)));

	}

//	BookInfoTab.addOption(ZLResourceKey("price"), new StringEntry(text));
//	BookInfoTab.addOption(ZLResourceKey("seriesTitle"), new StringEntry(book.SeriesTitle));

	ZLDialogContent &SummaryTab = myDialog->createTab(ZLResourceKey("Summary"));
	//SummaryTab.addOption(ZLResourceKey("title"), new StringEntry(book.Summary));
	SummaryTab.addOption(ZLResourceKey("title"), new StaticTextEntry(book.Summary));

//	commonTab.addOption(ZLResourceKey("title"), new ButtonEntry(new NetworkBookDownloadAction(myNode, book, false)));

	if (!book.reference(BookReference::DOWNLOAD_FULL).isNull() ||
				!book.reference(BookReference::DOWNLOAD_FULL_CONDITIONAL).isNull()) {
		//commonTab.addOption(ZLResourceKey("title"), new ButtonEntry(new NetworkBookReadAction(myNode, book, false)));
		//SummaryTab.addOption(ZLResourceKey("title"), new ButtonEntry(new NetworkBookDownloadAction(myNode, book, false)));
		//commonTab.addOption(ZLResourceKey("title"), new ButtonEntry(new NetworkBookDeleteAction(book)));
		}
		if (!book.reference(BookReference::DOWNLOAD_DEMO).isNull()) {
			//SummaryTab.addOption(ZLResourceKey("title"), new ButtonEntry(new NetworkBookReadAction(myNode, book, true)));//
			//SummaryTab.addOption(ZLResourceKey("title"), new ButtonEntry(new NetworkBookDownloadAction(myNode, book, true, myNode->resource()["demo"].value())));

			//registerTreeAction(new NetworkBookReadAction(this, book, true));
			//registerTreeAction(new NetworkBookDownloadAction(this, book, true, resource()["demo"].value()));
		}
		if (!book.reference(BookReference::BUY).isNull()) {
			//SummaryTab.addOption(ZLResourceKey("title"), new ButtonEntry(new NetworkBookBuyDirectlyAction(myNode, book)));
			//registerTreeAction(new NetworkBookBuyDirectlyAction(this, book));
		} else if (!book.reference(BookReference::BUY_IN_BROWSER).isNull()) {
			//SummaryTab.addOption(ZLResourceKey("title"), new ButtonEntry(new NetworkBookBuyInBrowserAction(book)));
			//registerTreeAction(new NetworkBookBuyInBrowserAction(book));
		}
}
/*
 	const NetworkBookItem &book = this->book();

	if (!book.reference(BookReference::DOWNLOAD_FULL).isNull() ||
			!book.reference(BookReference::DOWNLOAD_FULL_CONDITIONAL).isNull()) {
		registerTreeAction(new NetworkBookReadAction(this, book, false));
		//registerTreeAction(new NetworkBookDownloadAction(this, book, false));
		registerTreeAction(new NetworkBookDeleteAction(book));
	}
	if (!book.reference(BookReference::DOWNLOAD_DEMO).isNull()) {
		registerTreeAction(new NetworkBookReadAction(this, book, true));
		//registerTreeAction(new NetworkBookDownloadAction(this, book, true, resource()["demo"].value()));
	}
	if (!book.reference(BookReference::BUY).isNull()) {
		//registerTreeAction(new NetworkBookBuyDirectlyAction(this, book));
	} else if (!book.reference(BookReference::BUY_IN_BROWSER).isNull()) {
		registerTreeAction(new NetworkBookBuyInBrowserAction(book));
	}
 */
NetworkBookPreviewDialog::~NetworkBookPreviewDialog() {
	// TODO Auto-generated destructor stub
}
