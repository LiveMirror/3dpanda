#include "SceneNodeImpl.h"
#include "Scene/ISceneNode.h"
#include "Scene/ISceneObject.h"
#include "SceneObjectImpl.h"
#include "../RenderSystem/RenderQueue.h"

namespace panda
{
	SceneNodeImpl::SceneNodeImpl( ISceneMgr* pSceneMgr )
	{
		mSceneMgr = pSceneMgr;
	}

	SceneNodeImpl::~SceneNodeImpl( void )
	{
		ObjectList::iterator itr = mObjects.begin();
		while (itr != mObjects.end())
		{
			delete *itr;
			itr++;
		}
	}

	INode* SceneNodeImpl::CreateChild( void )
	{
		SceneNodeImpl* pImpl = new SceneNodeImpl(mSceneMgr);
		pImpl->mParent = mThisPtr;
		ISceneNode* pNode = new ISceneNode(pImpl);
		mChildren.push_back(pNode);
		return pNode;
	}

	void SceneNodeImpl::FindVisibleObjects( ICamera* pCamera, RenderQueue* pQueue, bool displayChild /*= true*/ )
	{
		if(!mVisible) return;

		ObjectList::iterator itr = mObjects.begin();
		while (itr != mObjects.end())
		{
			(*itr)->mImpl->UpdateRenderQueue(pCamera, pQueue);
			itr++;
		}

		// µÝ¹é×Ó½Úµã
		if(displayChild)
		{
			SceneNodeImpl* pTemp;
			NodeList::iterator nodeItr = mChildren.begin();
			while(nodeItr != mChildren.end())
			{
				pTemp = (SceneNodeImpl*)(*nodeItr)->mImpl;
				pTemp->FindVisibleObjects(pCamera, pQueue, true);
				nodeItr++;
			}
		}
	}

	void SceneNodeImpl::AttachObject( ISceneObject* object )
	{
		// remove it if the parent is not null
		if(NULL != object->GetParentNode())
		{
			SceneNodeImpl* pParent = (SceneNodeImpl*)object->GetParentNode()->mImpl;
			pParent->DisAttachObject(object);
		}

		mObjects.push_back(object);
		SceneObjectImpl* pImpl = object->mImpl;
		pImpl->mParent = (ISceneNode*)mThisPtr;
	}

	bool SceneNodeImpl::Probe( const Ray& ray, ProbeResult& result)
	{
		// Recursion to find out all objects that may intersect
		ObjectList objs;
		_ProbeWithBox(ray, objs);

		f32 d = F32_MAX;
		ProbeResult r;
		ObjectList::iterator i = objs.begin();
		while (i != objs.end())
		{
			SceneObjectImpl* pImpl = (*i)->mImpl;
			if(pImpl->Intersects(ray, r))
			{
				if (r.distance < d)
				{
					d = r.distance;
					result = r;
				}
			}
			i++;
		}
		return result.object != NULL;
	}

	void SceneNodeImpl::_ProbeWithBox( const Ray& ray, ObjectList& outList )
	{
		if (!mVisible)
		{
			return;
		}

		ObjectList::iterator itr = mObjects.begin();
		while (itr != mObjects.end())
		{
			SceneObjectImpl* pImpl = (*itr)->mImpl;
			if (pImpl->mEnableProbe)
			{
				if(pImpl->ProbeBindBox(ray))
				{
					outList.push_back(*itr);
				}
			}
			itr++;
		}

		NodeList::iterator i = mChildren.begin();
		while (i != mChildren.end())
		{
			SceneNodeImpl* pImpl = (SceneNodeImpl*)(*i)->mImpl;
			pImpl->_ProbeWithBox(ray, outList);
			i++;
		}
	}

	void SceneNodeImpl::DisAttachObject( ISceneObject* object )
	{
		ObjectList::iterator itr = mObjects.begin();
		while (itr != mObjects.end())
		{
			if(object == *itr)
			{
				SceneObjectImpl* pImpl = (*itr)->mImpl;
				pImpl->mParent = NULL;
				mObjects.erase(itr);
				return;
			}
			itr++;
		}
	}

	ISceneObject* SceneNodeImpl::GetObject( u32 index ) const
	{
		if (index >= mObjects.size())
		{
			return NULL;
		}
		ObjectList::const_iterator itr = mObjects.begin();
		for (u32 i = 0; i < index; i++)
		{
			itr++;
		}
		return *itr;
	}
}