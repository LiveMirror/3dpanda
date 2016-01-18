//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 11:25:43_
// 描述:  
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
		// 导出模型
		virtual bool	ExportMesh(FileStream& file, IResMesh* pMesh){ throw _T("Not implement the export of this format yet"); }

		// 导入模型
		virtual bool	ImportMesh(FileStream& file, IResMesh* pMesh) = 0;
	};
}

#endif // _MESHSERIALIZE_201443112543_