////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-29 21:39:16
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014429213916_H_
#define	_Tian_2014429213916_H_

#include "Pass.h"
#include "base/Vector2D.h"

namespace panda
{
	class Effect;
	class PostProcessPass:public Pass
	{
	public:
		PostProcessPass(IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr);
		virtual ~PostProcessPass();
		virtual void		SetParam(MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject);
		void				PPSetParam(Effect* effect);
		virtual void		GetPsHandles(void);
		virtual void		GetVsHandles(void);

		void				Resize(s32 width, s32 height);
		void				SetKernel(u32 count, Vector2Df* vArr);

		void				SetScale(f32 scale);
		void				SetUVScale(f32 scale);
	public:
		f32					mScale;
		f32					mUvScale;
		D3DXHANDLE			mHandleScale;
		D3DXHANDLE			mHandleUvScale;
		D3DXHANDLE			mHandleNormalTex;
		D3DXHANDLE			mHandleColorTex;
		D3DXHANDLE			mHandlePixeKernel;

		u32					mKernel;
		Vector2Df*			mvKernel;
		D3DXVECTOR4*		mVectorArr;
	};
}

#endif _Tian_2014429213916_H_