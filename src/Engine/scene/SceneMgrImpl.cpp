#include "SceneMgrImpl.h"
#include "Scene/ISceneNode.h"
#include "SceneNodeImpl.h"
#include "Scene/ICamera.h"
#include "CameraImpl.h"
#include "MeshObjectImpl.h"
#include "Scene/IMeshObject.h"
#include "../Animation/AniObject.h"
#include "ParticleObjectImpl.h"
#include "scene/IParticleObject.h"
//#include "scene/ipointlight.h"


namespace panda
{
	SceneMgrImpl::SceneMgrImpl( ISceneMgr* pThis )
	{
		mThisPtr = pThis;
		SceneNodeImpl* pImpl = new SceneNodeImpl(mThisPtr);
		pImpl->mName = _T("Root");
		mRootNode = new ISceneNode(pImpl);
	}

	SceneMgrImpl::~SceneMgrImpl(void)
	{
		delete mRootNode;
	}

	ISceneNode* SceneMgrImpl::CreateNode( ISceneNode* pParent /*= NULL*/ )
	{
		if( NULL == pParent)
		{
			pParent = mRootNode;
		}
		return (ISceneNode*)pParent->CreateChild();
	}

	ICamera* SceneMgrImpl::CreateCamera( void )
	{
		CameraImpl* pImpl = new CameraImpl(mThisPtr);
		ICamera* pCam = new ICamera(pImpl);
		return pCam;
	}

	void SceneMgrImpl::FindVisibleObjects( ICamera* pCamera, RenderQueue* pQueue )
	{
		SceneNodeImpl* pImpl = (SceneNodeImpl*)mRootNode->mImpl;
		pImpl->FindVisibleObjects(pCamera, pQueue);
	}

	IMeshObject* SceneMgrImpl::CreateMeshObject( void )
	{
		MeshObjectImpl* pImpl = new MeshObjectImpl(mThisPtr);
		IMeshObject* pMeshObj = new IMeshObject(pImpl);
		return pMeshObj;
	}


	IParticleObject* SceneMgrImpl::CreateParticleObject( void )
	{
		ParticleObjectImpl* pImpl = new ParticleObjectImpl(mThisPtr);
		IParticleObject* pPart = new IParticleObject(pImpl);
		return pPart;
	}


	void SceneMgrImpl::UpdateAnimation( f32 time )
	{
		AniObjectList::iterator itr = mAnimations.begin();
		while (itr != mAnimations.end())
		{
			AniObject* ani = *itr;
			itr++;
			ani->Update(time);
		}
	}

	IPointLight* SceneMgrImpl::CreateLight( void )
	{
		return NULL;
	}

	void SceneMgrImpl::RemoveLight( IPointLight* pLight )
	{
		LightList::iterator itr = mLights.begin();
		while (itr != mLights.end())
		{
			if(*itr == pLight)
			{
				mLights.erase(itr);
				delete pLight;
			}
			itr++;
		}
	}
}