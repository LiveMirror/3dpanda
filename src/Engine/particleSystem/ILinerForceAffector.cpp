#include "particleSystem/ILinerForceAffector.h"
#include "linerforceaffectorimpl.h"

#define Ptr		((LinerForceAffectorImpl*)mImpl)

namespace panda
{
	ILinerForceAffector::ILinerForceAffector( LinerForceAffectorImpl* impl )
		:IParticleAffector(impl)
	{

	}

	void ILinerForceAffector::SetForceVector( const Vector3Df& force )
	{
		Ptr->mForceVector = force;
	}

	const Vector3Df& ILinerForceAffector::GetForceVector() const
	{
		return Ptr->mForceVector;
	}
}