//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/26 14:43:20_
// ����:  
//

#ifndef _PARTICLEFACTORY_2014526144320_
#define _PARTICLEFACTORY_2014526144320_

#include "base/Struct.h"

namespace panda
{
	class IParticleEmitter;
	class IParticleAffector;
	class IParticleRender;
	class ParticleFactory
	{
	public:
		static IParticleRender*			CreateRender(ParticleRenderType::eValue type);
		static IParticleAffector*		CreateAffector(ParticleAffectorType::eValue type);
		static IParticleEmitter*		CreateEmitter(ParticleEmitterType::eValue type);
	};
}

#endif // _PARTICLEFACTORY_2014526144320_