//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/8 17:29:56_
// 描述:  
//

#ifndef _HYSKELETONSERIALIZE_201458172956_
#define _HYSKELETONSERIALIZE_201458172956_

#include "SkeletonSerialize.h"

namespace panda
{
	class IBone;
	class IAnimation;
	class INodeAnimationTrack;
	class Animation;
	class hySkeletonSerialize:public SkeletonSerialize
	{
	public:
		// 导出骨骼
		virtual bool	ExportSkeleton(FileStream& file, ResSkeletonImpl* pSkn);

		// 导入骨骼
		virtual bool	ImportSkeleton(FileStream& file, ResSkeletonImpl* pSkn);

		bool			WriteSkeleton(FileStream& file, ResSkeletonImpl* pSkn);
		void			WriteHeader(FileStream& file);

		void			WriteBone(FileStream& file, IBone* pBone);
		void			WriteBoneRelation(FileStream& file, IBone* pBone);
		void			WriteAnimation(FileStream& file, IAnimation* pAni);

		bool			ReadHead(FileStream& file);
		void			ReadBone(FileStream& file, ResSkeletonImpl* pSkn);
		void			ReadBoneRelation(FileStream& file, ResSkeletonImpl* pSkn);
		void			ReadAnimation(FileStream& file, ResSkeletonImpl* pSkn);

		void			ReadAnimationTrack(FileStream& file, Animation* pAni, ResSkeletonImpl* pSkn);
		void			ReadKeyFrame(FileStream& file, INodeAnimationTrack* pTrack);

		s32				CaleBoneSize(IBone* pBone);
		s32				CaleAniSize(IAnimation* pAni);
		s32				CaleAnimationTrack(INodeAnimationTrack* pTrack);

		void			_WriteTrack(FileStream& file, INodeAnimationTrack* pTrack);

	public:
		u8				mChuckID;
		s32				mChunkLen;
	};
}

#endif // _HYSKELETONSERIALIZE_201458172956_