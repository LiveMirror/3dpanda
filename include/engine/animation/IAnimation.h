//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 10:40:47_
// 描述:  动画
//

#ifndef _IANIMATION_201458104047_
#define _IANIMATION_201458104047_

#include "base/Config.h"

namespace panda
{
	class INode;
	class INodeAnimationTrack;
	class IAnimation
	{
	public:
		virtual ~IAnimation() {}
		virtual	const tstring&			GetName(void)const = 0;

		virtual void					SetLen(f32 len) = 0;
		virtual f32						GetLen(void)const = 0;

		virtual INodeAnimationTrack*	CreateNodeTrack(u16 handle, INode* node) = 0;
		virtual void					CreateNodeTrack(u16 handle, INode* node, INodeAnimationTrack* track) = 0;
		virtual INodeAnimationTrack*	GetNodeTrack(u16 handle) = 0;
	};
}

#endif // _IANIMATION_201458104047_