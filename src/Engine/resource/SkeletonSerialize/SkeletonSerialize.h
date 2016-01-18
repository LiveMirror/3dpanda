//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/8 17:28:58_
// ����:  
//

#ifndef _SKELETONSERIALIZE_201458172858_
#define _SKELETONSERIALIZE_201458172858_

#include "FileStream.h"

namespace panda
{
	class ResSkeletonImpl;
	/*
	* �������л�
	*/
	class SkeletonSerialize
	{
	public:
		// ��������
		virtual bool	ExportSkeleton(FileStream& file, ResSkeletonImpl* pSkn){ throw _T("Not implement the export of this format yet"); }

		// �������
		virtual bool	ImportSkeleton(FileStream& file, ResSkeletonImpl* pSkn) = 0;
	};
}

#endif // _SKELETONSERIALIZE_201458172858_