////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-5-29 0:02:19
// ����:  ����Ⱦ����
////////////////////////////////////////////////////////

#ifndef	_Tian_201452900219_H_
#define	_Tian_201452900219_H_

#include "Renderable.h"

namespace panda
{
	class Pass;
	class RenderableSet:public Renderable
	{
	public:
		RenderableSet(void);

	public:
		virtual void				Render(RenderSystem* pRender, ICamera* pCamera);
		
		// ��Ⱦ����ģ��
		virtual void				RenderGeometry(RenderSystem* pRender)const;
		virtual void				RenderSets(RenderSystem* pRender, Pass* pass);
	};
}

#endif _Tian_201452900219_H_