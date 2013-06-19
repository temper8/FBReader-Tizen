/*
 * DialogForm.h
 *
 *  Created on: 24.11.2011
 *      Author: Alex
 */

#ifndef DIALOGFORM_H_
#define DIALOGFORM_H_
#include <FApp.h>
#include <FBase.h>
#include <FUi.h>
#include <FContent.h>

#include <shared_ptr.h>
#include <ZLOptionsDialog.h>


#define	ID_ACT_UPDATE	1700
#define ID_ACT_DELETE	1701
#define ID_ACT_CLOSE	1702
#define ID_BUTTON_CHECKED    1801
#define ID_BUTTON_UNCHECKED  1802

#define ID_LIST_ITEM  			101
#define ID_LIST_TEXT_TITLE  	102
#define ID_LIST_TEXT_SUBTITLE  	103
#define ID_LIST_BITMAP  		104
#define ID_LIST_CHECKBOX  		105
#define ID_LIST_CUSTOM  		106
#define ID_LIST_BITMAP1  		107
#define ID_LIST_BITMAP2  		108
#define ID_LIST_BITMAP3  		109
#define ID_LIST_BITMAP4  		110
#define ID_LIST_TEXT_BITMAP1  		111
#define ID_LIST_TEXT_BITMAP2  		112
#define ID_LIST_TEXT_BITMAP3  		113
#define ID_LIST_TEXT_BITMAP4  		114
#define ID_LIST_BACKGROUND  		115
#define ID_LIST_COLOR  			116

#define ID_OPTIONKEY  300
#define ID_OPTIONMENU_ITEM0 200


class SpinOptionPopup;
class SpinOptionView;
class ComboOptionPopup;
class ComboOptionView;
class ColorComboOptionPopup;
class ColorOptionView;
class ZLbadaOptionsDialog;
class ZLbadaOptionView;
class MenuView;

class OptionListItem : public Tizen::Ui::Controls::CustomListItem {
public:
	OptionListItem(ZLbadaOptionView*  badaOptionView);
	void OnActionPerformed(int actionId);
	ZLbadaOptionView* mybadaOptionView;
};

class DialogForm :
	public Tizen::Ui::Controls::Form,
	public Tizen::Ui::IActionEventListener,
	public Tizen::Ui::Controls::IFormBackEventListener,
    public Tizen::Ui::IGroupedItemEventListener {

 protected:
	bool showApplyButton;
	void ShowOptionMenu(void);
	void HideOptionMenu(void);

	Tizen::Ui::Controls::OptionMenu* __pOptionMenu;
	MenuView* myMenuView;
	void updateMenu();
	void runAction(shared_ptr<ZLRunnableWithKey> action);

 public:
	void setMenuView(MenuView* view);

 public:

    Tizen::Ui::Controls::CustomListItemFormat* __pComboViewListItemFormat;
    Tizen::Ui::Controls::CustomListItemFormat* __pStringViewListItemFormat;
    Tizen::Ui::Controls::CustomListItemFormat* __pSpinViewListItemFormat;
    Tizen::Ui::Controls::CustomListItemFormat* __pBooleanListItemFormat;
    Tizen::Ui::Controls::CustomListItemFormat* __pCustomListItemFormat2;
    Tizen::Ui::Controls::CustomListItemFormat* __pColorListItemFormat;
    Tizen::Ui::Controls::CustomListItemFormat* __pImageViewListItemFormat;
    Tizen::Ui::Controls::CustomListItemFormat* __pButtonViewListItemFormat;
    Tizen::Ui::Controls::CustomListItemFormat* __pStaticTextListItemFormat;

public:
	DialogForm();
	virtual ~DialogForm();

	bool Initialize(const char *title, bool showApplyButton);
	void SetPreviousForm(Tizen::Ui::Controls::Form* preForm);
	//result  AddControls();
	result  AddTab(const char *title);

//protected:

	//Tizen::Ui::Controls::FooterItem* footerItem;


public:
	// Ui
//	int YPos;
//	Tizen::Ui::Controls::ScrollPanel* pScrollPanel;
	Tizen::Ui::Controls::Form*	pPreviousForm;
	//Tizen::Graphics::Rectangle clientArea;
	SpinOptionPopup* __pSpinOptionPopup;
	ComboOptionPopup*	__pComboOptionPopup;
	ColorComboOptionPopup*	__pColorComboOptionPopup;
	//shared_ptr<ZLOptionsDialog>
	shared_ptr<ZLOptionsDialog> __badaOptionsDialog;
	Tizen::Graphics::Bitmap* buttonBmp;
	Tizen::Graphics::Bitmap* buttonBmp2;
	Tizen::Graphics::Bitmap* arrowDownBmp;
    int GroupCount;

    Tizen::Ui::Controls::GroupedList* __pCustomList;
   // Tizen::Ui::Controls::CustomList* __pCustomList;

 //  virtual void OnItemStateChanged(const Tizen::Ui::Control& source, int index, int itemId, int elementId, Tizen::Ui::ItemStatus status);
 //  virtual void OnItemStateChanged(const Tizen::Ui::Control &source, int index, int itemId, Tizen::Ui::ItemStatus status);
    virtual void  OnItemStateChanged (const Tizen::Ui::Control &source, int groupIndex, int itemIndex, int itemId, Tizen::Ui::ItemStatus status);
    virtual void  OnItemStateChanged (const Tizen::Ui::Control &source, int groupIndex, int itemIndex, int itemId, int elementId, Tizen::Ui::ItemStatus status);

	virtual void OnFormBackRequested(Tizen::Ui::Controls::Form& source);


public:

	result	OnInitializing(void);
	result	OnTerminating(void);
	void	OnActionPerformed(const Tizen::Ui::Control& source, int actionId);
    void 	OnUserEventReceivedN(RequestId requestId, Tizen::Base::Collection::IList* pArgs);
	void ShowComboOptionPopup(ComboOptionView* pComboOptionView);
	void ShowColorComboOptionPopup(ColorOptionView* pColorOptionView);
	void ShowSpinOptionPopup(SpinOptionView* pSpinOptionView);

	void DeleteOptionPopup();

};


#endif /* DIALOGFORM_H_ */
