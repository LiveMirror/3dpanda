////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-8 23:34:04
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201438233404_H_
#define	_Tian_201438233404_H_

#include "ControlImpl.h"
#include <vector>

namespace panda
{
	class ISliderBarTag;
	class SliderBarTag;
	class SliderBarImpl:public ControlImpl
	{
	public:
		SliderBarImpl(void);

		virtual void		OnRender(IGraph2D* graph);

		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseUp(MouseEventArgs& e);
		virtual void		OnMouseMove(MouseEventArgs& e);

		void				SetMaximun(s32 v);
		void				SetValue(s32 v);

		ISliderBarTag*		AddTag(s32 v, s32 userData);
		void				ClearTags(void);

		void	_DrawTags(IGraph2D* graph);

		void	_updateInfo(void);

	public:
		typedef	std::vector<SliderBarTag*>	TagList;
		TagList		mTags;

		s32			mMaximun;
		s32			mValue;
		f32			mPerWidth;

		s32			mBarWidth;
		s32			mMouseDownX;
		bool		mDropValue;

		EventCtrl	mOnValueChange;
	};
}

#endif _Tian_201438233404_H_