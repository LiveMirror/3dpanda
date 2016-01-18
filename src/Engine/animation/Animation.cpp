#include "Animation.h"
#include "animation/IAnimationTrack.h"
#include "AnimationTrackImpl.h"

namespace panda
{
	Animation::Animation( const tstring& name, f32 len )
		:mName(name),
		mLen(len)
	{

	}

	Animation::~Animation( void )
	{
		NodeTrackList::iterator itr = mNodeTracks.begin();
		while (itr != mNodeTracks.end())
		{
			delete itr->second;
			itr++;
		}
	}

	const tstring& Animation::GetName( void )const
	{
		return mName;
	}

	void Animation::SetLen( f32 len )
	{
		mLen = len;
	}

	f32 Animation::GetLen( void )const
	{
		return mLen;
	}

	INodeAnimationTrack* Animation::CreateNodeTrack( u16 handle, INode* node )
	{
		INodeAnimationTrack* pTrack = CreateNodeTrack(handle);
		pTrack->SetAssociatedNode(node);
		return pTrack;
	}

	INodeAnimationTrack* Animation::CreateNodeTrack( u16 handle )
	{
		if(NULL != GetNodeTrack(handle))
		{
			throw _T("Node track with the specified handle already exists");
		}
		NodeAnimationTrackImpl* pImpl = new NodeAnimationTrackImpl(this, handle);
		INodeAnimationTrack* pTrack = new INodeAnimationTrack(pImpl);
		mNodeTracks[handle] = pTrack;
		return pTrack;
	}

	void Animation::CreateNodeTrack( u16 handle, INode* node, INodeAnimationTrack* track )
	{
		INodeAnimationTrack* pTrack = CreateNodeTrack(handle);
		pTrack->SetAssociatedNode(node);
		NodeAnimationTrackImpl* pDst = (NodeAnimationTrackImpl*)pTrack->mImpl;
		NodeAnimationTrackImpl* pScr = (NodeAnimationTrackImpl*)track->mImpl;
		pDst->mKeyFrames = pScr->mKeyFrames;
	}

	INodeAnimationTrack* Animation::GetNodeTrack( u16 handle )
	{
		NodeTrackList::iterator i = mNodeTracks.find(handle);
		if(i == mNodeTracks.end())
		{
			return NULL;
		}
		return i->second;
	}

	void Animation::Apply( f32 timePos, f32 weight )
	{
		NodeTrackList::iterator itr = mNodeTracks.begin();
		while (itr != mNodeTracks.end())
		{
			itr->second->Apply(timePos, weight);
			itr++;
		}
	}
}