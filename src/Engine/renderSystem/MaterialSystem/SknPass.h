//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/9 15:39:29_
// ����:  
//

#ifndef _SKNPASS_201459153929_
#define _SKNPASS_201459153929_

#include "Pass.h"

namespace panda
{
	class SknPass:public Pass
	{
	public:
		SknPass(IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr);

		virtual void		_GetVsHandles(void);
		virtual void		_SetParam(MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject);

	public:
		D3DXHANDLE			mHandleMatrixArray;
	};
}

#endif // _SKNPASS_201459153929_