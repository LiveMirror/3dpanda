////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-3-1 11:03:24
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201431110324_H_
#define	_Tian_201431110324_H_

#include "MenuItemImpl.h"

namespace panda
{
	class uiManager;
	class MenuImpl:public MenuItemImpl
	{
	public:
		MenuImpl(void);
		virtual void		Draw(Rect& rect, IGraph2D* graph);
		virtual void		ShowMenu(s32 x, s32 y);

	public:
		
	};
}

#endif _Tian_201431110324_H_