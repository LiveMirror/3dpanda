//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 15:58:38_
// ����:  
//

#ifndef _IRENDERTARGET_201443155838_
#define _IRENDERTARGET_201443155838_

#include "Resources/ITexture.h"

namespace panda
{
	class RenderTargetImpl;
	class IRenderTarget:public ITexture
	{
	public:
		IRenderTarget(RenderTargetImpl* pImpl);
	};
}
#endif // _IRENDERTARGET_201443155838_