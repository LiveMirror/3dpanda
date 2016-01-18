//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/3/11 9:54:53_
// 描述:  
//

#ifndef _TOOLTIP_201431195453_
#define _TOOLTIP_201431195453_

#include "ControlImpl.h"

namespace panda
{
	class ToolTipImpl:public ControlImpl
	{
	public:
		ToolTipImpl(void);
		virtual void		SetText(const tstring& text);
		virtual void		OnRender(IGraph2D* graph);
		void	ShowTip(s32 x, s32 y);
	};
}

#endif // _TOOLTIP_201431195453_