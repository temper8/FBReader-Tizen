/*
 * TizenComboOptionForm.h
 *
 *  Created on: Aug 17, 2013
 *      Author: Alex
 */

#ifndef TIZENCOMBOOPTIONFORM_H_
#define TIZENCOMBOOPTIONFORM_H_

#include <FBase.h>
#include <FUi.h>
#include <FApp.h>

#include <ZLOptionEntry.h>

class TizenComboOptionView;

class TizenComboOptionForm :
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::Controls::IFormBackEventListener,
	public Tizen::Ui::Controls::IListViewItemEventListener,
	public Tizen::Ui::Controls::IListViewItemProvider
{
public:
	//TizenComboOptionForm(const std::string &name, ZLComboOptionEntry& comboOption);
	//TizenComboOptionForm(TizenComboOptionView* view);
	TizenComboOptionForm();
	virtual ~TizenComboOptionForm();

	Tizen::Ui::Controls::Form*	pPreviousForm;
    Tizen::Ui::Controls::ListView* pListView;



    void Initialize(TizenComboOptionView* view);
    virtual result OnInitializing(void);
	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);


    // IListViewItemEventListener
    virtual void OnListViewContextItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListContextItemStatus state);
    virtual void OnListViewItemStateChanged(Tizen::Ui::Controls::ListView &listView, int index, int elementId, Tizen::Ui::Controls::ListItemStatus status);
    virtual void OnListViewItemSwept(Tizen::Ui::Controls::ListView &listView, int index, Tizen::Ui::Controls::SweepDirection direction);

    // IListViewItemProvider
    virtual Tizen::Ui::Controls::ListItemBase* CreateItem(int index, int itemWidth);
    virtual bool DeleteItem(int index, Tizen::Ui::Controls::ListItemBase* pItem, int itemWidth);
    virtual int GetItemCount(void);
private:
    int selectedIndex;
    TizenComboOptionView* myView;
  //  const ZLComboOptionEntry& myComboOption;
  //  const std::string &myName;

};

#endif /* TIZENCOMBOOPTIONFORM_H_ */
