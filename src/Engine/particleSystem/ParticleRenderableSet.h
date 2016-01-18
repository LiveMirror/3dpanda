
//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-6-3 22:43:17
// 描述:  
//

#ifndef	_Tian_201463224317_H_
#define	_Tian_201463224317_H_

#include "../rendersystem/RenderableSet.h"
#include "../typedef.h"

namespace panda
{
	class IParticleRender;
	class ParticleObjectImpl;
	class ParticleRenderableSet:public RenderableSet
	{
	public:
		ParticleRenderableSet(ParticleList& particles);	

		virtual void				RenderSets(RenderSystem* pRender, Pass* pass);
		virtual const Matrix44f&	GetWorldTransforms(void)const;
		virtual AABBOX&				GetBoundBox(void)const;
	public:
		IParticleRender*	mRender;
		ParticleList&		mParticles;
		Matrix44f			mTransformMat;
		ParticleObjectImpl*	mParent;
	};
}

#endif _Tian_201463224317_H_