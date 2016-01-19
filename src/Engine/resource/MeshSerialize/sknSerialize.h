//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2012/11/16 14:27:08_
// 描述:  英雄联盟模型
//

#ifndef _SKNSERIALIZE_20121116142708_
#define _SKNSERIALIZE_20121116142708_

#include <vector>
#include "MeshSerialize.h"

namespace shine
{
	struct SubMeshInfo
	{
		char buffer[64];
		s32 index;
		s32 vPos;
		s32 vNum;
		s32 iPos;
		s32 iNum;
	};

	class ResMeshImpl;
	class sknSerialize:public MeshSerialize
	{
	public:
		// 导入模型
		virtual bool	ImportMesh(CFileIO& file, IResMesh* pMesh);

		void			ReadSubMeshInfo(CFileIO& file, ResMeshImpl* pMesh);

		bool			ReadIndex(CFileIO& file, s32 indexNum, ResMeshImpl* pMesh);
		bool			ReadVertex(CFileIO& file, s32 vertexNum, ResMeshImpl* pMesh);

	protected:
		typedef std::vector<SubMeshInfo>	SubMeshList;
		s16				mSubNum;
		SubMeshList		mSubMeshs;
	};
}

#endif // _SKNSERIALIZE_20121116142708_