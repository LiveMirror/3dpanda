#include "ParticleRenderableSet.h"
#include "resources/IMaterial.h"
#include "particleSystem/IParticleRender.h"
#include "ParticleRenderImpl.h"
#include "../renderSystem/RenderSystem.h"
#include "../scene/ParticleObjectImpl.h"
#include "scene/ISceneNode.h"
#include "../renderSystem/MaterialSystem/EffectSetPass.h"
#include "Particle.h"

namespace panda
{
	ParticleRenderableSet::ParticleRenderableSet( ParticleList& particles )
		:mRender(NULL),
		mParticles(particles)
	{

	}

	const Matrix44f& ParticleRenderableSet::GetWorldTransforms( void ) const
	{
		return mParent->mParent->GetWorldMatrix();
	}

	void ParticleRenderableSet::RenderSets( RenderSystem* pRender, Pass* pass )
	{
		EffectSetPass* epass = (EffectSetPass*)pass;
		const Matrix44f& nodeMat = mParent->mParent->GetWorldMatrix();
		Matrix44f transform;
		ParticleList::iterator it = mParticles.begin();
		while(it != mParticles.end())
		{
			transform = Matrix44f::NormalMat();
			(*it)->GetTransform(transform);
			transform = transform * nodeMat;
			epass->SetWorldTransform(transform);
			epass->SetColor((*it)->mColor);
			mRender->mImpl->RenderParticle(*it, pRender->mGraph3D);
			it++;
		}
	}

	AABBOX& ParticleRenderableSet::GetBoundBox( void ) const
	{
		throw 0;
	}
}