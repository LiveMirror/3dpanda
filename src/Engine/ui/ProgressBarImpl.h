////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-3-5 22:59:37
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201435225937_H_
#define	_Tian_201435225937_H_

#include "ControlImpl.h"

namespace panda
{
	/*
	*
	*/
	class ProgressBarImpl:public ControlImpl
	{
	public:
		ProgressBarImpl(void);

		virtual void		OnRender(IGraph2D* graph);

	public:
		f32		mValue;
	};
}

#endif _Tian_201435225937_H_