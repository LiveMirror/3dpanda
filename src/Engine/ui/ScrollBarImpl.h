//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/3/3 15:10:34_
// 描述:  
//

#ifndef _SCROLLBARIMPL_201433151034_
#define _SCROLLBARIMPL_201433151034_

#include "ControlImpl.h"

namespace panda
{
	class ScrollBarImpl:public ControlImpl
	{
	public:
		ScrollBarImpl(void);
		virtual void		OnRender(IGraph2D* graph);
		virtual void		OnMouseEnter();
		virtual void		OnMouseLevae();
		virtual void		Update(s32 tick);
		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseUp(MouseEventArgs& e);
		virtual void		OnMouseMove(MouseEventArgs& e);
		virtual void		OnMouseWheel(MouseEventArgs& e);
		virtual void		SetSize(s32 width, s32 height);

		virtual void		SetMaximun(s32 v);
		virtual void		SetValue(s32 v);

		void			_UpdateBarHeight(void);
		void			_UpdateBarPos(void);
		void			_UpdateValue(void);
	public:
		bool		mMouseOn;
		bool		mMouseDown;
		s32			mMaximun;
		s32			mMinimun;
		s32			mValue;
		s32			mCurPosY;
		s32			mMaxPosY;
		f32			mAniAlpha;
		s32			mMouseDownY;

		s32			mWheelStep;
		s32			mBarHeight;

		EventHandle mOnValueChange;
	};
}

#endif // _SCROLLBARIMPL_201433151034_