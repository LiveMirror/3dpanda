////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-3-9 20:53:52
// ����:  
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