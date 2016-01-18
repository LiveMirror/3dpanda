////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-4 23:51:07
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201434235107_H_
#define	_Tian_201434235107_H_

#include "ControlImpl.h"

namespace panda
{
	/*
	*
	*/
	class CheckBoxImpl:public ControlImpl
	{
	public:
		CheckBoxImpl(void);

		virtual void		SetText(const tstring& text);
		virtual void		OnRender(IGraph2D* graph);
		virtual void		OnMouseClick(MouseEventArgs& e);
	public:
		bool			mChecked;
		EventHandle		mOnCheckedChange;
	};
}

#endif _Tian_201434235107_H_