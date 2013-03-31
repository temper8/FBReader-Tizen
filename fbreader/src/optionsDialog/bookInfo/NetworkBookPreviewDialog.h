/*
 * NetworkBookPreviewDialog.h
 *
 *  Created on: 29.01.2012
 *      Author: Alex
 */

#ifndef NETWORKBOOKPREVIEWDIALOG_H_
#define NETWORKBOOKPREVIEWDIALOG_H_
#include <string>

#include <ZLOptionEntry.h>

#include "../../formats/FormatPlugin.h"
#include "../../networkTree/NetworkNodes.h"

class NetworkBookPreviewDialog {
public:
	NetworkBookPreviewDialog(NetworkBookNode *node);
	virtual ~NetworkBookPreviewDialog();

	ZLOptionsDialog &dialog();

private:
	shared_ptr<ZLOptionsDialog> myDialog;
	NetworkBookNode *myNode;
	//shared_ptr<Book> myBook;

	//friend class BookPreviewTitleEntry;
	//friend class BookOpenAction;

};



inline ZLOptionsDialog &NetworkBookPreviewDialog::dialog() { return *myDialog; }
#endif /* NETWORKBOOKPREVIEWDIALOG_H_ */
