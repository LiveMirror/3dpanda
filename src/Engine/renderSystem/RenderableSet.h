////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-29 0:02:19
// 描述:  可渲染集合
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
		
		// 渲染几何模型
		virtual void				RenderGeometry(RenderSystem* pRender)const;
		virtual void				RenderSets(RenderSystem* pRender, Pass* pass);
	};
}

#endif _Tian_201452900219_H_