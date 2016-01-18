//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/3/3 14:53:15_
// ����:  
//

#ifndef _ISCROLLBAR_201433145315_
#define _ISCROLLBAR_201433145315_

#include "IControl.h"

namespace panda
{
	class ScrollBarImpl;
	class ENGINE_API IScrollBar:public IControl
	{
	public:
		IScrollBar(void);
		IScrollBar(ScrollBarImpl* impl);

		virtual void	SetMaximun(s32 v);
		virtual s32		GetMaximun(void);
		virtual void	SetValue(s32 v);
		virtual s32		GetValue(void);

		virtual EventHandle&	OnValueChange(void);
	};
}

#endif // _ISCROLLBAR_201433145315_