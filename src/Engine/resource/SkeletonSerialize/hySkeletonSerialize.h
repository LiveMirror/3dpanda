//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/8 17:29:56_
// ����:  
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
		// ��������
		virtual bool	ExportSkeleton(FileStream& file, ResSkeletonImpl* pSkn);

		// �������
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