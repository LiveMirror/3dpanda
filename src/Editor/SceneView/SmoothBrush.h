////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-16 23:33:36
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014516233336_H_
#define	_Tian_2014516233336_H_

#include "IBrush.h"

namespace editor
{
	/*
	*
	*/
	class SmoothBrush:public IBrush
	{
	public:
		SmoothBrush(void);

		virtual	void		OnPaint(f32 x, f32 y);

		virtual void		SetInsideRadius(s32 radius);
		virtual void		SetValue(f32 v);
	};
}

#endif _Tian_2014516233336_H_