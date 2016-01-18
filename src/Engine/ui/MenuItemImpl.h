////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-28 23:29:27
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014228232927_H_
#define	_Tian_2014228232927_H_

#include "PanelImpl.h"

namespace panda
{
	class IMenuItem;
	class uiManager;
	/*
	*
	*/
	class MenuItemImpl:public PanelImpl
	{
	public:
		MenuItemImpl(void);
		virtual IMenuItem*	AddItem(const tstring& text);
		virtual void		Draw(Rect& rect, IGraph2D* graph);
		virtual void		OnRender(IGraph2D* graph);
		virtual void		DrawChilds(s32 x, s32 y, IGraph2D* graph);
		virtual IControl*	HitTest(s32 x, s32 y, Vector2Dn& outPt);

		virtual void		OnMouseClick(MouseEventArgs& e);
		virtual void		OnMouseEnter();
		virtual void		OnMouseLevae();

		void		ClearDrawChild(void);
	public:
		bool		mDrawChild;
		bool		mMouseOn;
		s32			mChildHeight;
		s32			mItemHeight;
		bool		mIsDelimiter;	// 分隔
		s32			mShowX;
		s32			mShowY;
		MenuItemImpl*	mMouseOnChild;
	};
}

#endif _Tian_2014228232927_H_