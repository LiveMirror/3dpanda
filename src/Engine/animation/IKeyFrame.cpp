#include "animation/IKeyFrame.h"
#include "KeyFrameImpl.h"

namespace panda
{
	/********************************************        IKeyFrame      **************************************************/
	IKeyFrame::IKeyFrame( KeyFrameImpl* pImpl )
		:mImpl(pImpl)
	{

	}

	IKeyFrame::~IKeyFrame( void )
	{
		if (NULL != mImpl)
		{
			delete mImpl;
		}
	}

	f32 IKeyFrame::GetTime( void )
	{
		return mImpl->mTime;
	}


	/********************************************        ITransformKeyFrame      **************************************************/
#define Ptr		((TransformKeyFrameImpl*)mImpl)

	ITransformKeyFrame::ITransformKeyFrame( TransformKeyFrameImpl* pImpl )
		:IKeyFrame(pImpl)
	{

	}

	void ITransformKeyFrame::SetTranslate( const Vector3Df& trans )
	{
		Ptr->SetTranslate(trans);
	}

	const Vector3Df& ITransformKeyFrame::GetTranslate( void ) const
	{
		return Ptr->mTranslate;
	}

	void ITransformKeyFrame::SetScale( const Vector3Df& scale )
	{
		Ptr->SetScale(scale);
	}

	const Vector3Df& ITransformKeyFrame::GetScale( void ) const
	{
		return Ptr->mScale;
	}

	void ITransformKeyFrame::SetRotation( const Quaternion& rot )
	{
		Ptr->SetRotation(rot);
	}

	const Quaternion& ITransformKeyFrame::GetRotation( void ) const
	{
		return Ptr->mRotate;
	}
}