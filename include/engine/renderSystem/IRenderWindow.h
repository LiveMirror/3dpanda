////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-22 11:16:04
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014222111604_H_
#define	_Tian_2014222111604_H_

#include "base/Config.h"
#include "base/color.h"

namespace panda
{
	class IRenderTarget;
	class ICamera;
	class IUiManager;
	/*
	*
	*/
	class IRenderWindow
	{
	public:
		//-----------------------------------------
		//! 更新渲染窗口
		virtual void				Update(void) = 0;

		//-----------------------------------------
		//! 是否自动更新
		virtual bool				IsAutoUpdate(void)const = 0;
		virtual void				SetAutoUpdate(bool bAuto) = 0;

		virtual void				SetBackColor(const Color& color) = 0;
		virtual const Color&		GetBackColor(void)const = 0;

		//! 设置渲染目标
		//! 如果pTarget为NULL,则渲染到默认渲染目标上
		virtual void				SetRenderTarget(IRenderTarget* pTarget, s32 index = 0) = 0;
		virtual IRenderTarget*		GetRenderTarget(s32 index) = 0;

		virtual void				SetCamera(ICamera* pCam) = 0;
		virtual ICamera*			GetCamera(void) = 0;

		virtual IUiManager*			GetUiManager(void) = 0;

		virtual	s32					GetWidth(void)const = 0;
		virtual s32					GetHeight(void)const = 0;

		virtual void				Resize(s32 width, s32 height) = 0;

		virtual void				Release(void) = 0;
	};
}

#endif _Tian_2014222111604_H_