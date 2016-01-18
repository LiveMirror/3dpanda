//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/26 11:28:57_
// 描述:  
//

#ifndef _PARTICLERENDERIMPL_2014526112857_
#define _PARTICLERENDERIMPL_2014526112857_

#include "base/Struct.h"
#include "config.h"
#include "resources/ResRefDefine.h"

namespace panda
{
	class Graph3D;
	class Particle;
	class ParticleRenderImpl
	{
	public:
		ParticleRenderImpl(void);

		//! 渲染粒子
		virtual	void				RenderParticle(Particle* p, Graph3D* graph3D);
	public:
		tstring						mName;
		ParticleRenderType::eValue	mType;
		ResTexture					mImage;
	};
}

#endif // _PARTICLERENDERIMPL_2014526112857_