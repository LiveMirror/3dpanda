//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 16:23:21_
// 描述:  
//

#ifndef _KEYFRAMEIMPL_201458162321_
#define _KEYFRAMEIMPL_201458162321_

#include "Base/Config.h"
#include "Base/Vector3D.h"
#include "Base/Quaternion.h"

namespace panda
{
	class AnimationTrackImpl;
	class KeyFrameImpl
	{
	public:
		KeyFrameImpl(AnimationTrackImpl* parent, f32 time);
		virtual ~KeyFrameImpl(void);
	public:
		f32						mTime;
		AnimationTrackImpl*		mParentTrack;

	};

	class TransformKeyFrameImpl:public KeyFrameImpl
	{
	public:
		TransformKeyFrameImpl(AnimationTrackImpl* parent, f32 time);
		virtual ~TransformKeyFrameImpl(void);
		void				SetTranslate(const Vector3Df& trans);
		void				SetScale(const Vector3Df& scale);
		void				SetRotation(const Quaternion& rot);
	public:
		Vector3Df	mTranslate;
		Vector3Df	mScale;
		Quaternion	mRotate;
	};
}

#endif // _KEYFRAMEIMPL_201458162321_