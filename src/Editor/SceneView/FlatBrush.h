//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/20 16:16:26_
// 描述:  
//

#ifndef _FLATBRUSH_2014520161626_
#define _FLATBRUSH_2014520161626_

#include "IBrush.h"

namespace editor
{
	class FlatBrush:public IBrush
	{
	public:
		FlatBrush(void);
		virtual	void		OnPaint(f32 x, f32 y);
	};
}

#endif // _FLATBRUSH_2014520161626_