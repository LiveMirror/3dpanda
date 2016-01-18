#include "ColourAffectorImpl.h"
#include "Particle.h"

namespace panda
{
	ColourAffectorImpl::ColourAffectorImpl( void )
	{
		mType = ParticleAffectorType::Colour;
		mAddColor.a = 0;
		mAddColor.r = 0.1f;mAddColor.g = 0;mAddColor.b = 0;
	}

	void ColourAffectorImpl::AffectParticles( ParticleList& pattilces, f32 time )
	{
		ParticleList::iterator pit = pattilces.begin();
		Colorf add = mAddColor * time;
		while (pit != pattilces.end())
		{
			(*pit)->mColor += add;
			pit++;
		}
	}
}