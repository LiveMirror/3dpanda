#include "particleSystem/IParticleAffector.h"
#include "ParticleAffectorImpl.h"

namespace panda
{
	IParticleAffector::IParticleAffector( ParticleAffectorImpl* impl )
		:mImpl(impl)
	{

	}

	void IParticleAffector::SetName( const tstring& name )
	{
		mImpl->mName = name;
	}

	const tstring& IParticleAffector::GetName( void ) const
	{
		return mImpl->mName;
	}

	ParticleAffectorType::eValue IParticleAffector::GetType( void ) const
	{
		return mImpl->mType;
	}

	IParticleTechnique* IParticleAffector::GetParent( void ) const
	{
		return mImpl->mParent;
	}
}