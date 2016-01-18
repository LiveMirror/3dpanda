////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-16 20:48:34
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014516204834_H_
#define	_Tian_2014516204834_H_

#include "Pass.h"

namespace panda
{
	class LinePass:public Pass
	{
	public:
		LinePass(IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr);

		//! 为pass设置相应参数
		//! call it when need to use it to render the object
		virtual void		SetParam(MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject);
		virtual void		GetPsHandles(void);
	};
}

#endif _Tian_2014516204834_H_