//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/26 16:20:43_
// 描述:  
//

#ifndef _PARTICLEEMITTERIMPL_2014526162043_
#define _PARTICLEEMITTERIMPL_2014526162043_

#include "base/Struct.h"
#include "../TypeDef.h"

namespace panda
{
	class IParticleEmitter;
	class IParticleTechnique;
	class ParticleEmitterImpl
	{
	public:
		ParticleEmitterImpl(void);

		//! 发射粒子
		virtual void			Emit(ParticleList& pattilces, f32 time);
		void					decNum(void);

	public:
		ParticleEmitterType::eValue		mType;
		IParticleEmitter*		mThis;
		IParticleTechnique*		mParent;
		tstring					mName;
		Vector3Df				mPos;
		Vector3Df				mDirection;
		Vector3Df				mMaxSize;
		Vector3Df				mMinSize;
		Colorf					mStartColor;
		Colorf					mEndColor;
		f32						mStartTime;
		s32						mAngle;			// 0 - 180
		f32						mMaxSpeed;		// 最大速度
		f32						mMinSpeed;		// 最小速度
		f32						mDuration;		// 发射器的持续时间 0是永远
		f32						mRepeatDelay;	// 重复延时
		bool					mLoop;
		s32						mMinNum;		// 最小粒子数
		s32						mMaxNum;		// 最大粒子数
		s32						mRate;			// 发射速率
		f32						mYuTime;
		s32						mCurNum;		// 当前发射粒子数量
		f32						mTimeToLive;	// 粒子的生命周期
	};
}

#endif // _PARTICLEEMITTERIMPL_2014526162043_