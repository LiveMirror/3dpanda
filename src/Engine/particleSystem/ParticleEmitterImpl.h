//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/26 16:20:43_
// ����:  
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

		//! ��������
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
		f32						mMaxSpeed;		// ����ٶ�
		f32						mMinSpeed;		// ��С�ٶ�
		f32						mDuration;		// �������ĳ���ʱ�� 0����Զ
		f32						mRepeatDelay;	// �ظ���ʱ
		bool					mLoop;
		s32						mMinNum;		// ��С������
		s32						mMaxNum;		// ���������
		s32						mRate;			// ��������
		f32						mYuTime;
		s32						mCurNum;		// ��ǰ������������
		f32						mTimeToLive;	// ���ӵ���������
	};
}

#endif // _PARTICLEEMITTERIMPL_2014526162043_