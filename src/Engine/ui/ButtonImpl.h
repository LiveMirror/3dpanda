//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/2/26 11:03:26_
// ����:  
//

#ifndef _BUTTONIMPL_2014226110326_
#define _BUTTONIMPL_2014226110326_

#include "ControlImpl.h"

namespace panda
{
	class ButtonImpl:public ControlImpl
	{
	public:
		ButtonImpl();

		virtual void		OnRender(IGraph2D* graph);

		virtual void		OnMouseEnter(void);
		virtual void		OnMouseLevae(void);
		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseUp(MouseEventArgs& e);
		virtual void		Update(s32 tick);
	public:
		bool		mMouseDown;
		f32			mAniAlpha;
	};
}

#endif // _BUTTONIMPL_2014226110326_