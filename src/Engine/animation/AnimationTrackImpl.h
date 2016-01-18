//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 16:26:27_
// 描述:  
//

#ifndef _ANIMATIONTRACKIMPL_201458162627_
#define _ANIMATIONTRACKIMPL_201458162627_

#include "Base/Config.h"
#include "Base/Struct.h"
#include "KeyFrameImpl.h"
#include <vector>


namespace panda
{
	class IAnimation;
	class IKeyFrame;
	class KeyFrameImpl;
	class AnimationTrackImpl
	{
	public:
		AnimationTrackImpl(IAnimation* parent, u16 handle);
		virtual ~AnimationTrackImpl(void);
		IKeyFrame*		CreateKeyFrame(f32 timePos);
		IKeyFrame*		GetKeyFrame(u16 index)const;
		void			RemoveKeyFrame(u16 index);
		void			RemoveAllKeyFrames(void);

		f32				GetKeyFramesAtTime(f32 timeIndex, IKeyFrame** keyFrame1, IKeyFrame** keyFrame2,
			u16* firstKeyIndex = 0) const;

		virtual IKeyFrame*		_CreateKeyFrameImpl(f32 timePos) = 0;
		virtual void			_KeyFreamDataChanged(void);

		virtual void			_Apply(f32 time, f32 weight = 1) = 0;
	public:
		IAnimation*	mParent;
		u16			mHandle;

		typedef std::vector<IKeyFrame*>	KeyFrameList;
		KeyFrameList	mKeyFrames;
	};

	class TransformKeyFrameImpl;
	class INode;
	class NodeAnimationTrackImpl:public AnimationTrackImpl
	{
	public:
		NodeAnimationTrackImpl(IAnimation* parent, u16 handle);
		virtual IKeyFrame*		_CreateKeyFrameImpl(f32 timePos);
		virtual void			_Apply(f32 time, f32 weight = 1);

		void					GetInterpolatedKeyFrame(f32 time, TransformKeyFrameImpl& frame);

	public:
		bool					mBlend;
		TransformKeyFrameImpl	mBlendFrame;
		TransformKeyFrameImpl	mCurFrame;
		INode*					mTargetNode;
	};
}

#endif // _ANIMATIONTRACKIMPL_201458162627_