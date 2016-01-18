#include "LinerForceAffectorImpl.h"
#include "Particle.h"

namespace panda
{
	LinerForceAffectorImpl::LinerForceAffectorImpl( void )
	{
		mType = ParticleAffectorType::LinerForce;
		mForceVector.y = -1;
	}

	void LinerForceAffectorImpl::AffectParticles( ParticleList& pattilces, f32 time )
	{
		ParticleList::iterator pit = pattilces.begin();
		Vector3Df scaledVector = mForceVector * time;
		while (pit != pattilces.end())
		{
			(*pit)->mDirection += scaledVector;
			pit++;
		}
	}
}