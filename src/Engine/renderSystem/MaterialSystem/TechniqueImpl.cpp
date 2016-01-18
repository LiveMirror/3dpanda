#include "TechniqueImpl.h"
#include "Pass.h"
#include "../../resource/MaterialImpl.h"
#include "../../resource/ResourceMgr.h"
#include "PassMgr.h"

namespace panda
{
	TechniqueImpl::TechniqueImpl(IDirect3DDevice9* d3dDevice)
		:mD3dDevice(d3dDevice)
	{

	}

	TechniqueImpl::~TechniqueImpl( void )
	{
		PassList::iterator itr = mPasses.begin();
		while (itr != mPasses.end())
		{
			delete *itr;
			itr++;
		}
	}


	void TechniqueImpl::RenderObject( SceneObjectImpl* obj, ICamera* pCam )
	{

	}

	u16 TechniqueImpl::GetNumPasses( void )
	{
		return mPasses.size();
	}

	IPass* TechniqueImpl::GetPass( u16 index )
	{
		if (index >= mPasses.size())
		{
			return NULL;
		}
		return mPasses[index];
	}

	IPass* TechniqueImpl::CreatePass( PassType::eValue type/* = PassType::type_StaticMesh*/ )
	{
		Pass* p = (Pass*)mParent->mResMgr->mPassMgr->CreatePass(type);
		p->mParent = this;
		mPasses.push_back(p);
		return p;
	}

	void TechniqueImpl::RemovePass( IPass* pass )
	{
		PassList::iterator itr = mPasses.begin();
		while (itr != mPasses.end())
		{
			if(pass == *itr)
			{
				delete pass;
				mPasses.erase(itr);
				return;
			}
			itr++;
		}
	}
}