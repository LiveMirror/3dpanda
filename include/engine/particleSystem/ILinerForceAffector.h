//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-6-4 23:20:22
// ����:  
//

#ifndef	_Tian_201464232022_H_
#define	_Tian_201464232022_H_

#include "IParticleAffector.h"

namespace panda
{
	class LinerForceAffectorImpl;
	class ILinerForceAffector:public IParticleAffector
	{
	public:
		ILinerForceAffector(LinerForceAffectorImpl* impl);
	
		virtual void					SetForceVector(const Vector3Df& force);
		virtual const Vector3Df&		GetForceVector(void)const;
	};
}

#endif _Tian_201464232022_H_