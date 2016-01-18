#include "scene/IParticleObject.h"
#include "ParticleObjectImpl.h"
#include "resources/IParticleSys.h"
#include "../particleSystem/ParticleController.h"

#define Ptr		((ParticleObjectImpl*)mImpl)

namespace panda
{
	IParticleObject::IParticleObject( ParticleObjectImpl* impl )
		:ISceneObject(impl)
	{

	}

	void IParticleObject::SetResParticl( ResParticleSys particle )
	{
		Ptr->SetResParticl(particle);
	}

	ResParticleSys IParticleObject::GetResParticl( void )
	{
		return Ptr->mRes;
	}

	void IParticleObject::Play( void )
	{
		if(NULL != Ptr->mController)
		{
			Ptr->mController->mCurTime = 0;
			Ptr->mController->SetEnabled(true);
		}
	}

	bool IParticleObject::IsPlay( void )
	{
		if(NULL != Ptr->mController)
		{
			return Ptr->mController->GetEnabled();
		}
		return false;
	}

	void IParticleObject::Stop( void )
	{
		if(NULL != Ptr->mController)
		{
			Ptr->mController->SetEnabled(false);
		}
	}
}