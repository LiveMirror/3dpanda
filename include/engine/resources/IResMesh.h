//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 10:54:31_
// 描述:  
//

#ifndef _IRESMESH_201443105431_
#define _IRESMESH_201443105431_

#include "Base/AABBOX.h"
#include "IResource.h"

namespace panda
{
	class ISubMesh
	{
	public:
		virtual	void						SetRenderOperation(RenderOperation::eValue op) = 0;
		virtual RenderOperation::eValue		GetRenderOperation(void)const = 0;
		virtual void						SetVertexCount(s32 count) = 0;
		virtual void						SetIndexCount(s32 count, bool is32Bit) = 0;

		//! 下面4个方法都必须在SetVertexCount后调用
		//! dataType:DeclareType
		//! usage:DeclareUsage
		virtual void						AddElement(s32 source, s32 offset, s8 dataType, s8 usage, s8 usageIndex) = 0;
		virtual void						CreateVertexBuffer(s32 sourceID, s32 vertexSize) = 0;
		virtual void*						LockVertexBuffer(s32 sourceID) = 0;
		virtual void						UnLockVertexBuffer(s32 sourceID) = 0;

		//! 下面的2个方法必须在SetIndexCount后调用
		virtual void*						LockIndexBuffer(void) = 0;
		virtual void						UnLockIndexBuffer(void) = 0;
	};

	class ResMeshImpl;
	class IResMesh:public IResource
	{
	public:
		IResMesh(ResMeshImpl* pImpl);

		//! 获得包围盒
		virtual const AABBOX&	GetAABBOX()const;

		//! 更新包围盒
		virtual	void			UpdateAABB(void);

		//! 更新模型法线
		virtual void			UpdateNormals(void);

		//! 获得顶点个数
		virtual s32				GetVertexNum(void) const;

		//! 获得三角形个数
		virtual s32				GetTriangleNum(void) const;

		//! 获得子集个数
		virtual u32				GetSubSetNum(void) const;

		//! 获得子模型
		virtual ISubMesh*		GetSubMesh(u32 index) const;

		//! 创建子模型
		virtual ISubMesh*		CreateSubMesh(void);
	};
}

#endif // _IRESMESH_201443105431_