//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-6-4 23:26:22
// ����:  
//

#ifndef	_Tian_201464232622_H_
#define	_Tian_201464232622_H_

#include "ParticleAffectorImpl.h"

namespace panda
{
	class LinerForceAffectorImpl:public ParticleAffectorImpl
	{
	public:
		LinerForceAffectorImpl(void);

		virtual void		AffectParticles(ParticleList& pattilces, f32 time);
	public:
		Vector3Df			mForceVector;
	};
}

#endif _Tian_201464232622_H_