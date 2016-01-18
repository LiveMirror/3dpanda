////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-25 23:34:26
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014225233426_H_
#define	_Tian_2014225233426_H_

#include "../TypeDef.h"
#include "ControlImpl.h"

namespace panda
{
	class RadioButtonImpl;
	class IScrollBar;
	class PanelImpl:public ControlImpl
	{
	public:
		PanelImpl(void);
		virtual void		AddChild(IControl* ctrl);
		virtual IControl*	HitTest(s32 x, s32 y, Vector2Dn& outPt);
		virtual void		Draw(Rect& rect, IGraph2D* graph);
		virtual void		OnRender(IGraph2D* graph);
		virtual void		SetSize(s32 width, s32 height);
		
		virtual void		Update(s32 tick);
		virtual void		UpdateScrollValue(void);
		virtual void		UpdateScrollValue(s32 oldY, s32 curY);
		virtual bool		OnScrollChange(IControl* pCtrl, s32 x, s32 y);
		virtual void		OnMouseWheel(MouseEventArgs& e);

		virtual Vector2Dn	PointToScreen(s32 x, s32 y, IControl* pChild = NULL);

		void				CreateScrollBar(void);

		void				BringToFront(IControl* pCtrl);
		void				SendToBack(IControl* pCtrl);

		bool				HasChild(IControl* ctrl);
		void				RemoveChild(IControl* ctrl);
	public:
		CtrlList			mChilds;
		RadioButtonImpl*	mRadioButton;
		bool				mScrollable;		// 标记是否自动更新滚动条
		IScrollBar*			mScrollBar;
		s32					mMaxHeight;
		s32					mCurY;
	};
}

#endif _Tian_2014225233426_H_