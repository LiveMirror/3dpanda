//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/23 15:33:36_
// 描述:  
//

#ifndef _IBILLBOARDRENDER_2014523153336_
#define _IBILLBOARDRENDER_2014523153336_

#include "IParticleRender.h"

namespace panda
{
	class BillboardRenderImpl;
	class IBillboardRender:public IParticleRender
	{
	public:
		IBillboardRender(BillboardRenderImpl* impl);
	};
}

#endif // _IBILLBOARDRENDER_2014523153336_