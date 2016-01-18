////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-3 21:56:59
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201443215659_H_
#define	_Tian_201443215659_H_

#include "IControl.h"
#include "IPanel.h"

namespace panda
{
	class ToolBarItemImpl;
	class IToolBarItem:public IControl
	{
	public:
		enum Type
		{
			ImageButton,
			ToggleButton,
			Label,
			Separator
		};
	public:
		IToolBarItem(void);
		IToolBarItem(ToolBarItemImpl* impl);

		// for toggle button only
		
	};

	class IToolBarToggleButton:public IToolBarItem
	{
	public:
		IToolBarToggleButton(ToolBarItemImpl* impl);
		
		virtual bool	GetSelected(void);
		virtual void	SetSelected(bool select);

		virtual EventCtrl&	OnSelectChanged(void);
	};

	class ToolBarImpl;
	/*
	*
	*/
	class IToolBar:public IPanel
	{
	public:
		IToolBar(void);
		IToolBar(ToolBarImpl* impl);

		virtual IToolBarItem*	AddToolItem(const tstring& item, IToolBarItem::Type type = IToolBarItem::ImageButton);
		virtual u32				GetItemNum(void)const;
		virtual IToolBarItem*	GetItem(u32 index)const;
		virtual void			RemoveItem(u32 index);
		virtual void			RemoveItem(IToolBarItem* item);
	};
}

#endif _Tian_201443215659_H_