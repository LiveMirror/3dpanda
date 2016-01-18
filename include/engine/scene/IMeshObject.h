//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 10:29:04_
// 描述:  
//

#ifndef _IMESHOBJECT_201443102904_
#define _IMESHOBJECT_201443102904_

#include "ISceneObject.h"
#include "resources/ResRefDefine.h"

namespace panda
{
	class IAnimationController;
	class MeshObjectImpl;
	class IMeshObject:public ISceneObject
	{
	public:
		IMeshObject(MeshObjectImpl* pImpl);

		//! 在调用此方法后,不能修改IResMesh的SubMesh的结构
		virtual void					BindResMesh(ResMesh mesh);
		virtual ResMesh					GetResMesh(void);

		//! 获得子集数量
		virtual u16						GetNumSubset(void)const;

		virtual void					SetMaterial(s16 nIndex, ResMaterial mat);
		virtual void					SetMaterial(ResMaterial mat);
		virtual ResMaterial				GetMaterial(u16 nIndex)const;

		virtual void					SetSubMeshVisible(u32 index, bool visible);

		virtual void					SetSkeletion(ResSkeletion skn);
		virtual ResSkeletion			GetSkeletion(void);

		virtual IAnimationController*	GetAnimationController(void);
	};
}

#endif // _IMESHOBJECT_201443102904_