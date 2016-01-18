////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-27 22:05:24
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014527220524_H_
#define	_Tian_2014527220524_H_

#include "SceneObjectImpl.h"
#include "resources/ResRefDefine.h"
#include "../TypeDef.h"

namespace panda
{
	class ParticleRenderableSet;
	struct ParticleItem
	{
		ParticleList			particles;
		ParticleRenderableSet*	renderableSet;
	};

	class ParticleController;
	class ParticleObjectImpl:public SceneObjectImpl
	{
	public:
		ParticleObjectImpl(ISceneMgr* pCreator);

		virtual void			UpdateRenderQueue(ICamera* pCamera, RenderQueue* pQueue);
		void					SetResParticl(ResParticleSys particle);

		void					_UpdatePartic(void);
	public:
		typedef std::vector<ParticleItem>	ParticlePool;
		ParticlePool			mParticles;
		ResParticleSys			mRes;
		ParticleController*		mController;
	};
}

#endif _Tian_2014527220524_H_