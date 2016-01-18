////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-5 22:46:44
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201435224644_H_
#define	_Tian_201435224644_H_

#include "IControl.h"

namespace panda
{
	class ProgressBarImpl;
	class IProgressBar:public IControl
	{
	public:
		IProgressBar(void);
		IProgressBar(ProgressBarImpl* impl);

		// 0-1
		virtual void	SetValue(f32 v);
		virtual f32		GetValue(void);
	};
}

#endif _Tian_201435224644_H_