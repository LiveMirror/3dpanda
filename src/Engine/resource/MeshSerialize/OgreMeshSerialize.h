////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2012-10-23 23:31:21
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_20121023233121_H_
#define	_Tian_20121023233121_H_

#include <list>
#include <map>
#include "MeshSerialize.h"

namespace panda
{
	struct subMeshInfo
	{
		u16*		pIndexBuf;
		u32			indexCount;
		tstring		matrailName;
	};

	struct VertexBoneAssignment
	{
		u32 vertexIndex;
		u16 boneIndex;
		f32 weight;
	};

	class ResourceMgr;
	class ResMeshImpl;
	class VertexData;
	/*
	* ogre mesh格式模型解析器
	*/
	class OgreMeshSerialize:public MeshSerialize
	{
	public:
		typedef std::multimap<u32, VertexBoneAssignment> AssignmentList;
		
		// 导入模型
		virtual bool	ImportMesh(FileStream& file, IResMesh* pMesh);

		void			readMesh(FileStream& file, IResMesh* pMesh);
		void			readSubMesh(FileStream& file, ResMeshImpl* pImpl);
		void			readGeometry(FileStream& file, ResMeshImpl* pMesh, VertexData* dest);
		void			readGeometryVertexDeclaration(FileStream& file, VertexData* dest);
		void			readGeometryVertexBuffer(FileStream& file, ResMeshImpl* pMesh, VertexData* dest);
		void			readBoundsInfo(FileStream& file);
		void			readSubMeshNameTable(FileStream& file);
		void			readSkeletonLink(FileStream& file, ResMeshImpl* pMesh);

		void			readMeshBoneAssignment(FileStream& file, ResMeshImpl* pMesh);

		// read a chunk header
		u16				readChunk(FileStream& file);
		// 回跳一个Chunk文件头
		void			_turnBack(FileStream& file);

		// 根据读入的数据构造模型
		// 因为ogre的骨骼权重信息没有和顶点数据存储在一起
		void			_CompileMesh(IResMesh* pMesh);

		// 根据骨骼附加信息, 重新构建顶点数据
		void			_RebulidVertexData(VertexData* pData, AssignmentList* assigns);

		// 转换ogre的usage定义到dx
		s16				_ConvertUsage(s16 ogreUsage);
	protected:
		s32				mStreamLen;
	};
}

#endif _Tian_20121023233121_H_