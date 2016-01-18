//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/8 17:11:07_
// ����:  
//

#ifndef _BONEIMPL_201458171107_
#define _BONEIMPL_201458171107_

#include "NodeImpl.h"
#include "Base/Matrix44.h"

namespace panda
{
	class IBone;
	class IResSkeleton;
	class IMeshObject;
	class BoneImpl:public NodeImpl
	{
	public:
		BoneImpl(IResSkeleton* creater);

		//! �����ӽڵ�
		virtual INode*		CreateChild(void);

		void				AddChild(IBone* pBone);

		void				SetBindPose(void);

		//! Gets the transform which takes bone space to current from the binding pose
		void				GetOffsetTransform(Matrix44f& m);

	public:
		IResSkeleton*	mCreater;
		tstring			mName;
		u16				mHandle;

		Matrix44f		mOffsetTransform;
	};
}

#endif // _BONEIMPL_201458171107_