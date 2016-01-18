#include "ResSkeletonImpl.h"
#include "ResourceMgr.h"
#include "FileStream.h"
#include <algorithm>
#include "../animation/Animation.h"
#include "skeletonserialize/SkeletonSerialize.h"
#include "skeletonserialize/hySkeletonSerialize.h"
#include "skeletonserialize/OgreSkeletonSerialize.h"
#include "../scene/boneimpl.h"
#include "scene/IBone.h"

namespace panda
{
	ResSkeletonImpl::ResSkeletonImpl( ResourceMgr* resMgr )
		:ResourceImpl(resMgr),
		mNextAutoHandle(0)
	{
		mResType = ResType::ResType_Skeletion;
	}

	bool ResSkeletonImpl::_Load( void )
	{
		// 根据后缀名判断格式
		tstring ext;
		FileStream::GetFileExtension(mPath, ext);

		// 将后缀到小写
		transform(ext.begin(), ext.end(), ext.begin(), tolower);

		// 查找相应的序列化器
		SkeletonSerialize* pLoader = _findSerialize(ext);

		FileStream file;
		
		// 判断加载是否成功
		if(NULL == pLoader 
			|| !file.Open(mPath.c_str(), true)
			|| !pLoader->ImportSkeleton(file, this))
		{
			if(NULL != pLoader)
			{
				delete pLoader;
			}
			return false;
		}

		delete pLoader;
		return true;
	}

	void ResSkeletonImpl::_UnLoad( void )
	{
		AnimationMap::iterator it = mAnimations.begin();
		while (it != mAnimations.end())
		{
			delete it->second;
			it++;
		}
	}

	SkeletonSerialize* ResSkeletonImpl::_findSerialize( const tstring& ext )
	{
		if(ext.length() == 0 || ext == _T("3dm"))		// shine
		{

		}
		else if(ext == _T("hyskn"))
		{
			return new hySkeletonSerialize;
		}
		else if(ext == _T("skeleton"))		// ogre
		{
			return new OgreSkeletonSerialize;
		}
		/*else if(ext == _T("skl"))
		{
			return new SklSerialize;
		}*/
		return NULL;
	}

	IBone* ResSkeletonImpl::CreateBone( const tstring& name )
	{
		return CreateBone(name, mNextAutoHandle++);
	}

	IBone* ResSkeletonImpl::CreateBone( const tstring& name, u16 handle )
	{
		if (GetBone(name) != NULL)
		{
			return NULL;
		}
		// Check handle not used
		if (handle < mBonesList.size() && mBonesList[handle] != NULL)
		{
			//throw _T("A bone with the handle already exists");
			return mBonesList[handle];
			return NULL;
		}

		BoneImpl* pImpl = new BoneImpl((IResSkeleton*)mThis);
		pImpl->mName = name;
		pImpl->mHandle = handle;
		IBone* pBone = new IBone(pImpl);
		if (mBonesList.size() <= handle)
		{
			mBonesList.resize(handle+1);
		}
		mBonesByName[name] = pBone;
		mBonesList[handle] = pBone;
		return pBone;
	}

	IBone* ResSkeletonImpl::GetBone( const tstring& name )
	{
		BoneMap::iterator itr = mBonesByName.find(name);
		if (itr != mBonesByName.end())
		{
			return itr->second;
		}
		return NULL;
	}

	IBone* ResSkeletonImpl::GetBone( u16 handle )
	{
		if (handle < mBonesList.size())
		{
			return mBonesList[handle];
		}
		return NULL;
	}

	IAnimation* ResSkeletonImpl::CreateAnimation( const tstring& name, f32 len )
	{
		if (mAnimations.find(name) != mAnimations.end())
		{
			throw _T("An animation with the name already exists");
		}
		Animation* pAni = new Animation(name, len);
		mAnimations[name] = pAni;
		return pAni;
	}

	void ResSkeletonImpl::_DeriveRootBone( void )
	{
		if (mBonesList.empty())
		{
			throw _T("Cannot derive root bone as this skeleton has no bones!");
		}
		mRootBones.clear();
		BoneList::iterator i = mBonesList.begin();
		while (i != mBonesList.end())
		{
			if ((*i)->GetParent() == NULL)
			{
				mRootBones.push_back(*i);
			}
			i++;
		}
	}

	IBone* ResSkeletonImpl::GetRootBone( void )
	{
		if (mRootBones.empty())
		{
			_DeriveRootBone();
		}
		return mRootBones[0];
	}

	void ResSkeletonImpl::_Save( const tchar* path )
	{
		FileStream file;
		if (!file.Open(path, false))
		{
			return;
		}
		hySkeletonSerialize* serialize = new hySkeletonSerialize;
		serialize->ExportSkeleton(file, this);
	}

	IAnimation* ResSkeletonImpl::GetAnimation( const tstring& name )
	{
		AnimationMap::iterator itr = mAnimations.find(name);
		if (itr != mAnimations.end())
		{
			return itr->second;
		}
		return NULL;
	}

	IAnimation* ResSkeletonImpl::GetAniByIndex( u32 index )
	{
		if(index >= mAnimations.size())
		{
			return NULL;
		}
		AnimationMap::iterator itr = mAnimations.begin();
		for(u32 i = 0; i < index; i++)
		{
			itr++;
		}
		return itr->second;
	}

	void ResSkeletonImpl::GetBoneMatrices( Matrix44f* pMatrices )
	{
		BoneList::iterator itr = mBonesList.begin();
		while (itr != mBonesList.end())
		{
			BoneImpl* bone = (BoneImpl*)(*itr)->mImpl;
			bone->GetOffsetTransform(*pMatrices);
			pMatrices++;
			itr++;
		}
	}

	void ResSkeletonImpl::SetBindingPose( void )
	{
		BoneList::iterator i = mBonesList.begin();
		while (i != mBonesList.end())
		{
			BoneImpl* bone = (BoneImpl*)(*i)->mImpl;
			bone->SetBindPose();
			i++;
		}
	}

	void ResSkeletonImpl::ResetBone( void )
	{
		BoneList::iterator i = mBonesList.begin();
		while (i != mBonesList.end())
		{
			BoneImpl* bone = (BoneImpl*)(*i)->mImpl;
			bone->ResetToInitialState();
			i++;
		}
	}

	void ResSkeletonImpl::RenameAnimation( const tstring& oldName, const tstring& newName )
	{
		AnimationMap::iterator itr = mAnimations.find(oldName);
		if (itr != mAnimations.end())
		{
			Animation* pAni = (Animation*)itr->second;
			pAni->mName = newName;
			mAnimations.erase(itr);
			mAnimations[newName] = pAni;
		}
	}

	void ResSkeletonImpl::DeleteAnimation( const tstring& name )
	{
		AnimationMap::iterator itr = mAnimations.find(name);
		if (itr != mAnimations.end())
		{
			Animation* pAni = (Animation*)itr->second;
			delete pAni;
			mAnimations.erase(itr);
		}
	}
}