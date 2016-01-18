////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-24 22:19:26
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014224221926_H_
#define	_Tian_2014224221926_H_

#include "base/Rect.h"
#include "ui/CtrlDef.h"
#include "base/Color.h"
#include "resources/ResrefDefine.h"

namespace panda
{
	class IControl;
	class IGraph2D;
	class IFont;
	class IPanel;
	class uiManager;
	/*
	*
	*/
	class ControlImpl
	{
	public:
		ControlImpl(void);
		virtual ~ControlImpl(void);

		virtual void		OnBindThis(IControl* pThis);
		virtual void		OnBindUiMgr(uiManager* uiMgr);
		virtual void		Draw(Rect& rect, IGraph2D* graph);
		virtual void		OnRender(IGraph2D* graph);

		virtual void		SetSize(s32 width, s32 height);
		virtual void		SetPos(s32 x, s32 y);
		virtual void		SetText(const tstring& text);
		virtual IControl*	HitTest(s32 x, s32 y, Vector2Dn& outPt);

		virtual void		SetVisible(bool visible);

		virtual void		SetFocus(void);
		virtual void		OnGotFocus(void);
		virtual void		OnLostFocus(void);

		virtual void		SetToolTip(const tstring& str);
		virtual const tstring&	GetToolTip(void)const;

		virtual void		Update(s32 tick);
		virtual void		OnMouseMove(MouseEventArgs& e);
		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseDClick(MouseEventArgs& e);
		virtual void		OnMouseUp(MouseEventArgs& e);
		virtual void		OnMouseClick(MouseEventArgs& e);
		virtual void		OnMouseWheel(MouseEventArgs& e);
		virtual void		OnMouseEnter(void);
		virtual void		OnMouseLevae(void);
		virtual void		OnMouseHover(MouseEventArgs& e);
		virtual void		OnKeyDown(KeyEventArgs& e);
		virtual void		OnChar(s32 key);

		// 
		virtual Vector2Dn	PointToScreen(s32 x, s32 y, IControl* pChild = NULL);
		bool				IsAncestor(IControl* pCtrl);
		void				BringToFront(void);
		void				SendToBack(void);

	public:
		uiManager*		mUiMgr;
		IControl*		mThis;
		s32				mAniState;
		bool			mIsVisible;
		Rect			mRect;
		Color			mBackColor;
		Color			mBackColor2;
		bool			mDrawBorder;
		bool			mIsFocus;
		bool			mEnable;
		Color			mBorderColor;
		Color			mTextColor;
		f32				mBorderSize;
		tstring			mText;
		tstring			mTipText;
		IFont*			mFont;
		ResTexture		mBackImage;
		bool			mMouseOn;
		IPanel*			mParent;
		s32				mUserData;

		// 事件
		EventHandle		mOnSizeChange;
		EventHandle		mOnPosChange;
		EventMouse		mOnMouseMove;
		EventMouse		mOnMouseDown;
		EventMouse		mOnMouseUp;
		EventMouse		mOnMouseClick;
		EventMouse		mOnMouseDClick;
		EventMouse		mOnMouseHover;
		EventMouse		mOnMouseWheel;
		EventKey		mOnKeyDown;
		EventCtrl		mOnClick;
		EventCtrl		mOnMouseEnter;
		EventCtrl		mOnMouseLeave;
		EventCtrl		mOnLostFocus;
		EventCtrl		mOnGetFocus;
	};
}

#endif _Tian_2014224221926_H_