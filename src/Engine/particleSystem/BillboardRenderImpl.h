////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-27 21:07:02
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014527210702_H_
#define	_Tian_2014527210702_H_

#include "ParticleRenderImpl.h"

namespace panda
{
	/*
	*
	*/
	class BillboardRenderImpl:public ParticleRenderImpl
	{
	public:
		BillboardRenderImpl(void);

		//! 渲染粒子
		virtual	void				RenderParticle(Particle* p, Graph3D* graph3D);
	};
}

#endif _Tian_2014527210702_H_