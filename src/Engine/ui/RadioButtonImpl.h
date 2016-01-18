//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/3/10 10:15:31_
// 描述:  
//

#ifndef _RADIOBUTTONIMPL_2014310101531_
#define _RADIOBUTTONIMPL_2014310101531_

#include "ControlImpl.h"

namespace panda
{
	class RadioButtonImpl:public ControlImpl
	{
	public:
		RadioButtonImpl(void);
		virtual void		SetText(const tstring& text);
		virtual void		OnRender(IGraph2D* graph);
		virtual void		OnMouseClick(void);

		void	_SetCheck(bool check);
	public:
		bool			mChecked;
		EventHandle		mOnCheckedChange;
	};
}

#endif // _RADIOBUTTONIMPL_2014310101531_