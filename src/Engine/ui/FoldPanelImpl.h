//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/22 14:42:05_
// 描述:  
//

#ifndef _FOLDPANELIMPL_2014522144205_
#define _FOLDPANELIMPL_2014522144205_

#include "PanelImpl.h"

namespace panda
{
	class IFoldPage;
	class FoldPanelImpl:public PanelImpl
	{
	public:
		FoldPanelImpl(void);
		virtual void		Draw(Rect& rect, IGraph2D* graph);
		virtual void		OnRender(IGraph2D* graph);

		virtual IControl*	HitTest(s32 x, s32 y, Vector2Dn& outPt);
		virtual void		OnMouseMove(MouseEventArgs& e);
		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseLevae(void);

		IFoldPage*			AddPage(const tstring& name);
		void				DrawTitle(IGraph2D* grahp);

	public:
		s32			mSelectIndex;
		s32			mMouseOnIndex;
		Vector2Dn	mPanelOffset;
		s32			mTitleHeight;
	};
}

#endif // _FOLDPANELIMPL_2014522144205_