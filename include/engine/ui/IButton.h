////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-2-24 22:14:08
// ����:  
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