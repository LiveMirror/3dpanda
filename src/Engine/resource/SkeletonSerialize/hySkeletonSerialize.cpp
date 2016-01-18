#include "scene/IBone.h"
#include "animation/IAnimation.h"
#include "animation/IAnimationTrack.h"
#include "animation/IKeyFrame.h"

#include "../../resource/ResSkeletonImpl.h"
#include "../../animation/Animation.h"
#include "../../animation/AnimationTrackImpl.h"

#include "hySkeletonSerialize.h"

#define SKNANI_VER 0

namespace panda
{
	bool hySkeletonSerialize::ExportSkeleton( FileStream& file , ResSkeletonImpl* pSkn)
	{
		return WriteSkeleton(file, pSkn);
	}

	bool hySkeletonSerialize::ImportSkeleton( FileStream& file, ResSkeletonImpl* pSkn )
	{
		if (!ReadHead(file))
		{
			return false;
		}

		while (!file.Eof())
		{
			file.Read(mChuckID);
			file.Read(mChunkLen);

			switch(mChuckID)
			{
			case 1:
				{
					ReadBone(file, pSkn);
					break;
				}
			case 2:
				{
					ReadBoneRelation(file, pSkn);
					break;
				}
			case 3:
				{
					ReadAnimation(file, pSkn);
					break;
				}
			default:
				{
					file.Seek(mChunkLen - 5);
					break;
				}
			}
		}

		return true;
	}

	bool hySkeletonSerialize::WriteSkeleton( FileStream& file, ResSkeletonImpl* pSkn )
	{
		WriteHeader(file);

		ResSkeletonImpl::BoneList::iterator boneItr = pSkn->mBonesList.begin();
		while (boneItr != pSkn->mBonesList.end())
		{
			mChuckID = 1;
			file.Write(mChuckID);
			mChunkLen = CaleBoneSize(*boneItr);
			mChunkLen += 5;
			file.Write(mChunkLen);
			WriteBone(file, *boneItr);
			boneItr++;
		}

		boneItr = pSkn->mBonesList.begin();
		while (boneItr != pSkn->mBonesList.end())
		{
			if(NULL != (*boneItr)->GetParent())
			{
				mChuckID = 2;
				file.Write(mChuckID);
				mChunkLen = 9;
				file.Write(mChunkLen);
				WriteBoneRelation(file, *boneItr);
			}
			boneItr++;
		}

		ResSkeletonImpl::AnimationMap::iterator aniItr = pSkn->mAnimations.begin();
		while (aniItr != pSkn->mAnimations.end())
		{
			mChuckID = 3;
			file.Write(mChuckID);
			mChunkLen = CaleAniSize(aniItr->second);
			mChunkLen += 5;
			file.Write(mChunkLen);
			WriteAnimation(file, aniItr->second);
			aniItr++;
		}
		return true;
	}

	void hySkeletonSerialize::WriteHeader( FileStream& file )
	{
		char c = 'h';
		file.Write(c);
		c = 'y';
		file.Write(c);
		c = 's';
		file.Write(c);
		c = 'k';
		file.Write(c);

		s8 ver = SKNANI_VER;
		file.Write(ver);
	}

	void hySkeletonSerialize::WriteBone( FileStream& file, IBone* pBone )
	{
		pBone->ResetToInitialState();
		file.WriteStr(pBone->GetName());
		file.Write(pBone->GetHandle());
		file.Write(pBone->GetPosition());
		file.Write(pBone->GetRotate());
	}

	void hySkeletonSerialize::WriteBoneRelation( FileStream& file, IBone* pBone )
	{
		IBone* parent = (IBone*)pBone->GetParent();
		file.Write(pBone->GetHandle());
		file.Write(parent->GetHandle());
	}

	void hySkeletonSerialize::WriteAnimation( FileStream& file, IAnimation* pAni )
	{
		file.WriteStr(pAni->GetName());
		file.Write(pAni->GetLen());

		Animation* ani = (Animation*)pAni;
		u32 size = ani->mNodeTracks.size();
		file.Write(size);

		Animation::NodeTrackList::iterator itr = ani->mNodeTracks.begin();
		while (itr != ani->mNodeTracks.end())
		{
			_WriteTrack(file, itr->second);
			itr++;
		}
	}

	void hySkeletonSerialize::_WriteTrack( FileStream& file, INodeAnimationTrack* pTrack )
	{
		NodeAnimationTrackImpl* pImpl = (NodeAnimationTrackImpl*)pTrack->mImpl;
		file.Write(pImpl->mHandle);
		u16 size = pImpl->mKeyFrames.size();
		file.Write(size);
		AnimationTrackImpl::KeyFrameList::iterator itr = pImpl->mKeyFrames.begin();
		while (itr != pImpl->mKeyFrames.end())
		{
			ITransformKeyFrame* frame = (ITransformKeyFrame*)*itr;
			file.Write(frame->GetTime());
			file.Write(frame->GetTranslate());
			file.Write(frame->GetRotation());
			itr++;
		}
	}

