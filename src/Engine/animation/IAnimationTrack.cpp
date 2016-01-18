#include "animation/IAnimationTrack.h"
#include "AnimationTrackImpl.h"

namespace panda
{
	IAnimationTrack::IAnimationTrack( AnimationTrackImpl* pImpl )
		:mImpl(pImpl)
	{

	}

	IAnimationTrack::~IAnimationTrack( void )
	{
		if (NULL != mImpl)
		{
			delete mImpl;
		}
	}

	u16 IAnimationTrack::GetHandle( void ) const
	{
		return mImpl->mHandle;
	}

	u16 IAnimationTrack::GetNumKeyFrames( void ) const
	{
		return mImpl->mKeyFrames.size();
	}

	IKeyFrame* IAnimationTrack::GetKeyFrame( u16 index ) const
	{
		return mImpl->GetKeyFrame(index);
	}

	IKeyFrame* IAnimationTrack::CreateKeyFrame( f32 timePos )
	{
		return mImpl->CreateKeyFrame(timePos);
	}

	void IAnimationTrack::RemoveKeyFrame( u16 index )
	{
		mImpl->RemoveKeyFrame(index);
	}

	void IAnimationTrack::RemoveAllKeyFrames( void )
	{
		mImpl->RemoveAllKeyFrames();
	}

	IAnimation* IAnimationTrack::GetParent( void )
	{
		return mImpl->mParent;
	}

	f32 IAnimationTrack::GetKeyFramesAtTime( f32 timePos, IKeyFrame** keyFrame1, IKeyFrame** keyFrame2, u16* firstKeyIndex /*= 0*/ ) const
	{
		return mImpl->GetKeyFramesAtTime(timePos, keyFrame1, keyFrame2, firstKeyIndex);
	}

	void IAnimationTrack::Apply( f32 time, f32 weight/* = 1*/)
	{
		mImpl->_Apply(time, weight);
	}

	void IAnimationTrack::GetInterpolateKeyFrame( void )
	{

	}

	/******************************************* INodeAnimationTrack ***************************************************/

#define Ptr		((NodeAnimationTrackImpl*)mImpl)

	INodeAnimationTrack::INodeAnimationTrack( NodeAnimationTrackImpl* pImpl )
		:IAnimationTrack(pImpl)
	{

	}

	void INodeAnimationTrack::SetAssociatedNode( INode* pNode )
	{
		Ptr->mTargetNode = pNode;
	}
}