////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-24 22:14:08
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014224221408_H_
#define	_Tian_2014224221408_H_

#include "base/Config.h"
#include "IControl.h"

namespace panda
{
	class ButtonImpl;
	/*
	*
	*/
	class ENGINE_API IButton:public IControl
	{
	public:
		IButton(void);
		IButton(ButtonImpl* impl);
	};
}

#endif _Tian_2014224221408_H_