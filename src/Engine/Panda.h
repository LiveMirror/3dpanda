////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-2-22 10:12:13
// ����:  
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
		//! ��ʼ����Ⱦ�豸
		//! param device:IDirect3DDevice9
		virtual IRenderWindow*	InitDevice(RenderWindowParam* info = NULL, void* device = NULL);

		virtual IRenderSystem*	GetRenderSystem(void);
		virtual IResMgr*		GetResMgr(void);

		//-----------------------------------------
		//! ����һ������������
		//! ����Ҫ�ֶ�����ISceneMgr��Release�����Ƿ���
		virtual ISceneMgr*		CreateSceneMgr(void) const;

		//-----------------------------------------
		//! ������Ϣѭ��
		virtual void			Run(void);

		//! �ͷ�
		virtual void			Release(void);

	protected:
		void					_update(void);

	public:
		RenderSystem*			mRenderSystem;
		ResourceMgr*			mResMgr;
	};
}

#endif _Tian_2014222101213_H_