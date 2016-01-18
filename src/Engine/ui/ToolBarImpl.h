////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-3 22:11:33
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201443221133_H_
#define	_Tian_201443221133_H_

#include "PanelImpl.h"
#include "ui/IToolBar.h"

namespace panda
{
	/*
	*
	*/
	class ToolBarImpl:public PanelImpl
	{
	public:
		ToolBarImpl(void);
		IToolBarItem*	AddToolItem(const tstring& item, IToolBarItem::Type type = IToolBarItem::ImageButton);
		IToolBarItem*	GetItem(u32 index)const;

		void			RemoveItem(u32 index);
		void			RemoveItem(IToolBarItem* item);

	protected:
		s32				mCurWidth;
	};
}

#endif _Tian_201443221133_H_