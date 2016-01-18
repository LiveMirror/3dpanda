#include "scene/ISceneObject.h"
#include "SceneObjectImpl.h"
#include "Scene/ISceneNode.h"

namespace panda
{
	ISceneObject::ISceneObject( SceneObjectImpl* pImpl )
		:mImpl(pImpl)
	{
		if (NULL != mImpl)
		{
			mImpl->mThisPtr = this;
		}
	}

	ISceneObject::~ISceneObject( void )
	{
		delete mImpl;
	}

	ISceneMgr* ISceneObject::GetSceneMgr( void ) const
	{
		return mImpl->mCreator;
	}

	ISceneNode* ISceneObject::GetParentNode( void ) const
	{
		return mImpl->mParent;
	}

	bool ISceneObject::GetVisible( void ) const
	{
		return mImpl->mVisible;
	}

	void ISceneObject::SetVisible( bool visible )
	{
		mImpl->SetVisible(visible);
	}

	void ISceneObject::Release()
	{
		if (NULL != mImpl->mParent)
		{
			ISceneNode* parent = (ISceneNode*)mImpl->mParent;
			parent->DisAttachObject(this);
		}
		delete this;
	}

	bool ISceneObject::Probe( const Ray& ray, ProbeResult& result)
	{
		return mImpl->Probe(ray, result);
	}

	const AABBOX& ISceneObject::GetBindBox( void ) const
	{
		return mImpl->mBindBox;
	}

	void ISceneObject::SetEnableProbe( bool enable )
	{
		mImpl->mEnableProbe = enable;
	}

	bool ISceneObject::GetEnableProbe( void ) const
	{
		return mImpl->mEnableProbe;
	}

	void ISceneObject::SetName( const tchar* name )
	{
		mImpl->mName = name;
	}

	const tchar* ISceneObject::GetName( void ) const
	{
		return mImpl->mName.c_str();
	}
}