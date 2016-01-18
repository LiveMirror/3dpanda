//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/23 15:04:36_
// 描述:  
//

#ifndef _IPARTICLETECHNIQUE_2014523150436_
#define _IPARTICLETECHNIQUE_2014523150436_

#include "base/Struct.h"
#include "config.h"

namespace panda
{
	class IParticleRender;
	class IParticleAffector;
	class IParticleEmitter;
	class IParticleTechnique
	{
	public:
		virtual void					SetName(const tstring& name) = 0;
		virtual const tstring&			GetName(void)const = 0;

		// 发射器
		virtual IParticleEmitter*		AddEmitter(ParticleEmitterType::eValue type) = 0;
		virtual IParticleEmitter*		GetEmitter(u32 index) const = 0;
		virtual	u32						GetNumEmitters(void)const = 0;
		virtual	void					RemoveEmitter(u32 index) = 0;
		virtual	void					RemoveAllEmitters(void) = 0;

		// 效果器
		virtual IParticleAffector*		AddAffector(ParticleAffectorType::eValue type) = 0;
		virtual IParticleAffector*		GetAffector(u32 index) const = 0;
		virtual	u32						GetNumAffector(void)const = 0;
		virtual	void					RemoveAffector(u32 index) = 0;
		virtual	void					RemoveAllAffector(void) = 0;

		virtual void					SetRender(ParticleRenderType::eValue type) = 0;
		virtual IParticleRender*		GetRender(void) = 0;
	};
}

#endif // _IPARTICLETECHNIQUE_2014523150436_