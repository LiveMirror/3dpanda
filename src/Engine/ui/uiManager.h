////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-24 22:17:45
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014224221745_H_
#define	_Tian_2014224221745_H_

#include "base/Config.h"
#include "../TypeDef.h"
#include "base/Rect.h"
#include "ui/IUiManager.h"
#include "ui/IUiInput.h"

namespace panda
{
	class IGraph2D;
	class IControl;
	class RenderSystem;
	class IFont;
	class ToolTipImpl;
	
	/*
	*
	*/
	class uiManager:public IUiManager, public IUiInput
	{
	public:
		uiManager(RenderSystem* renderSys);
		virtual IFont*			CeateFont(s32 height, s32 width, const tstring faceName , s32 weight = 500, 
			bool italic = false, bool underline = false, bool strikeOut = false);
		virtual IButton*		CreateButton(IPanel* parent = NULL);
		virtual IPictureBox*	CreatePictureBox(IPanel* parent = NULL);
		virtual IPanel*			CreatePanel(IPanel* parent = NULL);
		virtual IMenu*			CreateMenu(void);
		virtual IComboBox*		CreateComboBox(IPanel* parent = NULL);
		virtual ITextBox*		CreateTextBox(IPanel* parent = NULL);
		virtual ILabel*			CreateLabel(IPanel* parent = NULL);
		virtual IScrollBar*		CreateScrollBar(IPanel* parent = NULL);
		virtual ICheckBox*		CreateCheckBox(IPanel* parent = NULL);
		virtual IProgressBar*	CreateProgressBar(IPanel* parent = NULL);
		virtual IDialog*		CreateDialogs(IPanel* parent = NULL);
		virtual IListBox*		CreateListBox(IPanel* parent = NULL);
		virtual ISliderBar*		CreateSliderBar(IPanel* parent = NULL);
		virtual ITabCtrl*		CreateTabCtrl(IPanel* parent = NULL);
		virtual IRadioButton*	CreateRadioButton(IPanel* parent = NULL);
		virtual IToolBar*		CreateToolBar(IPanel* parent = NULL);
		virtual ITreeView*		CreateTreeView(IPanel* parent = NULL);
		virtual IListView*		CreateListView(IPanel* parent = NULL);
		virtual IFoldPanel*		CreateFoldPanel(IPanel* parent = NULL);
		virtual IPropertyGrid*	CreatePropertyGrid(IPanel* parent = NULL);
		virtual EventHandle&	OnResize(void);

		/*********************************************************************************/
		virtual void		OnMouseMove(MouseEventArgs& e);
		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseDClick(MouseEventArgs& e);
		virtual void		OnMouseUp(MouseEventArgs& e);
		virtual void		OnMouseWheel(MouseEventArgs& e);
		virtual void		OnKeyDown(KeyEventArgs& e);
		virtual void		OnChar(s32 key);

		virtual s32			GetWidth(void)const;
		virtual s32			GetHeight(void)const;

		void			Render(IGraph2D* graph, s32 tick);
		void			AddChild(IControl* ctrl);
		void			SetPopUpCtrl(IControl* pCtrl);
		void			SetFocus(IControl* pCtrl);
		void			SetCapture(IControl* pCtrl);
		void			SetModeDialog(IDialog* pDialog);
		void			RealeseCapture(void);
		void			Resize(s32 width, s32 height);
		void			ResetHover(void);
		void			DeviceLost(void);
		void			ResetDevice(void);

		void			RemoveCtrl(IControl* ctrl);

		void			BringToFront(IControl* pCtrl);
		void			SendToBack(IControl* pCtrl);
	public:
		CtrlList		mModeDialogs;
		s32				mMouseOverTime;
		s32				mLaskTick;
		RenderSystem*	mRenderSys;
		IFont*			mDefaultFont;
		Rect			mClientRect;
		IDialog*		mModeDialog;		// 模式对话框
		CtrlList		mChilds;
		IControl*		mMouseOn;
		IControl*		mCapture;
		IControl*		mPopupCtrl;
		IControl*		mFocus;
		ToolTipImpl*	mToolTip;

		bool			mHasNoticeHover;
		Vector2Dn		mOldPoint;
		EventHandle		mOnResize;
	};
}

#endif _Tian_2014224221745_H_