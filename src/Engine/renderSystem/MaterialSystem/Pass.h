//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 15:17:39_
// 描述:  
//

#ifndef _PASS_201443151739_
#define _PASS_201443151739_

#include "Base/Color.h"
#include "RenderSystem/IPass.h"
#include "Base/Matrix44.h"
#include <d3dx9.h>

namespace panda
{
	class RenderSystem;
	class TechniqueImpl;
	class Renderable;
	class CameraImpl;
	class MaterialImpl;
	class Pass:public IPass
	{
	public:
		Pass(IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr);
		~Pass();

		// interface
		virtual bool		LoadVertexShader(const tstring& file);
		virtual bool		LoadPixelShader(const tstring& file);

	public:
		//! 为pass设置相应参数
		//! call it when need to use it to render the object
		virtual void		SetParam(MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject);

	protected:
		//! 加载句柄
		virtual void		GetVsHandles(void);
		virtual void		GetPsHandles(void);
		virtual void		_GetPsHandles(void);		// use for Subclass to load handles
		virtual void		_GetVsHandles(void);		// use for Subclass to load handles
		//! use for subclass to bind their param
		virtual void		_SetParam(MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject);

		void				SetMatrixArr(IDirect3DDevice9*	d3dDevice, Matrix44f* pMatrix, u32 count);
		void				SetVsTex(D3DXHANDLE handle, IDirect3DTexture9* tex);
		void				SetPsTex(D3DXHANDLE handle, IDirect3DTexture9* tex);

		virtual	void		DrawRenderObject(Renderable* pObject, CameraImpl* pCamera);

	public:
		IDirect3DDevice9*	mD3dDevice;
		RenderSystem*		mRenderMgr;
		TechniqueImpl*		mParent;

		IDirect3DVertexShader9*		mVertexShader;
		IDirect3DPixelShader9*		mPixelShader;
		ID3DXConstantTable*			mVConstTable;
		ID3DXConstantTable*			mPConstTable;

		D3DXHANDLE			mHandleEnvColor;		// 环境光颜色
		D3DXHANDLE			mHandleDirLightColor;	// 方向光颜色
		D3DXHANDLE			mHandleLightDir;		// 光方向
		D3DXHANDLE			mHandleEyePos;			// 摄像机的位置
		D3DXHANDLE			mHandleMatrl;
		D3DXHANDLE			mHandleDiffuseTex;
		D3DXHANDLE			mHandleNormalTex;
		D3DXHANDLE			mHandleViewProj;
		D3DXHANDLE			mHandleWorldMatrix;
	};
}

#endif // _PASS_201443151739_