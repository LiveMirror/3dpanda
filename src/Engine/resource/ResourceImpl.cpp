#include "ResourceImpl.h"

namespace panda
{
	ResourceImpl::ResourceImpl( ResourceMgr* resMgr )
		:mResMgr(resMgr),
		mIsCreater(false),
		mUserData(NULL)
	{

	}

	ResourceImpl::~ResourceImpl( void )
	{

	}

	void ResourceImpl::BindThis( IResource* ptr )
	{
		mThis = ptr;
	}

	bool ResourceImpl::Load( void )
	{
		if (ResState::Loaded == mResState)
		{
			return true;
		}
		if (ResState::Loading == mResState)
		{
			return false;
		}

		mResState = ResState::Loading;
		if (_Load())
		{
			mResState = ResState::Loaded;
			return true;
		}
		mResState = ResState::Error;
		return false;
	}

	void ResourceImpl::UnLoad( void )
	{
		if (mResState == ResState::Loaded)
		{
			_UnLoad();
		}
	}

	void ResourceImpl::Save( const tchar* path /*= NULL*/ )
	{
		_Save(path);
	}
}