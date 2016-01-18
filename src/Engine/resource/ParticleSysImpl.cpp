#include "ParticleSysImpl.h"
#include "../particlesystem/Particletechnique.h"

namespace panda
{
	ParticleSysImpl::ParticleSysImpl( ResourceMgr* resMgr )
		:ResourceImpl(resMgr)
	{
		mResType = ResType::ResType_Effect;
	}

	ParticleSysImpl::~ParticleSysImpl( void )
	{

	}

	bool ParticleSysImpl::_Load( void )
	{
		return false;
	}

	void ParticleSysImpl::_UnLoad( void )
	{

	}


	IParticleTechnique* ParticleSysImpl::CreateTechnique( const tstring& name )
	{
		ParticleTechnique* tech = new ParticleTechnique;
		tech->mName = name;
		mTechniques.push_back(tech);
		return tech;
	}

	IParticleTechnique* ParticleSysImpl::GetTechnique( u32 index ) const
	{
		if(index >= mTechniques.size())
		{
			return NULL;
		}
		return mTechniques[index];
	}

	void ParticleSysImpl::RemoveAllTechnique( void )
	{
		//
	}

	void ParticleSysImpl::_Save( const tchar* path )
	{

	}

	void ParticleSysImpl::RemoveTechnique( u32 index )
	{
		if(index < mTechniques.size())
		{
			TechniqueList::iterator it = mTechniques.begin();
			it + index;
			delete *it;
			mTechniques.erase(it);
		}
	}
}