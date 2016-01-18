//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/6/3 14:58:25_
// 描述:  
//

#ifndef _BILLBORADPASS_201463145825_
#define _BILLBORADPASS_201463145825_

#include "Pass.h"

namespace panda
{
	class EffectSetPass:public Pass
	{
	public:
		EffectSetPass(IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr);

		void				SetWorldTransform(const Matrix44f& mat);
		void				SetColor(const Colorf& color);
		virtual void		_GetPsHandles(void);		// use for Subclass to load handles
		//virtual void		_SetParam(MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject);
	public:
		D3DXHANDLE			mHandleColor;
		Colorf				mColor;
	};
}

#endif // _BILLBORADPASS_201463145825_