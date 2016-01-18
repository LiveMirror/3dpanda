////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-24 22:12:00
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014224221200_H_
#define	_Tian_2014224221200_H_

#include "base/Config.h"
#include "base/Size.h"
#include "base/Vector2D.h"
#include "base/Color.h"
#include "resources/resrefdefine.h"
#include "CtrlDef.h"

namespace panda
{
	class ControlImpl;
	class IGraph2D;
	class IPanel;
	class IUiManager;
	/*
	*
	*/
	class ENGINE_API IControl
	{
	public:
		IControl(void);
		IControl(ControlImpl* impl);
		virtual ~IControl(void);

		virtual void		OnRender(IGraph2D* grahp);

		virtual void		SetText(const tstring& str);
		virtual const tstring&	GetText(void);

		virtual void		SetSize(const Size& size);
		virtual void		SetSize(s32 width, s32 height);
		virtual const Size&			GetSize(void)const;

		virtual void		SetPos(const Vector2Dn& pos);
		virtual void		SetPos(s32 x, s32 y);
		virtual const Vector2Dn&	GetPos(void)const;

		virtual void		SetEnable(bool enable);
		virtual bool		GetEnable(void)const;

		virtual void		SetBackColor(Color c);
		virtual void		SetBorderColor(Color c);
		virtual void		SetBorderSize(f32 width);

		virtual void		SetToolTip(const tstring& str);
		virtual const tstring&	GetToolTip(void)const;

		virtual void		Update(s32 tick);

		virtual void		SetVisible(bool visible);
		virtual bool		GetVisible(void)const;

		virtual void		SetDrawBorder(bool draw);
		virtual bool		GetDrawBorder(void)const;

		virtual void		SetBackImage(ResTexture image);
		virtual ResTexture	GetBackImage(void)const;

		virtual IPanel*		GetParent(void);
		virtual void		SetFocus(void);
		
		virtual Vector2Dn	PointToClient(s32 x, s32 y);
		virtual Vector2Dn	PointToScreen(s32 x, s32 y);

		virtual void		BringToFront(void);
		virtual void		SendToBack(void);

		virtual void		SetUserData(s32 data);
		virtual s32			GetUserData(void)const;

		virtual IUiManager*	GetUiMgr(void);

		virtual void		RealeseCapture(void);

		virtual EventMouse&	OnMouseUp(void);
		virtual EventMouse&	OnMouseDown(void);
		virtual EventMouse&	OnMouseClick(void);
		virtual EventMouse&	OnMouseMove(void);
		virtual EventMouse&	OnMouseWheel(void);
		virtual EventKey&	OnKeyDown(void);
		virtual EventCtrl&	OnClick(void);
		virtual EventCtrl&	OnLostFocus(void);
	public:
		ControlImpl*	mImpl;
	};
}

#endif _Tian_2014224221200_H_