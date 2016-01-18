//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 10:58:34_
// 描述:  
//

#ifndef _RESMESHIMPL_201443105834_
#define _RESMESHIMPL_201443105834_

#include "Base/AABBOX.h"
#include "ResourceImpl.h"
#include <vector>

namespace panda
{
	class MeshSerialize;
	class VertexData;
	class IndexData;
	class ISubMesh;
	class SubMesh;

	class ResMeshImpl:public ResourceImpl
	{
	public:
		ResMeshImpl(ResourceMgr* resMgr);
		virtual ~ResMeshImpl(void);

		virtual bool	_Load(void);
		virtual void	_UnLoad(void);
		virtual void	_Save(const tchar* path);

		// 获得包围盒
		const AABBOX&	GetAABBOX(void)const;

		// 更新包围盒
		void			UpdateAABB(void);

		// 更新模型法线
		virtual void	UpdateNormals(void);

		// 获得顶点个数
		s32				GetVectorNum(void) const;

		// 获得三角形个数
		s32				GetTriangleNum(void) const;

		// 获得子集个数
		u32				GetSubSetNum(void) const;

		ISubMesh*		GetSubMesh(u32 index) const;

		//! 创建子mesh
		SubMesh*		CreateSubMesh(void);

	public:
		//! 探测算法写到模型中，便于不同模型自己内部优化算法
		virtual bool	Probe(const Ray& ray, ProbeResult& result);

	protected:
		MeshSerialize*	_FindSerialize(const tstring& ext);
		void			_UpdateAABB(VertexData* buffer);

		//! 判断IndexData定义的模型数据是否与ray射线相交
		//! 射线必须是经过物体的坐标变化
		bool	_Intersects(const Ray& ray, VertexData* pData, IndexData* pIndex, ProbeResult& result);

	public:
		VertexData*		mVertexData;
		typedef std::vector<SubMesh*>		SubMeshList;
		SubMeshList		mSubMeshs;
		AABBOX			mAABBOX;		// 包围盒
	};
}

#endif // _RESMESHIMPL_201443105834_