#include "KeyFrameImpl.h"
#include "AnimationTrackImpl.h"

namespace panda
{
	KeyFrameImpl::KeyFrameImpl( AnimationTrackImpl* parent, f32 time )
		:mParentTrack(parent),
		mTime(time)
	{

	}

	KeyFrameImpl::~KeyFrameImpl(void)
	{

	}

	/*******************************************  TransformKeyFrameImpl  *****************************************************/
	TransformKeyFrameImpl::TransformKeyFrameImpl( AnimationTrackImpl* parent, f32 time )
		:KeyFrameImpl(parent, time)
	{
		mScale.x = 1;
		mScale.y = 1;
		mScale.z = 1;
	}

	TransformKeyFrameImpl::~TransformKeyFrameImpl( void )
	{

	}

	void TransformKeyFrameImpl::SetTranslate( const Vector3Df& trans )
	{
		mTranslate = trans;
		mParentTrack->_KeyFreamDataChanged();
	}

	void TransformKeyFrameImpl::SetScale( const Vector3Df& scale )
	{
		mScale = scale;
		mParentTrack->_KeyFreamDataChanged();
	}

	void TransformKeyFrameImpl::SetRotation( const Quaternion& rot )
	{
		mRotate = rot;
		mParentTrack->_KeyFreamDataChanged();
	}
}