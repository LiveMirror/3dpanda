#include "particleSystem/IParticleRender.h"
#include "ParticleRenderImpl.h"
#include "resources/ITexture.h"
namespace panda
{
	IParticleRender::IParticleRender( ParticleRenderImpl* impl )
		:mImpl(impl)
	{

	}

	void IParticleRender::SetName( const tstring& name )
	{
		mImpl->mName = name;
	}

	const tstring& IParticleRender::GetName( void ) const
	{
		return mImpl->mName;
	}

	ParticleRenderType::eValue IParticleRender::GetType( void ) const
	{
		return mImpl->mType;
	}

	void IParticleRender::SetTexture( ResTexture tex )
	{
		mImpl->mImage = tex;
	}

	ResTexture IParticleRender::GetTexture( void ) const
	{
		return mImpl->mImage;
	}
}