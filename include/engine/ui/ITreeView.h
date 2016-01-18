////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-10 23:43:21
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014410234321_H_
#define	_Tian_2014410234321_H_

#include "IPanel.h"

namespace panda
{
	class TreeViewItemImpl;
	class ITreeView;
	class ITreeViewItem
	{
	public:
		ITreeViewItem(void);

		virtual ITreeView*		GetTreeView(void)const;
		virtual bool			IsSelected(void)const;

		virtual ITreeViewItem*	GetParentItem(void)const;


		virtual bool			IsExpanded(void)const;
		virtual void			Expand(void);
		virtual void			ExpandAll(void);

		virtual void			Collapse(void);
		virtual void			Toggle(void);

		virtual s32				GetItemNum(void)const;
		virtual ITreeViewItem*	AddItem(const tstring& str);
		virtual ITreeViewItem*	InsertItem(const tstring& str, u32 index);

		virtual void			SetText(const tstring& text);
		virtual const tstring&	GetText(void)const;

		virtual bool			GetVisible(void)const;
		virtual void			SetVisible(bool visible);

		virtual void			SetUserData(s32 data);
		virtual s32				GetUserData(void)const;
	public:
		TreeViewItemImpl*		mImpl;
	};


	class TreeViewImpl;
	/*
	* 
	*/
	class ITreeView:public IPanel
	{
	public:
		ITreeView(void);
		ITreeView(TreeViewImpl* impl);

		virtual s32				GetItemNum(void)const;
		virtual ITreeViewItem*	AddItem(const tstring& str);
		virtual ITreeViewItem*	InsertItem(const tstring& str, u32 index);
		virtual ITreeViewItem*	GetItem(u32 index);
		virtual ITreeViewItem*	GetItemAt(s32 x, s32 y);
		virtual ITreeViewItem*	GetSelected(void);
		virtual void			ExpandAll(void);
		virtual EventCtrl&		OnSelectedChange(void);
		virtual void			Clear(void);
	};
}

#endif _Tian_2014410234321_H_