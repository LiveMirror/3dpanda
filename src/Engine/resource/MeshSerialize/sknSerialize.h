//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2012/11/16 14:27:08_
// ����:  Ӣ������ģ��
//

#ifndef _SKNSERIALIZE_20121116142708_
#define _SKNSERIALIZE_20121116142708_

#include <vector>
#include "MeshSerialize.h"

namespace panda
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
		// ����ģ��
		virtual bool	ImportMesh(FileStream& file, IResMesh* pMesh);

		void			ReadSubMeshInfo(FileStream& file, ResMeshImpl* pMesh);

		bool			ReadIndex(FileStream& file, s32 indexNum, ResMeshImpl* pMesh);
		bool			ReadVertex(FileStream& file, s32 vertexNum, ResMeshImpl* pMesh);

	protected:
		typedef std::vector<SubMeshInfo>	SubMeshList;
		s16				mSubNum;
		SubMeshList		mSubMeshs;
	};
}

#endif // _SKNSERIALIZE_20121116142708_