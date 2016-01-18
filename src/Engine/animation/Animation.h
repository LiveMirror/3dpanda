//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 16:56:28_
// 描述:  
//

#ifndef _ANIMATION_201458165628_
#define _ANIMATION_201458165628_

#include "animation/IAnimation.h"
#include <map>

namespace panda
{
	class AnimationControl;
	class INodeAnimationTrack;

	class Animation:public IAnimation
	{
	public:
		Animation(const tstring& name, f32 len);
		virtual ~Animation(void);
		virtual	const tstring&			GetName(void)const;

		virtual void					SetLen(f32 len);
		virtual f32						GetLen(void)const;

		virtual INodeAnimationTrack*	CreateNodeTrack(u16 handle, INode* node);
		virtual void					CreateNodeTrack(u16 handle, INode* node, INodeAnimationTrack* track);
		virtual INodeAnimationTrack*	GetNodeTrack(u16 handle);

		void							Apply(f32 timePos, f32 weight);

	public:
		INodeAnimationTrack*			CreateNodeTrack(u16 handle);

	public:
		typedef std::map<u16, INodeAnimationTrack*>	NodeTrackList;
		NodeTrackList		mNodeTracks;
		tstring				mName;
		f32					mLen;
	};
}

#endif // _ANIMATION_201458165628_