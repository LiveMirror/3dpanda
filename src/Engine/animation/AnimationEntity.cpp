#include "AnimationEntity.h"
#include "Animation.h"

namespace panda
{
	AnimationEntity::AnimationEntity( void )
		:mCurPos(0),
		mWeight(1)
	{

	}

	const tstring& AnimationEntity::GetName( void ) const
	{
		return mName;
	}

	f32 AnimationEntity::GetLen( void ) const
	{
		return mLen;
	}

	void AnimationEntity::SetTimePos( f32 time )
	{
		if(mCurPos == time)
		{
			return;
		}
		mCurPos = time;

		if(mCurPos > mLen)
		{
			mCurPos -= mLen;
			// notice ani end
		}
	}

	f32 AnimationEntity::GetTimePos( void ) const
	{
		return mCurPos;
	}

	bool AnimationEntity::AddTime( f32 time )
	{
		mFadeTime += time;
		if(mFadeTime < mBlendTime)
		{
			if(mFadeOut)
			{
				mWeight = 1 - mFadeTime / mBlendTime;
			}
			else
			{
				mWeight = mFadeTime / mBlendTime;
			}
		}
		else
		{
			mWeight = 1;
			if(mFadeOut)
			{
				return false;
			}
		}
		SetTimePos(mCurPos + time);
		return true;
	}

	void AnimationEntity::SetWeight( f32 weiht )
	{
		mWeight = weiht;
	}

	f32 AnimationEntity::GetWeight( void ) const
	{
		return mWeight;
	}

	void AnimationEntity::Apply( void )
	{
		mAni->Apply(mCurPos, mWeight);
	}
}
