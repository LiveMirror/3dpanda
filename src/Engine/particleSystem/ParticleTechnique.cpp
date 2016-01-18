#include "ParticleTechnique.h"
#include "ParticleFactory.h"
#include "particleSystem/IParticleEmitter.h"
#include "particleSystem/IParticleRender.h"
#include "particlesystem/IParticleAffector.h"
#include "ParticleEmitterImpl.h"
#include "particleAffectorImpl.h"
#include "Particle.h"

namespace panda
{
	ParticleTechnique::ParticleTechnique( void )
		:mRender(NULL)
	{

	}

	void ParticleTechnique::SetName( const tstring& name )
	{
		mName = name;
	}

	const tstring& ParticleTechnique::GetName( void ) const
	{
		return mName;
	}

	IParticleEmitter* ParticleTechnique::AddEmitter( ParticleEmitterType::eValue type )
	{
		IParticleEmitter* pEmitter = ParticleFactory::CreateEmitter(type);
		if(NULL != pEmitter)
		{
			mEmitters.push_back(pEmitter);
		}
		return pEmitter;
	}

	IParticleEmitter* ParticleTechnique::GetEmitter( u32 index ) const
	{
		if(index >= mEmitters.size())
		{
			return NULL;
		}
		return mEmitters[index];
	}

	u32 ParticleTechnique::GetNumEmitters( void ) const
	{
		return mEmitters.size();
	}

	void ParticleTechnique::RemoveEmitter( u32 index )
	{
		if(index >= mEmitters.size())
		{
			return;
		}
		EmitterList::iterator it = mEmitters.begin();
		it + index;
		delete *it;
		mEmitters.erase(it);
	}

	void ParticleTechnique::RemoveAllEmitters( void )
	{
		EmitterList::iterator it = mEmitters.begin();
		while (it != mEmitters.end())
		{
			delete *it;
		}
		mEmitters.clear();
	}

	IParticleAffector* ParticleTechnique::AddAffector( ParticleAffectorType::eValue type )
	{
		IParticleAffector* affector = ParticleFactory::CreateAffector(type);
		if(NULL != affector)
		{
			mAffectors.push_back(affector);
		}
		return affector;
	}

	IParticleAffector* ParticleTechnique::GetAffector( u32 index ) const
	{
		if(index >= mAffectors.size())
		{
			return NULL;
		}
		return mAffectors[index];
	}

	u32 ParticleTechnique::GetNumAffector( void ) const
	{
		return mAffectors.size();
	}

	void ParticleTechnique::RemoveAffector( u32 index )
	{
		if(index >= mAffectors.size())
		{
			return;
		}
		AffectorList::iterator it = mAffectors.begin();
		it + index;
		delete *it;
		mAffectors.erase(it);
	}

	void ParticleTechnique::RemoveAllAffector( void )
	{
		AffectorList::iterator it = mAffectors.begin();
		while (it != mAffectors.end())
		{
			delete *it;
		}
		mAffectors.clear();
	}

	void ParticleTechnique::SetRender( ParticleRenderType::eValue type )
	{
		if(NULL == mRender)
		{
			delete mRender;
		}
		mRender = ParticleFactory::CreateRender(type);
	}

	IParticleRender* ParticleTechnique::GetRender( void )
	{
		return mRender;
	}

	void ParticleTechnique::UpdateParticles( ParticleList& particle, f32 time)
	{
		ParticleList::iterator pit = particle.begin();
		while (pit != particle.end())
		{
			if(!(*pit)->Update(time))
			{
				delete *pit;
				pit = particle.erase(pit);
			}
			else
			{
				pit++;
			}
		}

		AffectorList::iterator ait = mAffectors.begin();
		while(ait != mAffectors.end())
		{
			(*ait)->mImpl->AffectParticles(particle, time);
			ait++;
		}

		EmitterList::iterator eit = mEmitters.begin();
		while (eit != mEmitters.end())
		{
			(*eit)->mImpl->Emit(particle, time);
			eit++;
		}
	}
}