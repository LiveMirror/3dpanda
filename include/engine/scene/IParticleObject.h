////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-27 22:03:14
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014527220314_H_
#define	_Tian_2014527220314_H_

#include "ISceneObject.h"
#include "resources/ResRefDefine.h"

namespace panda
{
	class ParticleObjectImpl;
	class IParticleObject:public ISceneObject
	{
	public:
		IParticleObject(ParticleObjectImpl* impl);

		//! 
		virtual void					SetResParticl(ResParticleSys particle);
		virtual ResParticleSys			GetResParticl(void);

		virtual void					Play(void);
		virtual void					Stop(void);
		virtual bool					IsPlay(void);
	};
}

#endif _Tian_2014527220314_H_