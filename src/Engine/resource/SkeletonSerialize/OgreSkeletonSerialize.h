//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/8 17:35:27_
// ����:  
//

#ifndef _OGRESKELETONSERIALIZE_201458173527_
#define _OGRESKELETONSERIALIZE_201458173527_

#include "SkeletonSerialize.h"

namespace panda
{
	class Animation;
	class INodeAnimationTrack;
	class OgreSkeletonSerialize:public SkeletonSerialize
	{
	public:
		// �������
		virtual bool	ImportSkeleton(FileStream& file, ResSkeletonImpl* pSkn);

		void readFileHeader(FileStream& file);

		// Internal import methods
		void readBone(FileStream& file, ResSkeletonImpl* pSkn);
		void readBoneParent(FileStream& file, ResSkeletonImpl* pSkn);
		void readAnimation(FileStream& file, ResSkeletonImpl* pSkn);
		void readAnimationTrack(FileStream& file, Animation* pAni, ResSkeletonImpl* pSkn);
		void readKeyFrame(FileStream& file, INodeAnimationTrack* pTrack);
		void readKeyFrameEx(FileStream& file, INodeAnimationTrack* pTrack);		// �����˲�������ʽ
		void readSkeletonAnimationLink(FileStream& file);

		// read a chunk header
		u16				readChunk(FileStream& file);
		// ����һ��Chunk�ļ�ͷ
		void			rollBackChunk(FileStream& file);

	protected:
		s32				mStreamLen;
	};
}

#endif // _OGRESKELETONSERIALIZE_201458173527_