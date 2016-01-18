////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-26 22:11:19
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014526221119_H_
#define	_Tian_2014526221119_H_

#include "base/Struct.h"
#include "../TypeDef.h"
#include "config.h"


namespace panda
{
	class IParticleSys;
	class IParticleTechnique;
	class ParticleAffectorImpl
	{
	public:
		ParticleAffectorImpl(void);

		virtual void		AffectParticles(ParticleList& pattilces, f32 time);

	public:
		tstring					mName;
		IParticleTechnique*		mParent;
		ParticleAffectorType::eValue	mType;
	};
}

#endif _Tian_2014526221119_H_