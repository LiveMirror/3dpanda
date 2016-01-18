//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 11:25:43_
// ����:  
//

#ifndef _MESHSERIALIZE_201443112543_
#define _MESHSERIALIZE_201443112543_

#include "FileStream.h"

namespace panda
{
	class IResMesh;

	class MeshSerialize
	{
	public:
		// ����ģ��
		virtual bool	ExportMesh(FileStream& file, IResMesh* pMesh){ throw _T("Not implement the export of this format yet"); }

		// ����ģ��
		virtual bool	ImportMesh(FileStream& file, IResMesh* pMesh) = 0;
	};
}

#endif // _MESHSERIALIZE_201443112543_