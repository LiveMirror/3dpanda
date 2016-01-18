////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-3-4 23:51:07
// ����:  
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