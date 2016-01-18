#include "ParticleObjectImpl.h"
#include "resources/IParticleSys.h"
#include "resources/IMaterial.h"
#include "scene/ISceneMgr.h"
#include "../rendersystem/renderqueue.h"
#include "../particleSystem/Particle.h"
#include "../particlesystem/particlecontroller.h"
#include "../particleSystem/ParticleTechnique.h"
#include "../particleSystem/ParticleRenderableSet.h"
#include "../resource/resourceimpl.h"
#include "../resource/resourcemgr.h"
#include "resources/ITexture.h"

namespace panda
{
	ParticleObjectImpl::ParticleObjectImpl( ISceneMgr* pCreator )
		:SceneObjectImpl(pCreator),
		mController(NULL)
	{

	}

	void ParticleObjectImpl::UpdateRenderQueue( ICamera* pCamera, RenderQueue* pQueue )
	{
		if (!mVisible || mRes.IsNull())
			return;

		ParticlePool::iterator it = mParticles.begin();
		while (it != mParticles.end())
		{
			// Õâ¸öÅÐ¶ÏÓï¾äÔÝÊ±
			if(!(*it).renderableSet->mMaterail.IsNull())
			{
				if ((*it).renderableSet->mMaterail->GetTextureAlpha())
				{
					pQueue->AddRenderObject((*it).renderableSet, RenderQueue::AlphaObject);
				}
				else
				{
					pQueue->AddRenderObject((*it).renderableSet, RenderQueue::NormalObject);
				}
			}
			it++;
		}
		_UpdatePartic();
	}

	void ParticleObjectImpl::SetResParticl( ResParticleSys particle )
	{
		if(mRes == particle)
		{
			return;
		}
		if(!mParticles.empty())
		{
			ParticlePool::iterator it = mParticles.begin();
			ParticleList::iterator pit;
			while (it != mParticles.end())
			{
				pit = (*it).particles.begin();
				while (pit != (*it).particles.end())
				{
					delete *pit;
					pit++;
				}
				(*it).particles.clear();
				it++;
			}
			mParticles.clear();
		}
		mRes = particle;
		if(mRes.IsNull())
		{
			if(NULL != mController)
			{
				mController->SetEnabled(false);
			}
			return;
		}
		u32 num = mRes->GetNumTechnique();
		for(u32 i = 0; i < num; i++)
		{
			IParticleRender* render = particle->GetTechnique(i)->GetRender();
			ParticleItem item;
			mParticles.push_back(item);
			ParticleItem& r = mParticles[mParticles.size() - 1];
			r.renderableSet = new ParticleRenderableSet(r.particles);
			r.renderableSet->mParent = this;
			r.renderableSet->mRender = render;
			r.renderableSet->mMaterail = particle->mImpl->mResMgr->CreateMaterial(MaterialType::Type_Effect);
			r.renderableSet->mMaterail->SetDiffuseTex(particle->mImpl->mResMgr->LoadTexture(_T("../media/smoke.png")));
		}

		if(NULL == mController)
		{
			mController = new ParticleController(mCreator->mImpl);
		}
		mController->mLoop = true;
	}

	void ParticleObjectImpl::_UpdatePartic( void )
	{
		if(!mController->GetEnabled())
		{
			return;
		}
		u32 num1 = mRes->GetNumTechnique();
		u32 num2 = mParticles.size();
		u32 num = math::Min(num1, num2);

		f32 tick = mController->GetTick();
		ParticleTechnique* tecq;
		for(u32 i = 0; i < num; i++)
		{
			 tecq = (ParticleTechnique*)mRes->GetTechnique(i);
			 ParticleItem& item = mParticles[i];
			 tecq->UpdateParticles(item.particles, tick);
		}
	}
}