//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 16:46:21_
// 描述:  
//

#ifndef _IRESSKELETON_201458164621_
#define _IRESSKELETON_201458164621_

#include "IResource.h"

namespace panda
{
	class IBone;
	class IAnimation;
	class ResSkeletonImpl;
	class IResSkeleton:public IResource
	{
	public:
		IResSkeleton(ResSkeletonImpl* pImpl);

		virtual IBone*		CreateBone(const tstring& name);
		virtual IBone*		CreateBone(const tstring& name, u16 handle);
		virtual IBone*		GetBone(const tstring& name);
		virtual IBone*		GetBone(u16 handle);
		virtual IBone*		GetRootBone(void);
		virtual u16			GetNumBones(void);

		virtual IAnimation*	CreateAnimation(const tstring& name, f32 len);
		virtual IAnimation*	GetAnimation(const tstring& name);
		virtual void		RenameAnimation(const tstring& oldName, const tstring& newName);
		virtual void		DeleteAnimation(const tstring& name);
		virtual IAnimation*	GetAniByIndex(u32 index);
		virtual u32			GetNumAni(void);
	};
}

#endif // _IRESSKELETON_201458164621_