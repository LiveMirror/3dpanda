//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2012/11/5 17:05:44_
// 描述:  
//

#ifndef _HYMESHSERIALIZE_2012115170544_
#define _HYMESHSERIALIZE_2012115170544_

#include "MeshSerialize.h"

namespace panda
{
	class VertexData;
	class SubMesh;
	class ResMeshImpl;
	class hyMeshSerialize:public MeshSerialize
	{
	public:
		// 导出模型
		virtual bool	ExportMesh(FileStream& file, IResMesh* pMesh);

		// 导入模型
		virtual bool	ImportMesh(FileStream& file, IResMesh* pMesh);

	public:
		bool			WriteMesh(FileStream& file, IResMesh* pMesh);

		bool			WriteGeomety(FileStream& file, VertexData* pData);
		bool			WriteSubMesh(FileStream& file, SubMesh* pSubMesh);

		s32				CalcGeometySize(VertexData* pData);
		s32				CalcSubMeshSize(SubMesh* pSubMesh);

		bool			ReadHeader(FileStream& file);
		void			ReadGeomety(FileStream& file, ResMeshImpl* pMesh, VertexData* pData);
		void			ReadSubMesh(FileStream& file, ResMeshImpl* pMesh);

		void			ReadVertexData(FileStream& file, ResMeshImpl* pMesh, VertexData* dest);

		u16				mNumSubMesh;
		u8				mChuckID;
		s32				mChunkLen;
	};
}

#endif // _HYMESHSERIALIZE_2012115170544_