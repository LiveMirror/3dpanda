#include "resources/IParticleSys.h"
#include "ParticleSysImpl.h"

#define Ptr		((ParticleSysImpl*)mImpl)

namespace panda
{
	IParticleSys::IParticleSys( ParticleSysImpl* impl )
		:IResource(impl)
	{

	}

	IParticleTechnique* IParticleSys::CreateTechnique( const tstring& name )
	{
		return Ptr->CreateTechnique(name);
	}

	u32 IParticleSys::GetNumTechnique( void ) const
	{
		return Ptr->mTechniques.size();
	}

	IParticleTechnique* IParticleSys::GetTechnique( u32 index ) const
	{
		return Ptr->GetTechnique(index);
	}

	void IParticleSys::RemoveAllTechnique( void )
	{
		Ptr->RemoveAllTechnique();
	}

	void IParticleSys::RemoveTechnique( u32 index )
	{
		Ptr->RemoveTechnique(index);
	}
}