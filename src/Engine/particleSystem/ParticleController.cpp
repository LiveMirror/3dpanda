#include "ParticleController.h"

namespace panda
{
	ParticleController::ParticleController( SceneMgrImpl* sceneMgr )
		:AniObject(sceneMgr),
		mCurTime(0),
		mLoop(false)
	{

	}

	void ParticleController::Update( f32 time )
	{
		if(!mLoop && mCurTime == mTotalTime)
		{
			SetEnabled(false);
		}
		mTick = time;
		mCurTime += time;
		if(mCurTime > mTotalTime)
		{
			if(mLoop)
			{
				mCurTime -= mTotalTime;
			}
			else
			{
				mTick = mTotalTime - mCurTime;
				mCurTime = mTotalTime;
			}
		}
	}

	f32 ParticleController::GetTick( void )
	{
		return mTick;
	}
}