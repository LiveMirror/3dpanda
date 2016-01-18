////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-2-22 11:57:09
// ����:  
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
		//! ������Ⱦ����
		virtual void				Update(void);

		//-----------------------------------------
		//! �Ƿ��Զ�����
		virtual bool				IsAutoUpdate(void)const;
		virtual void				SetAutoUpdate(bool bAuto);

		virtual void				SetBackColor(const Color& color);
		virtual const Color&		GetBackColor(void)const;

		//! ������ȾĿ��
		//! ���pTargetΪNULL,����Ⱦ��Ĭ����ȾĿ����
		virtual void				SetRenderTarget(IRenderTarget* pTarget, s32 index = 0);
		virtual IRenderTarget*		GetRenderTarget(s32 index);

		virtual void				SetCamera(ICamera* pCam);
		virtual ICamera*			GetCamera(void);

		virtual	s32					GetWidth(void)const;
		virtual s32					GetHeight(void)const;

		virtual void				Resize(s32 width, s32 height);

		virtual IUiManager*			GetUiManager(void);

		virtual void				Release(void);

		//! ���ڲ���Чʹ�õ���ʱ�л���ȾĿ��
		//! SetRenderTarget������Ӱ��һ֡��Ⱦ
		//! �˷����ɿ��Ƶ�������pass����ȾĿ��
		void						_SetRenderTarget(IDirect3DSurface9* pSurface, s32 index);
		void						_SetRenderTarget(IRenderTarget* pTarget, s32 index);
		IDirect3DSurface9*			_GetRenderTarget(s32 index);

	public:
		// ��ʼ�����ڲ���
		void						Init(s32 width, s32 height, IResMgr* pResMgr);
		void						DeviceLost(void);
		void						ResetDevice(void);

		void						_RenderQueue(void);
	public:
		s32							mWidth;
		s32							mHeight;
		RenderSystem*				mRenderSys;		// ��Ⱦ��
		bool						mAutoUpdate;
		IDirect3DDevice9*			mDevicePtr;		// �豸ָ��
		IDirect3DSwapChain9*		mSwapChainPtr;	// ������
		IDirect3DSurface9*			mDefaultRt;		// Ĭ����ȾĿ��
		Effect*						mEffect;		// ������Ч
		typedef std::list<IRenderTarget*>	RenderTargetList;
		RenderTargetList			mRenderTargets;	// ��ȾĿ��
		ICamera*					mCamera;
		HWND						mhWnd;			// ���ھ��
		Color						mBackColor;
		uiManager*					mUiManager;
		CTimer						mTimer;

		RenderQueue*				mRenderQueue;
	};
}

#endif _Tian_2014222115709_H_