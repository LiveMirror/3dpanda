#include "scene/ISceneMgr.h"
#include "SceneMgrImpl.h"

namespace panda
{
	ISceneMgr::ISceneMgr( void )
	{
		mImpl = new SceneMgrImpl(this);
	}

	ISceneMgr::ISceneMgr( SceneMgrImpl* pImpl ):mImpl(pImpl)
	{

	}

	ISceneMgr::~ISceneMgr( void )
	{
		if (NULL != mImpl)
		{
			delete mImpl;
		}
	}


	ISceneNode* ISceneMgr::GetRootNode( void )
	{
		return mImpl->mRootNode;
	}

	ISceneNode* ISceneMgr::CreateNode( ISceneNode* pParent /*= NULL*/ )
	{
		return mImpl->CreateNode(pParent);
	}

	ICamera* ISceneMgr::CreateCamera( void )
	{
		return mImpl->CreateCamera();
	}

	IMeshObject* ISceneMgr::CreateMeshObject( void )
	{
		return mImpl->CreateMeshObject();
	}
	
	IParticleObject* ISceneMgr::CreateParticleObject( void )
	{
		return mImpl->CreateParticleObject();
	}

	void ISceneMgr::Release( void )
	{
		delete this;
	}

	void ISceneMgr::SetAmbientLight( const Colorf& c )
	{
		mImpl->mAmbientColor = c;
	}

	
}
