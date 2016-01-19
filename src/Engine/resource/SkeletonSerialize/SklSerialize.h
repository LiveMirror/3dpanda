//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2013/8/23 9:34:59_
// ����:  
//

#ifndef _SKLSERIALIZE_201382393459_
#define _SKLSERIALIZE_201382393459_

#include <vector>
#include "Base/Matrix44.h"
#include "skeletonserialize.h"

namespace panda
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
		// �������
		virtual bool	ImportSkeleton(FileStream& file, ResSkeletonImpl* pSkn);


	private:
		void	readBone(FileStream& file);
		void	buildBones(ResSkeletonImpl* pSkn);


		void	ImportAnm(const tstring& path, ResSkeletonImpl* pSkn);

		void	_ImportAnm(const tchar* name, ResSkeletonImpl* pSkn);
		void	_readBoneAnm(FileStream& file, ResSkeletonImpl* pSkn, IAnimation* pAni, u32 frameNum);

	private:
		tstring	mFolderPath;
		std::vector<SklBone> mBones;
	};
}

#endif // _SKLSERIALIZE_201382393459_