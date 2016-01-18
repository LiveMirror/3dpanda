//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 14:38:01_
// 描述:  动画轨迹
//

#ifndef _IANIMATIONTRACK_201458143801_
#define _IANIMATIONTRACK_201458143801_

#include "Base/Config.h"
#include "Base/Struct.h"

namespace panda
{
	class IAnimation;
	class IKeyFrame;
	class AnimationTrackImpl;
	class IAnimationTrack
	{
	public:
		IAnimationTrack(AnimationTrackImpl* pImpl);
		virtual ~IAnimationTrack(void);

		/** Get the handle associated with this track. */
		virtual u16			GetHandle(void) const;

		virtual u16			GetNumKeyFrames(void)const;

		virtual IKeyFrame*	GetKeyFrame(u16 index)const;

		virtual IKeyFrame*	CreateKeyFrame(f32 timePos);
		virtual void		RemoveKeyFrame(u16 index);
		virtual void		RemoveAllKeyFrames(void);

		virtual void		Apply(f32 time, f32 weight = 1);

		virtual f32			GetKeyFramesAtTime(f32 timePos, 
			IKeyFrame** keyFrame1, 
			IKeyFrame** keyFrame2,
			u16* firstKeyIndex = 0) const;

		virtual void		GetInterpolateKeyFrame(void);

		virtual IAnimation*	GetParent(void);

	public:
		AnimationTrackImpl*	mImpl;
	};

	class INode;
	class NodeAnimationTrackImpl;
	class INodeAnimationTrack:public IAnimationTrack
	{
	public:
		INodeAnimationTrack(NodeAnimationTrackImpl* pImpl);
		virtual void		SetAssociatedNode(INode* pNode);
	};
}

#endif // _IANIMATIONTRACK_201458143801_