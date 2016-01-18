////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-8 23:18:26
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201438231826_H_
#define	_Tian_201438231826_H_

#include "PanelImpl.h"

namespace panda
{
	class IListBoxItem;
	class ListBoxImpl:public PanelImpl
	{
	public:
		ListBoxImpl(void);
		virtual void		OnRender(IGraph2D* graph);
		virtual void		OnMouseMove(MouseEventArgs& e);
		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		UpdateScrollValue(void);

		IListBoxItem*		AddItem(const tstring& text);
		IListBoxItem*		InsertItem(const tstring& text, u32 index);
		IListBoxItem*		GetItem(u32 index)const;
		IListBoxItem*		GetSelItem(void)const;
		void				SetSelItemIndex(s32 index);
		void				RemoveItem(u32 index);
		void				Clear(void);
	public:
		typedef std::vector<IListBoxItem*>	CtrlVector;
		CtrlVector		mChilds;
		s32				mMouseOnIndex;
		s32				mSelIndex;
		EventCtrl		mOnSelectedChange;
	};
}

#endif _Tian_201438231826_H_