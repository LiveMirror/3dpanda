//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/26 10:54:12_
// 描述:  
//

#ifndef _IUIMANAGER_2014226105412_
#define _IUIMANAGER_2014226105412_

#include "ctrldef.h"

namespace panda
{
	class IButton;
	class IPanel;
	class IFont;
	class IPictureBox;
	class IMenu;
	class IComboBox;
	class ITextBox;
	class ILabel;
	class IScrollBar;
	class ICheckBox;
	class IProgressBar;
	class IDialog;
	class IListBox;
	class ISliderBar;
	class ITabCtrl;
	class IRadioButton;
	class IToolBar;
	class ITreeView;
	class IListView;
	class IFoldPanel;
	class IPropertyGrid;
	class IUiManager
	{
	public:
		virtual IFont*			CeateFont(s32 height, s32 width, const tstring faceName , s32 weight, 
			bool italic = false, bool underline = false, bool strikeOut = false) = 0;

		virtual IButton*		CreateButton(IPanel* parent = NULL) = 0;
		virtual IPictureBox*	CreatePictureBox(IPanel* parent = NULL) = 0;
		virtual IPanel*			CreatePanel(IPanel* parent = NULL) = 0;
		virtual IMenu*			CreateMenu(void) = 0;
		virtual IComboBox*		CreateComboBox(IPanel* parent = NULL) = 0;
		virtual ITextBox*		CreateTextBox(IPanel* parent = NULL) = 0;
		virtual ILabel*			CreateLabel(IPanel* parent = NULL) = 0;
		virtual IScrollBar*		CreateScrollBar(IPanel* parent = NULL) = 0;
		virtual ICheckBox*		CreateCheckBox(IPanel* parent = NULL) = 0;
		virtual IProgressBar*	CreateProgressBar(IPanel* parent = NULL) = 0;
		virtual IDialog*		CreateDialogs(IPanel* parent = NULL) = 0;
		virtual IListBox*		CreateListBox(IPanel* parent = NULL) = 0;
		virtual ISliderBar*		CreateSliderBar(IPanel* parent = NULL) = 0;
		virtual ITabCtrl*		CreateTabCtrl(IPanel* parent = NULL) = 0;
		virtual IRadioButton*	CreateRadioButton(IPanel* parent = NULL) = 0;
		virtual IToolBar*		CreateToolBar(IPanel* parent = NULL) = 0;
		virtual ITreeView*		CreateTreeView(IPanel* parent = NULL) = 0;
		virtual IListView*		CreateListView(IPanel* parent = NULL) = 0;
		virtual IFoldPanel*		CreateFoldPanel(IPanel* parent = NULL) = 0;
		virtual IPropertyGrid*	CreatePropertyGrid(IPanel* parent = NULL) = 0;
		virtual s32				GetWidth(void)const = 0;
		virtual s32				GetHeight(void)const = 0;

		virtual EventHandle&	OnResize(void) = 0;
	};
}

#endif // _IUIMANAGER_2014226105412_