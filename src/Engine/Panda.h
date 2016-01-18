////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-22 10:12:13
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014222101213_H_
#define	_Tian_2014222101213_H_

#include "IPanda.h"

namespace panda
{
	class RenderSystem;
	class ResourceMgr;
	/*
	*
	*/
	class Panda:public IPanda
	{
	public:
		Panda(void);

		//-----------------------------------------
		//! 初始化渲染设备
		//! param device:IDirect3DDevice9
		virtual IRenderWindow*	InitDevice(RenderWindowParam* info = NULL, void* device = NULL);

		virtual IRenderSystem*	GetRenderSystem(void);
		virtual IResMgr*		GetResMgr(void);

		//-----------------------------------------
		//! 创建一个场景管理器
		//! 你需要手动调用ISceneMgr的Release方法是否它
		virtual ISceneMgr*		CreateSceneMgr(void) const;

		//-----------------------------------------
		//! 进入消息循环
		virtual void			Run(void);

		//! 释放
		virtual void			Release(void);

	protected:
		void					_update(void);

	public:
		RenderSystem*			mRenderSystem;
		ResourceMgr*			mResMgr;
	};
}

#endif _Tian_2014222101213_H_