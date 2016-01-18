//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/16 9:35:41_
// 描述:  
//

#ifndef _ITREELIST_201441693541_
#define _ITREELIST_201441693541_

#include "IPanel.h"

namespace panda
{
	class ListViewItemImpl;
	class IListViewItem:public IControl
	{
	public:
		IListViewItem(void);
		virtual bool		GetSelected(void)const;
		
		virtual void				SetTitle(const tstring& title);
		virtual const tstring&		GetTitle(void)const;

		// 
		virtual void		SetSize(s32 width, s32 height);
		virtual void		SetPos(s32 x, s32 y);
		
	};

	class ListViewImpl;
	class IListView:public IPanel
	{
	public:
		IListView(void);
		IListView(ListViewImpl* impl);
		virtual IListViewItem*		AddItem(const tstring& name);
		virtual IListViewItem*		GetSelectedItem(void)const;
		virtual void				SetItemSize(s32 width, s32 height);
		virtual void				ClearAll(void);
		virtual EventCtrl&			OnSelectChanged(void);
		virtual EventCtrl&			OnItemDClick(void);
		
	};
}

#endif // _ITREELIST_201441693541_