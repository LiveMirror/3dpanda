//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/23 10:40:29_
// ����:  
//

#ifndef _IPARTICLERENDER_2014523104029_
#define _IPARTICLERENDER_2014523104029_

#include "base/Struct.h"
#include "config.h"
#include "resources/ResRefDefine.h"

namespace panda
{
	class ParticleRenderImpl;
	class IParticleRender
	{
	public:
		IParticleRender(ParticleRenderImpl* impl);

		virtual void				SetName(const tstring& name);
		virtual const tstring&		GetName(void)const;

		virtual void				SetTexture(ResTexture tex);
		virtual ResTexture			GetTexture(void)const;

		virtual ParticleRenderType::eValue		GetType(void)const;
	public:
		ParticleRenderImpl*			mImpl;
	};
}

#endif // _IPARTICLERENDER_2014523104029_