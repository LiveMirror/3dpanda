#include "scene/ISceneNode.h"
#include "SceneNodeImpl.h"
#include "Scene/ISceneObject.h"

#define Ptr ((SceneNodeImpl*)mImpl)

namespace panda
{
	ISceneNode::ISceneNode( SceneNodeImpl* pImpl ):INode(pImpl)
	{

	}

	void ISceneNode::AttachObject( ISceneObject* object )
	{
		if (object->GetParentNode() == this)
		{
			return;
		}
		Ptr->AttachObject(object);
	}

	void ISceneNode::DisAttachObject( ISceneObject* object )
	{
		if (object->GetParentNode() == this)
		{
			Ptr->DisAttachObject(object);
		}
	}

	bool ISceneNode::Probe( const Ray& ray, ProbeResult& result)
	{
		return Ptr->Probe(ray, result);
	}

	void ISceneNode::SetName( const tchar* name )
	{
		Ptr->mName = name;
	}

	const tchar* ISceneNode::GetName( void )
	{
		return Ptr->mName.c_str();
	}

	void ISceneNode::SetVisible( bool visible )
	{
		Ptr->mVisible = visible;
	}

	bool ISceneNode::GetVisible( void ) const
	{
		return Ptr->mVisible;
	}

	void ISceneNode::Release( void )
	{
		if (NULL != mImpl->mParent)
		{
			mImpl->mParent->mImpl->RemoveChild(this);
		}
		delete this;
	}

	u32 ISceneNode::GetNumObject( void )
	{
		return Ptr->mObjects.size();
	}

	ISceneObject* ISceneNode::GetObject( u32 index ) const
	{
		return Ptr->GetObject(index);
	}

	ISceneMgr* ISceneNode::GetSceneMgr( void ) const
	{
		return Ptr->mSceneMgr;
	}
}