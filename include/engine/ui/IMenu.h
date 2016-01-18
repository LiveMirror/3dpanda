////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-28 21:54:03
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014228215403_H_
#define	_Tian_2014228215403_H_

#include "IPanel.h"

namespace panda
{
	class MenuItemImpl;
	class ENGINE_API IMenuItem:public IPanel
	{
	public:
		IMenuItem(MenuItemImpl* impl);

		virtual IMenuItem*	AddItem(const tstring& text);
	};

	class MenuImpl;
	class IUiManager;
	class ENGINE_API IMenu:public IMenuItem
	{
	public:
		IMenu(IUiManager* manager, MenuImpl* impl);
		virtual void		ShowMenu(s32 x, s32 y);
	};
}

#endif _Tian_2014228215403_H_