//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 15:29:47_
// 描述:  
//

#ifndef _SUBMESHOBJECT_201443152947_
#define _SUBMESHOBJECT_201443152947_

#include "Base/Struct.h"
#include "Resources/ResRefdefine.h"
#include "../rendersystem/renderable.h"

namespace panda
{
	class MeshObjectImpl;
	class SubMesh;

	class SubMeshObject:public Renderable
	{
	public:
		SubMeshObject(MeshObjectImpl* parent);
		
		virtual const Matrix44f&	GetWorldTransforms(void)const;
		virtual AABBOX&				GetBoundBox(void)const;
		// 渲染几何模型
		virtual void				RenderGeometry(RenderSystem* pRender)const;

		s32							_RenderNum(RenderOperation::eValue op, s32 indexCount)const;

	public:		
		MeshObjectImpl*	mParent;
		SubMesh*		mSubMesh;
	};
}

#endif // _SUBMESHOBJECT_201443152947_