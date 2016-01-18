#include "resources/IResource.h"
#include "ResourceImpl.h"

namespace panda
{
	IResource::IResource( ResourceImpl* pImpl )
		:mImpl(pImpl)
	{
		if(NULL != mImpl)
		{
			mImpl->BindThis(this);
		}
	}

	IResource::~IResource( void )
	{

	}


	const tchar* IResource::GetResPath( void ) const
	{
		return mImpl->mPath.c_str();
	}

	bool IResource::Load( void )
	{
		return mImpl->Load();
	}

	void IResource::Reload( void )
	{
		mImpl->Load();
	}

	void IResource::UnLoad( void )
	{
		mImpl->UnLoad();
	}

	bool IResource::Save( const tchar* path /*= NULL*/ )
	{ 
		mImpl->Save(path);
		return true;
	}

	bool IResource::IsLoaded( void ) const
	{
		return mImpl->mResState == ResState::Loaded;
	}

	ResType::eValue IResource::GetResType( void ) const
	{
		return mImpl->mResType;
	}

	ResState::eValue IResource::GetState( void ) const
	{
		return mImpl->mResState;
	}

	void IResource::SetData( void* pData )
	{
		mImpl->mUserData = pData;
	}

	void* IResource::GetData( void ) const
	{
		return mImpl->mUserData;
	}

	void IResource::Release( void )
	{

	}

	void IResource::SetPath( const tchar* path )
	{
		if(mImpl->mPath.empty())
		{
			mImpl->mPath = path;
		}
	}
}