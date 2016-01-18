//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 17:28:58_
// 描述:  
//

#ifndef _SKELETONSERIALIZE_201458172858_
#define _SKELETONSERIALIZE_201458172858_

#include "FileStream.h"

namespace panda
{
	class ResSkeletonImpl;
	/*
	* 骨骼序列化
	*/
	class SkeletonSerialize
	{
	public:
		// 导出骨骼
		virtual bool	ExportSkeleton(FileStream& file, ResSkeletonImpl* pSkn){ throw _T("Not implement the export of this format yet"); }

		// 导入骨骼
		virtual bool	ImportSkeleton(FileStream& file, ResSkeletonImpl* pSkn) = 0;
	};
}

#endif // _SKELETONSERIALIZE_201458172858_