	s32 hySkeletonSerialize::CaleBoneSize( IBone* pBone )
	{
		// name
		s32 size = 4;
		size += (pBone->GetName().size() + 1) * sizeof(tchar);

		size += 2;	// handle
		size += 12;	// position
		size += 16;	// rotaton

		return size;

	}

	s32 hySkeletonSerialize::CaleAniSize( IAnimation* pAni )
	{
		// name
		s32 size = 4;
		size += (pAni->GetName().size() + 1) * sizeof(tchar);
		size += 4;	// len
		size += 4;	// num of track

		Animation* ani = (Animation*)pAni;
		Animation::NodeTrackList::iterator itr = ani->mNodeTracks.begin();
		while (itr != ani->mNodeTracks.end())
		{
			size += CaleAnimationTrack(itr->second);
			itr++;
		}
		return size;
	}

	s32 hySkeletonSerialize::CaleAnimationTrack( INodeAnimationTrack* pTrack )
	{
		s32 size = 2;	// handle
		size += 2;		// num of keyframe
		NodeAnimationTrackImpl* pImpl = (NodeAnimationTrackImpl*)pTrack->mImpl;
		AnimationTrackImpl::KeyFrameList::iterator itr = pImpl->mKeyFrames.begin();
		while (itr != pImpl->mKeyFrames.end())
		{
			size += 4;	// time
			size += 12; // position
			size += 16; // rotation
			itr++;
		}

		return size;
	}

	bool hySkeletonSerialize::ReadHead( FileStream& file )
	{
		char c[4];
		file.Read(c[0]);
		file.Read(c[1]);
		file.Read(c[2]);
		file.Read(c[3]);
		if (c[0] != 'h' ||
			c[1] != 'y' ||
			c[2] != 's' ||
			c[3] != 'k')
		{
			return false;
		}
		s8 ver;
		file.Read(ver);
		if (ver != SKNANI_VER)
		{
			return false;
		}
		return true;
	}

	void hySkeletonSerialize::ReadBone( FileStream& file, ResSkeletonImpl* pSkn )
	{
		tstring boneName;
		file.ReadStr(boneName);
		u16 handle;
		file.Read(handle);

		IBone* pBone = pSkn->CreateBone(boneName, handle);

		Vector3Df pos;
		file.Read(pos);
		pBone->SetPosition(pos);

		Quaternion rot;
		file.Read(rot);
		//rot.W = -rot.W;

		//rot.Normalize();
		pBone->SetRotate(rot);
	}

	void hySkeletonSerialize::ReadBoneRelation( FileStream& file, ResSkeletonImpl* pSkn )
	{
		IBone* pBone;
		IBone* pParent;
		u16 childHandle, parentHandle;

		file.Read(childHandle);
		file.Read(parentHandle);
		pParent = pSkn->GetBone(parentHandle);
		pBone = pSkn->GetBone(childHandle);

		pParent->AddChild(pBone);
	}

	void hySkeletonSerialize::ReadAnimation( FileStream& file, ResSkeletonImpl* pSkn )
	{
		tstring name;
		file.ReadStr(name);
		f32 len;
		file.Read(len);

		Animation* pAni = (Animation*)pSkn->CreateAnimation(name, len);
		u32 num;
		file.Read(num);

		for (u32 i = 0; i < num; i++)
		{
			ReadAnimationTrack(file, pAni, pSkn);
		}
	}

	void hySkeletonSerialize::ReadAnimationTrack( FileStream& file, Animation* pAni, ResSkeletonImpl* pSkn )
	{
		u16 handle;
		u16 num;
		file.Read(handle);
		file.Read(num);

		// find bone
		IBone* pBone = pSkn->GetBone(handle);

		// create track
		INodeAnimationTrack* pTrack = pAni->CreateNodeTrack(handle, pBone);

		for (u16 i = 0; i < num; i++)
		{
			ReadKeyFrame(file, pTrack);
		}
	}

	void hySkeletonSerialize::ReadKeyFrame( FileStream& file, INodeAnimationTrack* pTrack )
	{
		f32 time;
		file.Read(time);

		ITransformKeyFrame* keyFrame = (ITransformKeyFrame*)pTrack->CreateKeyFrame(time);

		Vector3Df pos;
		file.Read(pos);
		keyFrame->SetTranslate(pos);

		Quaternion rot;
		file.Read(rot);
		//rot.W = -rot.W;

		//rot.Normalize();
		//if(pTrack->GetHandle() < 1)
		//{
		keyFrame->SetRotation(rot);
		//}
	}
}