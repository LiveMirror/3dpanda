////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-9 20:53:52
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201439205352_H_
#define	_Tian_201439205352_H_

#include "PanelImpl.h"

namespace panda
{
	/*
	*
	*/
	class TabPageImpl:public PanelImpl
	{
	public:
		TabPageImpl(void);

		virtual void		OnRender(IGraph2D* graph);

		virtual void		SetToolTip(const tstring& str);
		virtual const tstring&	GetToolTip(void)const;

	public:
		tstring		mToolTipStr;
	};
}

#endif _Tian_201439205352_H_