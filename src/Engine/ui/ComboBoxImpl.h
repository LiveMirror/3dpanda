//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/3/2 14:26:28_
// 描述:  
//

#ifndef _COMBOBOXIMPL_201432142628_
#define _COMBOBOXIMPL_201432142628_

#include "ControlImpl.h"

namespace panda
{
	class IListBoxItem;
	class IListBox;
	class ComboBoxImpl:public ControlImpl
	{
	public:
		ComboBoxImpl(void);

		virtual void			OnRender(IGraph2D* graph);
		virtual void			OnBindUiMgr(uiManager* uiMgr);
		virtual IListBoxItem*	AddItem(const tstring& text);

		virtual void			SetSize(s32 width, s32 height);
		virtual void			OnMouseDown(MouseEventArgs& e);
		virtual void			OnMouseWheel(MouseEventArgs& e);
		virtual void			OnMouseEnter();
		virtual void			OnMouseLevae();

		void			Clear(void);

		void			SetNumOfShow(u32 num);

		bool			OnSelectedChange(IControl* pCtrl);
		bool			OnListMouseDown(IControl* pCtrl, MouseEventArgs& e);
		void			SetSelItem(IListBoxItem* item);
		void			SetSelItem(s32 index);

		void			ResizeListCtrl(void);
	public:
		IListBox*		mListBox;
		IListBoxItem*	mSelItem;
		EventCtrl		mOnSelChange;
		bool			mMouseOn;
		u32				mNumOfShow;
	};
}

#endif // _COMBOBOXIMPL_201432142628_