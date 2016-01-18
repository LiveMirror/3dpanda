#include "AnimationTrackImpl.h"
#include "animation/IKeyFrame.h"
#include "animation/IAnimation.h"
#include "scene/INode.h"

namespace panda
{
	/*******************************************       AnimationTrackImpl        *******************************************************/
	AnimationTrackImpl::AnimationTrackImpl( IAnimation* parent, u16 handle )
		:mParent(parent),
		mHandle(handle)
	{

	}

	AnimationTrackImpl::~AnimationTrackImpl()
	{
		KeyFrameList::iterator itr = mKeyFrames.begin();
		while (itr != mKeyFrames.end())
		{
			delete *itr;
			itr++;
		}
	}

	IKeyFrame* AnimationTrackImpl::CreateKeyFrame( f32 timePos )
	{
		IKeyFrame* keyFrame = _CreateKeyFrameImpl(timePos);
		KeyFrameList::iterator itr = mKeyFrames.begin();
		while (itr != mKeyFrames.end())
		{
			if ((*itr)->GetTime() < timePos)
			{
				itr++;
			}
			else
			{
				break;
			}
		}
		mKeyFrames.insert(itr, keyFrame);
		_KeyFreamDataChanged();
		return keyFrame;
	}

	void AnimationTrackImpl::_KeyFreamDataChanged( void )
	{

	}

	void AnimationTrackImpl::RemoveKeyFrame( u16 index )
	{
		if (index >= mKeyFrames.size())
		{
			return;
		}
		KeyFrameList::iterator i = mKeyFrames.begin();
		i += index;
		delete *i;
		mKeyFrames.erase(i);
		_KeyFreamDataChanged();
	}

	void AnimationTrackImpl::RemoveAllKeyFrames( void )
	{
		KeyFrameList::iterator i = mKeyFrames.begin();

		for (; i != mKeyFrames.end(); ++i)
		{
			delete *i;
		}
		mKeyFrames.clear();
		_KeyFreamDataChanged();
	}

	IKeyFrame* AnimationTrackImpl::GetKeyFrame( u16 index )const
	{
		if (index >= mKeyFrames.size())
		{
			return NULL;
		}
		return mKeyFrames[index];
	}

	f32 AnimationTrackImpl::GetKeyFramesAtTime( f32 timePos, IKeyFrame** keyFrame1, IKeyFrame** keyFrame2, u16* firstKeyIndex /*= 0*/ ) const
	{
		// Parametric time
		// t1 = time of previous keyframe
		// t2 = time of next keyframe
		f32 t1, t2;

		// Find first keyframe after or on current time
		// Wrap time
		f32 totalAnimationLength = mParent->GetLen();

		while (timePos > totalAnimationLength && totalAnimationLength > 0.0f)
		{
			timePos -= totalAnimationLength;
		}

		// No global keyframe index, need to search with local keyframes.
		KeyFrameList::const_iterator i = mKeyFrames.begin();
		while (i != mKeyFrames.end())
		{
			if((*i)->GetTime() >= timePos)
			{
				break;
			}
			else
			{
				i++;
			}
		}


		if (i == mKeyFrames.end())
		{
			// There is no keyframe after this time, wrap back to first
			*keyFrame2 = mKeyFrames.front();
			t2 = mParent->GetLen() + (*keyFrame2)->GetTime();

			// Use last keyframe as previous keyframe
			--i;
		}
		else
		{
			*keyFrame2 = *i;
			t2 = (*keyFrame2)->GetTime();

			// Find last keyframe before or on current time
			if (i != mKeyFrames.begin() && timePos < (*i)->GetTime())
			{
				--i;
			}
		}

		// Fill index of the first key
		if (firstKeyIndex)
		{
			*firstKeyIndex = static_cast<unsigned short>(std::distance(mKeyFrames.begin(), i));
		}

		*keyFrame1 = *i;

		t1 = (*keyFrame1)->GetTime();

		if (t1 == t2)
		{
			// Same KeyFrame (only one)
			return 0.0f;
		}
		else
		{
			return (timePos - t1) / (t2 - t1);
		}
	}

	/**********************************************       NodeAnimationTrackImpl       *****************************************************/
	NodeAnimationTrackImpl::NodeAnimationTrackImpl( IAnimation* parent, u16 handle )
		:AnimationTrackImpl(parent, handle),
		mTargetNode(NULL),mCurFrame(NULL, 0), mBlendFrame(NULL, 0),mBlend(false)
	{
		mCurFrame.mParentTrack = this;
	}

	IKeyFrame* NodeAnimationTrackImpl::_CreateKeyFrameImpl( f32 timePos )
	{
		TransformKeyFrameImpl* pImpl = new TransformKeyFrameImpl(this, timePos);
		ITransformKeyFrame* keyFrame = new ITransformKeyFrame(pImpl);
		return keyFrame;
	}

	void NodeAnimationTrackImpl::_Apply( f32 time, f32 weight/* = 1 */)
	{
		if (mKeyFrames.empty() || NULL == mTargetNode)
		{
			return;
		}
		//mTargetNode->ResetToInitialState();

		GetInterpolatedKeyFrame(time, mCurFrame);

		mTargetNode->Translate(mCurFrame.mTranslate * weight);

		Quaternion rotate;
		rotate.Slerp(Quaternion::IDENTITY, mCurFrame.mRotate, weight);
		mTargetNode->Rotate(rotate);
	}


	void NodeAnimationTrackImpl::GetInterpolatedKeyFrame( f32 timePos, TransformKeyFrameImpl& keyFrame)
	{
		keyFrame.mTime = timePos;
		ITransformKeyFrame *k1, *k2;

		u16 firstKeyIndex;
		f32 t = GetKeyFramesAtTime(timePos, (IKeyFrame**)&k1, (IKeyFrame**)&k2, &firstKeyIndex);

		ITransformKeyFrame temp(NULL);
		if(mBlend)
		{
			temp.mImpl = &mBlendFrame;
			k1 = &temp;
		}

		if (t == 0)
		{
			keyFrame.SetRotation(k1->GetRotation());
			keyFrame.SetScale(k1->GetScale());
			keyFrame.SetTranslate(k1->GetTranslate());
		}
		else
		{
			Vector3Df base = k1->GetTranslate();
			keyFrame.SetTranslate(base + (k2->GetTranslate() - base) * t);

			base = k1->GetScale();
			keyFrame.SetScale(base + (k2->GetScale() - base) * t);

			Quaternion r;
			r.Slerp(k1->GetRotation(), k2->GetRotation(), t);
			keyFrame.SetRotation(r);
		}
		temp.mImpl = NULL;
	}
}