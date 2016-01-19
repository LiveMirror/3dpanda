//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/8/23 9:34:59_
// 描述:  
//

#ifndef _SKLSERIALIZE_201382393459_
#define _SKLSERIALIZE_201382393459_

#include <vector>
#include "Base/Matrix44.h"
#include "skeletonserialize.h"

namespace shine
{
	class IAnimation;
	class SklSerialize:public SkeletonSerialize
	{
		struct SklBone
		{
			int			parent;
			tstring		name;
			f32			scale;
			Matrix44f	mat;
		};

	public:
		// 导入骨骼
		virtual bool	ImportSkeleton(CFileIO& file, ResSkeletonImpl* pSkn);


	private:
		void	readBone(CFileIO& file);
		void	buildBones(ResSkeletonImpl* pSkn);


		void	ImportAnm(const tstring& path, ResSkeletonImpl* pSkn);

		void	_ImportAnm(const tchar* name, ResSkeletonImpl* pSkn);
		void	_readBoneAnm(CFileIO& file, ResSkeletonImpl* pSkn, IAnimation* pAni, u32 frameNum);

	private:
		tstring	mFolderPath;
		std::vector<SklBone> mBones;
	};
}

#endif // _SKLSERIALIZE_201382393459_