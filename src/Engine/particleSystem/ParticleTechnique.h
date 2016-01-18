//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/23 18:01:59_
// 描述:  
//

#ifndef _PARTICLETECHNIQUE_2014523180159_
#define _PARTICLETECHNIQUE_2014523180159_

#include "particleSystem/IParticleTechnique.h"
#include <vector>
#include "../TypeDef.h"

namespace panda
{
	class ParticleTechnique:public IParticleTechnique
	{
	public:
		ParticleTechnique(void);

		virtual void					SetName(const tstring& name);
		virtual const tstring&			GetName(void)const;

		// 发射器
		virtual IParticleEmitter*		AddEmitter(ParticleEmitterType::eValue type);
		virtual IParticleEmitter*		GetEmitter(u32 index) const;
		virtual	u32						GetNumEmitters(void)const;
		virtual	void					RemoveEmitter(u32 index);
		virtual	void					RemoveAllEmitters(void);

		// 效果器
		virtual IParticleAffector*		AddAffector(ParticleAffectorType::eValue type);
		virtual IParticleAffector*		GetAffector(u32 index) const;
		virtual	u32						GetNumAffector(void)const;
		virtual	void					RemoveAffector(u32 index);
		virtual	void					RemoveAllAffector(void);

		virtual void					SetRender(ParticleRenderType::eValue type);
		virtual IParticleRender*		GetRender(void);


		void				UpdateParticles(ParticleList& particle, f32 time);

	public:
		typedef	std::vector<IParticleEmitter*>	EmitterList;
		typedef std::vector<IParticleAffector*>	AffectorList;
		EmitterList			mEmitters;
		AffectorList		mAffectors;
		tstring				mName;
		IParticleRender*	mRender;

		f32					mTimeToLive;
		bool				mLoop;
	};
}

#endif // _PARTICLETECHNIQUE_2014523180159_