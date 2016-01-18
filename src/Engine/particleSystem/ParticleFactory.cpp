#include "ParticleFactory.h"
#include "particlesystem/IParticleEmitter.h"
#include "ParticleEmitterImpl.h"
#include "particleSystem/IBillboardRender.h"
#include "BillboardRenderImpl.h"
#include "particlesystem/ILinerforceAffector.h"
#include "LinerforceAffectorImpl.h"
#include "particlesystem/IColourAffector.h"
#include "ColourAffectorImpl.h"

namespace panda
{
	IParticleRender* ParticleFactory::CreateRender( ParticleRenderType::eValue type )
	{
		IParticleRender* render = NULL;
		switch(type)
		{
		case ParticleRenderType::Billborad:
			{
				render = new IBillboardRender(new BillboardRenderImpl);
				break;
			}
		}
		return render;
	}

	IParticleAffector* ParticleFactory::CreateAffector( ParticleAffectorType::eValue type )
	{
		IParticleAffector* affector = NULL;
		switch(type)
		{
		case ParticleAffectorType::Colour:
			{
				affector = new IColourAffector(new ColourAffectorImpl);
				break;
			}
		case ParticleAffectorType::LinerForce:
			{
				affector = new ILinerForceAffector(new LinerForceAffectorImpl);
				break;
			}
		}
		return affector;
	}

	IParticleEmitter* ParticleFactory::CreateEmitter( ParticleEmitterType::eValue type )
	{
		IParticleEmitter* pEmitter = NULL;
		switch(type)
		{
		case ParticleEmitterType::Point:
			{
				pEmitter = new IParticleEmitter(new ParticleEmitterImpl);
				break;
			}
		}
		return pEmitter;
	}
}
