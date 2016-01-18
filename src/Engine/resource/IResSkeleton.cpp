#include "resources/IResSkeleton.h"
#include "ResSkeletonImpl.h"

#define Ptr		((ResSkeletonImpl*)mImpl)

namespace panda
{
	IResSkeleton::IResSkeleton( ResSkeletonImpl* pImpl )
		:IResource(pImpl)
	{

	}

	IBone* IResSkeleton::CreateBone( const tstring& name )
	{
		return Ptr->CreateBone(name);
	}

	IBone* IResSkeleton::CreateBone( const tstring& name, u16 handle )
	{
		return Ptr->CreateBone(name, handle);
	}

	IBone* IResSkeleton::GetBone( const tstring& name )
	{
		return Ptr->GetBone(name);
	}

	IBone* IResSkeleton::GetBone( u16 handle )
	{
		return Ptr->GetBone(handle);
	}

	IAnimation* IResSkeleton::CreateAnimation( const tstring& name, f32 len )
	{
		return Ptr->CreateAnimation(name, len);
	}

	u16 IResSkeleton::GetNumBones( void )
	{
		return Ptr->mBonesList.size();
	}

	IBone* IResSkeleton::GetRootBone( void )
	{
		return Ptr->GetRootBone();
	}

	IAnimation* IResSkeleton::GetAnimation( const tstring& name )
	{
		return Ptr->GetAnimation(name);
	}

	IAnimation* IResSkeleton::GetAniByIndex( u32 index )
	{
		return Ptr->GetAniByIndex(index);
	}

	u32 IResSkeleton::GetNumAni( void )
	{
		return Ptr->mAnimations.size();
	}

	void IResSkeleton::RenameAnimation( const tstring& oldName, const tstring& newName )
	{
		Ptr->RenameAnimation(oldName, newName);
	}

	void IResSkeleton::DeleteAnimation( const tstring& name )
	{
		Ptr->DeleteAnimation(name);
	}
}