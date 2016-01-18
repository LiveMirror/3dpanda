#include "SceneObjectImpl.h"

namespace panda
{
	SceneObjectImpl::SceneObjectImpl( ISceneMgr* pCreator )
		:mCreator(pCreator),
		mParent(NULL),
		mVisible(true),
		mEnableProbe(true)
	{

	}

	SceneObjectImpl::~SceneObjectImpl( void )
	{

	}

	void SceneObjectImpl::SetVisible( bool visible )
	{
		mVisible = visible;
	}

	void SceneObjectImpl::UpdateRenderQueue( ICamera* pCamera, RenderQueue* pQueue )
	{
		// do nothing
	}

	bool SceneObjectImpl::Probe( const Ray& ray, ProbeResult& result)
	{
		return false;
	}

	bool SceneObjectImpl::ProbeBindBox( const Ray& ray, bool transformRay /*= true*/ )
	{
		return false;
	}

	bool SceneObjectImpl::Intersects( const Ray& ray, ProbeResult& result, bool transformRay /*= true*/ )
	{
		return false;
	}
}