//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/16 9:46:22_
// 描述:  
//

#ifndef _TREELISTIMPL_201441694622_
#define _TREELISTIMPL_201441694622_

#include "PanelImpl.h"

namespace panda
{
	class IListViewItem;
	class ListViewImpl:public PanelImpl
	{
	public:
		ListViewImpl(void);
		virtual void		SetSize(s32 width, s32 height);
		IListViewItem*		AddItem(const tstring& name);
		void				SetItemSize(s32 width, s32 height);
		void				NoticItemSelected(IListViewItem* item);
		void				NoticItemDClick(IListViewItem* item);
		void				ClearAll(void);
	protected:
		void		CalculatePos(s32 index, Vector2Dn& pos);
		void		ReCalculate();
	public:
		Size			mTileSize;
		IListViewItem*	mSeletedItem;
		EventCtrl		mOnSelectChanged;
		EventCtrl		mOnDClick;
	};
}

#endif // _TREELISTIMPL_201441694622_