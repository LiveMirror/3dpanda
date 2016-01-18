////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-8 23:52:38
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201438235238_H_
#define	_Tian_201438235238_H_

#include "IPanel.h"

namespace panda
{
	class TabPageImpl;
	class ITabPage:public IPanel
	{
	public:
		ITabPage(void);
		ITabPage(TabPageImpl* impl);
	};

	class TabCtrlImpl;
	class ITabCtrl:public IPanel
	{
	public:
		ITabCtrl(void);
		ITabCtrl(TabCtrlImpl* impl);

		virtual ITabPage*	AddPage(const tstring& name);

		virtual u32			GetPageNum(void)const;
		virtual ITabPage*	GetPage(u32 index)const;

		virtual void		SetSelPage(u32 index);
		virtual s32			GetSelIndex(void)const;
		virtual ITabPage*	GetSelPage(void)const;

		virtual EventCtrl&	OnSelPageChanged(void);
	};
}

#endif _Tian_201438235238_H_