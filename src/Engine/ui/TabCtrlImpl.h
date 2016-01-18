////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-8 23:54:24
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201438235424_H_
#define	_Tian_201438235424_H_

#include "PanelImpl.h"

namespace panda
{
	class ITabPage;
	class TabCtrlImpl:public PanelImpl
	{
	public:
		TabCtrlImpl(void);
		virtual void		Draw(Rect& rect, IGraph2D* graph);
		virtual void		OnRender(IGraph2D* graph);
		virtual IControl*	HitTest(s32 x, s32 y, Vector2Dn& outPt);
		virtual void		OnMouseMove(MouseEventArgs& e);
		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseLevae(void);

		ITabPage*	GetPage(u32 index)const;
		ITabPage*	GetSelPage(void)const;
		void		DrawTitle(IGraph2D* graph);
		ITabPage*	AddPage(const tstring& name);

		virtual Vector2Dn	PointToScreen(s32 x, s32 y, IControl* pChild = NULL);

	public:
		s32			mMaxPageTitleWidth;
		f32			mPageTitleWidth;
		s32			mTitleHeight;
		s32			mSelectIndex;
		u32			mMouseOnIndex;
		EventCtrl	mOnSelPageChanged;
	};
}

#endif _Tian_201438235424_H_