//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 15:22:07_
// 描述:  
//

#ifndef _RENDERABLE_201443152207_
#define _RENDERABLE_201443152207_

#include "Base/AABBOX.h"
#include "Base/Matrix44.h"
#include "Resources/ResRefDefine.h"

namespace panda
{
	class ICamera;
	class RenderSystem;
	/*
	*! 可渲染的对象
	*/
	class Renderable
	{
	public:
		Renderable(void);

		//! 渲染
		virtual void				Render(RenderSystem* pRender, ICamera* pCamera);
		virtual ResMaterial			GetMaterial(void)const;
		virtual void				SetVisible(bool visible);
		virtual bool				GetVisible(void)const;


		virtual const Matrix44f&	GetWorldTransforms(void)const = 0;
		virtual AABBOX&				GetBoundBox(void)const = 0;

		// 渲染几何模型
		virtual void				RenderGeometry(RenderSystem* pRender)const = 0;

	public:
		bool			mVisible;
		ResMaterial		mMaterail;
	};
}

#endif // _RENDERABLE_201443152207_