////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-22 23:00:28
// 描述:  粒子影响器
////////////////////////////////////////////////////////

#ifndef	_Tian_2014522230028_H_
#define	_Tian_2014522230028_H_

#include "base/Struct.h"

namespace panda
{
	class IParticleTechnique;
	class ParticleAffectorImpl;
	class IParticleAffector
	{
	public:
		IParticleAffector(ParticleAffectorImpl* impl);

		virtual void					SetName(const tstring& name);
		virtual const tstring&			GetName(void)const;

		virtual ParticleAffectorType::eValue	GetType(void)const;

		virtual IParticleTechnique*		GetParent(void)const;
	public:
		ParticleAffectorImpl*			mImpl;
	};
}

#endif _Tian_2014522230028_H_