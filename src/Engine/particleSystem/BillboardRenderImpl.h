////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-5-27 21:07:02
// ����:  
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

		//! ��Ⱦ����
		virtual	void				RenderParticle(Particle* p, Graph3D* graph3D);
	};
}

#endif _Tian_2014527210702_H_