////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-22 11:57:09
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014222115709_H_
#define	_Tian_2014222115709_H_

#include "renderSystem/IRenderWindow.h"
#include <d3dx9.h>
#include "../io/Timer.h"

namespace panda
{
	class RenderSystem;
	class uiManager;
	class IUiManager;
	class RenderQueue;
	class IRenderTarget;
	class ICamera;
	class Effect;
	class IResMgr;
	/*
	*
	*/
	class RenderWindow:public IRenderWindow
	{
	public:
		RenderWindow(RenderSystem* renderSys);

		//-----------------------------------------
		//! 更新渲染窗口
		virtual void				Update(void);

		//-----------------------------------------
		//! 是否自动更新
		virtual bool				IsAutoUpdate(void)const;
		virtual void				SetAutoUpdate(bool bAuto);

		virtual void				SetBackColor(const Color& color);
		virtual const Color&		GetBackColor(void)const;

		//! 设置渲染目标
		//! 如果pTarget为NULL,则渲染到默认渲染目标上
		virtual void				SetRenderTarget(IRenderTarget* pTarget, s32 index = 0);
		virtual IRenderTarget*		GetRenderTarget(s32 index);

		virtual void				SetCamera(ICamera* pCam);
		virtual ICamera*			GetCamera(void);

		virtual	s32					GetWidth(void)const;
		virtual s32					GetHeight(void)const;

		virtual void				Resize(s32 width, s32 height);

		virtual IUiManager*			GetUiManager(void);

		virtual void				Release(void);

		//! 供内部特效使用的临时切换渲染目标
		//! SetRenderTarget方法将影响一帧渲染
		//! 此方法可控制单个或多个pass的渲染目标
		void						_SetRenderTarget(IDirect3DSurface9* pSurface, s32 index);
		void						_SetRenderTarget(IRenderTarget* pTarget, s32 index);
		IDirect3DSurface9*			_GetRenderTarget(s32 index);

	public:
		// 初始化窗口参数
		void						Init(s32 width, s32 height, IResMgr* pResMgr);
		void						DeviceLost(void);
		void						ResetDevice(void);

		void						_RenderQueue(void);
	public:
		s32							mWidth;
		s32							mHeight;
		RenderSystem*				mRenderSys;		// 渲染器
		bool						mAutoUpdate;
		IDirect3DDevice9*			mDevicePtr;		// 设备指针
		IDirect3DSwapChain9*		mSwapChainPtr;	// 交换链
		IDirect3DSurface9*			mDefaultRt;		// 默认渲染目标
		Effect*						mEffect;		// 后期特效
		typedef std::list<IRenderTarget*>	RenderTargetList;
		RenderTargetList			mRenderTargets;	// 渲染目标
		ICamera*					mCamera;
		HWND						mhWnd;			// 窗口句柄
		Color						mBackColor;
		uiManager*					mUiManager;
		CTimer						mTimer;

		RenderQueue*				mRenderQueue;
	};
}

#endif _Tian_2014222115709_H_