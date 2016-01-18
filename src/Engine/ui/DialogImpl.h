////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-5 23:29:26
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201435232926_H_
#define	_Tian_201435232926_H_

#include "PanelImpl.h"

namespace panda
{
	/*
	*
	*/
	class DialogImpl:public PanelImpl
	{
	public:
		DialogImpl(void);
		virtual void		Draw(Rect& rect, IGraph2D* graph);
		virtual void		OnRenderTitle(IGraph2D* graph);
		virtual void		OnRender(IGraph2D* graph);
		virtual IControl*	HitTest(s32 x, s32 y, Vector2Dn& outPt);
		virtual void		UpdateScrollValue(void);

		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseUp(MouseEventArgs& e);
		virtual void		OnMouseMove(MouseEventArgs& e);

		virtual Vector2Dn	PointToScreen(s32 x, s32 y, IControl* pChild = NULL);

		void				CloseDlg(void);
		void				DoMode(void);
	public:
		bool		mEnableMove;
		s32			mTitleHeight;
		bool		mMouseDown;
		bool		mMoveDialog;
		s32			mOldX;
		s32			mOldY;
		bool		mMode;
		bool		mColseBtnDown;
		bool		mMouseOnCloseBtn;
		bool		mMouseOnMinBtn;
	};
}

#endif _Tian_201435232926_H_