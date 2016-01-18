////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-16 23:54:31
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014516235431_H_
#define	_Tian_2014516235431_H_

#include "Pass.h"

namespace panda
{
	/*
	*
	*/
	class TerPass:public Pass
	{
	public:
		TerPass(IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr);

	protected:
		virtual void		_GetPsHandles(void);
		virtual void		_GetVsHandles(void);
		virtual void		_SetParam(MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject);

	public:
		D3DXHANDLE			mHandleDetailTex;
		D3DXHANDLE			mHandleLightDir;
		D3DXHANDLE			mHandleTextureNum;
		D3DXHANDLE			mHandleTex1;
		D3DXHANDLE			mHandleTex2;
		D3DXHANDLE			mHandleTex3;
		D3DXHANDLE			mHandleTex4;
		D3DXHANDLE			mHandleScale1;
		D3DXHANDLE			mHandleScale2;
		D3DXHANDLE			mHandleScale3;
		D3DXHANDLE			mHandleScale4;
		D3DXHANDLE			mHandlDifScale;
	};
}

#endif _Tian_2014516235431_H_