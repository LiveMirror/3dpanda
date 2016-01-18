//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 16:47:51_
// 描述:  
//

#ifndef _RESSKELETONIMPL_201458164751_
#define _RESSKELETONIMPL_201458164751_

#include "ResourceImpl.h"
#include "Base/Matrix44.h"
#include <map>
#include <vector>

namespace panda
{
	class IAnimation;
	class IBone;
	class SkeletonSerialize;
	class ResourceMgr;
	class ResSkeletonImpl:public ResourceImpl
	{
	public:
		ResSkeletonImpl(ResourceMgr* resMgr);

		virtual bool	_Load(void);
		virtual void	_UnLoad(void);
		virtual void	_Save(const tchar* path);

		IBone*			CreateBone(const tstring& name);
		IBone*			CreateBone(const tstring& name, u16 handle);
		IBone*			GetBone(const tstring& name);
		IBone*			GetBone(u16 handle);

		IBone*			GetRootBone(void);

		IAnimation*		CreateAnimation(const tstring& name, f32 len);
		IAnimation*		GetAnimation(const tstring& name);
		IAnimation*		GetAniByIndex(u32 index);

		void			RenameAnimation(const tstring& oldName, const tstring& newName);
		void			DeleteAnimation(const tstring& name);
		void			GetBoneMatrices(Matrix44f* pMatrices);
		void			SetBindingPose(void);
		void			ResetBone(void);

	public:
		SkeletonSerialize*		_findSerialize(const tstring& ext);
		void					_DeriveRootBone(void);

	public:
		typedef	std::map<tstring, IBone*>	BoneMap;
		typedef std::vector<IBone*>			BoneList;
		BoneMap			mBonesByName;
		BoneList		mBonesList;

		// 根节点
		BoneList		mRootBones;

		// Bone automatic handles
		u16				mNextAutoHandle;

		typedef std::map<tstring, IAnimation*> AnimationMap;
		AnimationMap	mAnimations;
	};
}

#endif // _RESSKELETONIMPL_201458164751_