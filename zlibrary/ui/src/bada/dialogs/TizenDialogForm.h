/*
 * TizenDialogForm.h
 *
 *  Created on: Jul 23, 2013
 *      Author: Alex
 */

#ifndef TIZENDIALOGFORM_H_
#define TIZENDIALOGFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>

#include <FContent.h>


#include <ZLOptionsDialog.h>

class TizenDialogForm :
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::Controls::IFormBackEventListener,
    public Tizen::Ui::Controls::IGroupedTableViewItemProvider,
    public Tizen::Ui::Controls::IGroupedTableViewItemEventListener
{
public:
	TizenDialogForm();
	virtual ~TizenDialogForm();

public:
	bool Initialize(const char *title, bool showApplyButton);
	void SetPreviousForm(Tizen::Ui::Controls::Form* preForm);

	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);

	   // IGroupedTableViewItemEventListener
	    virtual void OnGroupedTableViewGroupItemStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView, int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status);
	    virtual void OnGroupedTableViewItemStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView, int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem, Tizen::Ui::Controls::TableViewItemStatus status);
	    virtual void OnGroupedTableViewContextItemActivationStateChanged(Tizen::Ui::Controls::GroupedTableView& tableView, int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewContextItem* pContextItem, bool activated);

	    // IGroupedTableViewItemProvider
	    virtual int GetGroupCount(void);
	    virtual int GetItemCount(int groupIndex);
	    virtual Tizen::Ui::Controls::TableViewGroupItem* CreateGroupItem(int groupIndex, int itemWidth);
	    virtual bool DeleteGroupItem(int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem);
	    virtual void UpdateGroupItem(int groupIndex, Tizen::Ui::Controls::TableViewGroupItem* pItem);
	    virtual Tizen::Ui::Controls::TableViewItem* CreateItem(int groupIndex, int itemIndex, int itemWidth);
	    virtual bool DeleteItem(int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	    virtual void UpdateItem(int groupIndex, int itemIndex, Tizen::Ui::Controls::TableViewItem* pItem);
	    virtual int GetDefaultItemHeight(void);
	    virtual int GetDefaultGroupItemHeight(void);

public:

	Tizen::Ui::Controls::Form*	pPreviousForm;
	shared_ptr<ZLOptionsDialog> __badaOptionsDialog;
	std::vector<shared_ptr<ZLDialogContent> > myTabs;

protected:
	bool showApplyButton;
	Tizen::Ui::Controls::GroupedTableView* __pTableView;

};

#endif /* TIZENDIALOGFORM_H_ */
