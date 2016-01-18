#include "ParticleEmitterImpl.h"
#include "Particle.h"

namespace panda
{
	ParticleEmitterImpl::ParticleEmitterImpl( void )
		:mParent(NULL),
		mType(ParticleEmitterType::Point),
		mAngle(20),
		mMaxSpeed(50),
		mMinSpeed(30),
		mDuration(0),
		mRepeatDelay(0),
		mMinNum(-1),
		mMaxNum(-1),
		mCurNum(0),
		mRate(100),
		mTimeToLive(5),
		mYuTime(0)
	{
		mDirection.y = 1;
		mMaxSize.x = 10;
		mMaxSize.y = 10;
		mMaxSize.z = 10;

		mMinSize = Vector3Df(1, 1, 1);
	}

	void ParticleEmitterImpl::Emit( ParticleList& pattilces, f32 time)
	{
		s32 count = mRate * (time + mYuTime);
		f32 passTime = (f32)count / mRate;
		mYuTime = time + mYuTime - passTime;
		for(s32 i = 0; i < count; i++)
		{
			Particle* p = new Particle;
			p->mCreater = mThis;

			// 方向
			f32 a = rand() % mAngle;
			p->mDirection = mDirection.RandomDeviant(3.14f * a / 180.0f);

			// 速度
			if(mMaxSpeed == mMinSpeed)
			{
				p->mSpeed = mMaxSpeed;
			}
			else
			{
				p->mSpeed = rand() % (s32)(mMaxSpeed - mMinSpeed) + mMinSpeed;
			}

			// 颜色
			if(mStartColor != mEndColor)
			{
				p->mColor.r = mStartColor.r + (0.01f * (rand() % 100) * (mEndColor.r - mStartColor.r));
				p->mColor.g = mStartColor.g + (0.01f * (rand() % 100) * (mEndColor.g - mStartColor.g));
				p->mColor.b = mStartColor.b + (0.01f * (rand() % 100) * (mEndColor.b - mStartColor.b));
				p->mColor.a = mStartColor.a + (0.01f * (rand() % 100) * (mEndColor.a - mStartColor.a));
			}
			else
			{
				p->mColor = mStartColor;
			}

			// 尺寸
			if(mMaxSize != mMinSize)
			{
				s32 r = rand() % (s32)(mMaxSize.x - mMinSize.x);
				p->mSize.x = mMinSize.x + r;
				p->mSize.y = mMinSize.y + r;
				p->mSize.z = mMinSize.z + r;
			}
			else
			{
				p->mSize = mMaxSize;
			}
			p->mPos = mPos;
			p->mTotalTimeToLive = mTimeToLive;
			pattilces.push_back(p);
			mCurNum++;
		}
	}

	void ParticleEmitterImpl::decNum( void )
	{
		mCurNum--;
	}
}