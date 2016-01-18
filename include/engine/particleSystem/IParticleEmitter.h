//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/22 17:08:20_
// 描述:  粒子发射器
//

#ifndef _IPARTICLEEMITTER_2014522170820_
#define _IPARTICLEEMITTER_2014522170820_

#include "base/Struct.h"

namespace panda
{
	class IParticleTechnique;
	class ParticleEmitterImpl;
	class IParticleEmitter
	{
	public:
		IParticleEmitter(ParticleEmitterImpl* impl);
		virtual ParticleEmitterType::eValue		GetType(void)const;
		
		virtual void					SetName(const tstring& name);
		virtual const tstring&			GetName(void)const;

		/** The position of this emitter relative to the particle system center. */
		virtual void					SetPosition(const Vector3Df& pos);
		virtual const Vector3Df&		GetPosition(void) const;

		/** The base direction of the emitter. */
		virtual void					SetDirection(const Vector3Df& direction);
		virtual const Vector3Df&		GetDirection(void) const;

		virtual void					SetParticleMaxSize(const Vector3Df& size);
		virtual const Vector3Df&		GetParticleMaxSize(void) const;

		virtual void					SetParticleMinSize(const Vector3Df& size);
		virtual const Vector3Df&		GetParticleMinSize(void) const;

		virtual void					SetColorStart(const Colorf& c);
		virtual const Colorf&			GetColorStart(void) const;

		virtual void					SetColorEnd(const Colorf& c);
		virtual const Colorf&			GetColorEnd(void) const;

		virtual void					SetAngle(s32 angle);
		virtual s32						GetAngle(void) const;

		virtual void					SetMaxSpeed(f32 speed);
		virtual f32						GetMaxSpeed(void) const;

		virtual void					SetMinSpeed(f32 speed);
		virtual f32						GetMinSpeed(void) const;

		virtual void					SetStartTime(f32 v);
		virtual f32						GetStartTime(void) const;

		//! 发射器的持续时间 0是永远
		virtual void					SetDuration(f32 v);
		virtual f32						GetDuration(void) const;

		virtual void					SetLoop(bool loop);
		virtual bool					GetLoop(void)const;

		virtual void					SetMinNum(s32 num);
		virtual s32						GetMinNum(void)const;

		virtual void					SetMaxNum(s32 num);
		virtual s32						GetMaxNum(void)const;

		virtual void					SetRate(s32 num);
		virtual s32						GetRate(void)const;

		//! 粒子的生命周期 0是永远
		virtual void					SetTimeToLive(f32 v);
		virtual f32						GetTimeToLive(void) const;

		virtual IParticleTechnique*		GetParent(void)const;
	public:
		ParticleEmitterImpl*			mImpl;
	};
}

#endif // _IPARTICLEEMITTER_2014522170820_