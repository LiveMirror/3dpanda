////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-8 23:16:58
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201438231658_H_
#define	_Tian_201438231658_H_

#include "IPanel.h"
#include "resources/ResRefDefine.h"

namespace panda
{
	class ListBoxItemImpl;
	class IListBoxItem
	{
	public:
		IListBoxItem(void);
		IListBoxItem(ListBoxItemImpl* impl);

		virtual void				SetText(const tstring& text);
		virtual const tstring&		GetText(void)const;
		virtual	IListBoxItem*		AddItem(const tstring& text);
		virtual u32					GetItemNum(void)const;
		virtual IListBoxItem*		GetItem(u32 index)const;

		virtual void				SetImage(ResTexture img);
		virtual ResTexture			GetImage(void)const;

		virtual bool				GetVisible(void)const;
		virtual void				SetVisible(bool visible);

		virtual void				SetUserData(s32 data);
		virtual s32					GetUserData(void)const;

	public:
		ListBoxItemImpl*	mImpl;
	};

	class ListBoxImpl;
	class IListBox:public IPanel
	{
	public:
		IListBox(void);
		IListBox(ListBoxImpl* impl);

		virtual	IListBoxItem*		AddItem(const tstring& text);
		virtual IListBoxItem*		InsertItem(const tstring& text, u32 index);
		virtual u32					GetItemNum(void)const;
		virtual IListBoxItem*		GetItem(u32 index)const;
		virtual s32					GetSelItemIndex(void)const;
		virtual void				SetSelItemIndex(s32 index);
		virtual IListBoxItem*		GetSelItem(void)const;
		virtual EventCtrl&			OnSelectedChange(void);
		virtual void				RemoveItem(u32 index);
		virtual void				Clear(void);
	};
}

#endif _Tian_201438231658_H_