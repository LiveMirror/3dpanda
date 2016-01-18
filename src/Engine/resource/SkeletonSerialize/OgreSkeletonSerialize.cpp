#include <winsock2.h>
#include "base/Quaternion.h"
#include "scene/IBone.h"
#include "animation/IKeyFrame.h"
#include "animation/IAnimationTrack.h"

#include "base/Vector3D.h"
#include "../../resource/ResSkeletonImpl.h"
#include "../../animation/Animation.h"
#include "../MeshSerialize/SerializeHelper.h"

#include "OgreSkeletonSerialize.h"


namespace panda
{
	enum SkeletonChunkID {
		SKELETON_HEADER            = 0x1000,
		// char* version           : Version number check
		SKELETON_BONE              = 0x2000,
		// Repeating section defining each bone in the system. 
		// Bones are assigned indexes automatically based on their order of declaration
		// starting with 0.

		// char* name                       : name of the bone
		// unsigned short handle            : handle of the bone, should be contiguous & start at 0
		// Vector3 position                 : position of this bone relative to parent 
		// Quaternion orientation           : orientation of this bone relative to parent 
		// Vector3 scale                    : scale of this bone relative to parent 

		SKELETON_BONE_PARENT       = 0x3000,
		// Record of the parent of a single bone, used to build the node tree
		// Repeating section, listed in Bone Index order, one per Bone

		// unsigned short handle             : child bone
		// unsigned short parentHandle   : parent bone

		SKELETON_ANIMATION         = 0x4000,
		// A single animation for this skeleton

		// char* name                       : Name of the animation
		// float length                      : Length of the animation in seconds

		SKELETON_ANIMATION_TRACK = 0x4100,
		// A single animation track (relates to a single bone)
		// Repeating section (within SKELETON_ANIMATION)

		// unsigned short boneIndex     : Index of bone to apply to

		SKELETON_ANIMATION_TRACK_KEYFRAME = 0x4110,
		// A single keyframe within the track
		// Repeating section

		// float time                    : The time position (seconds)
		// Quaternion rotate            : Rotation to apply at this keyframe
		// Vector3 translate            : Translation to apply at this keyframe
		// Vector3 scale                : Scale to apply at this keyframe

		SKELETON_ANIMATION_TRACK_KEYFRAME_OPTIMIZE  = 0x4120,	// 天龙八部数据格式

		SKELETON_ANIMATION_LINK         = 0x5000
		// Link to another skeleton, to re-use its animations

		// char* skeletonName					: name of skeleton to get animations from
		// float scale							: scale to apply to trans/scale keys

	};
	bool OgreSkeletonSerialize::ImportSkeleton( FileStream& file, ResSkeletonImpl* pSkn)
	{
		readFileHeader(file);

		u16 streamID;
		while (!file.Eof())
		{
			streamID = readChunk(file);
			switch(streamID)
			{
			case SKELETON_BONE:
				{
					readBone(file, pSkn);
					break;
				}
			case SKELETON_BONE_PARENT:
				{
					readBoneParent(file, pSkn);
					break;
				}
			case SKELETON_ANIMATION:
				{
					readAnimation(file, pSkn);
					break;
				}
			case SKELETON_ANIMATION_LINK:
				{
					readSkeletonAnimationLink(file);
					break;
				}
			}
		}
		pSkn->SetBindingPose();
		return true;
	}

	const u16 HEADER_STREAM_ID = 0x1000;
	void OgreSkeletonSerialize::readFileHeader( FileStream& file )
	{
		u16 headerID;
		file.Read(headerID);

		if (headerID == HEADER_STREAM_ID)
		{
			tstring ver;
			SerializeHelper::ReadString(file, ver);
		}
		else
		{
			throw _T("Invalid ogre skeleton file: not header");
		}
	}

	u16 OgreSkeletonSerialize::readChunk( FileStream& file )
	{
		u16 id;
		file.Read(id);
		file.Read(mStreamLen);
		return id;
	}

	void OgreSkeletonSerialize::rollBackChunk( FileStream& file )
	{
		file.Seek(-6);
	}

	void OgreSkeletonSerialize::readBone( FileStream& file, ResSkeletonImpl* pSkn)
	{
		tstring boneName;
		SerializeHelper::ReadString(file, boneName);

		// unsigned short handle            : handle of the bone, should be contiguous & start at 0
		u16 handle;
		file.Read(handle);

		if(boneName.empty())
		{
			tchar buf[20];
			_stprintf_s(buf, 20, _T("bone%d"), handle);
			boneName = buf;
		}

		IBone* pBone = pSkn->CreateBone(boneName, handle);

		Vector3Df pos;
		file.Read(pos);
		pBone->SetPosition(pos);

		Quaternion q;
		file.Read(q);
		q.X = -q.X;
		q.Y = -q.Y;
		q.Z = -q.Z;
		pBone->SetRotate(q);

		// Do we have scale?
		if (mStreamLen > 36)
		{
			Vector3Df scale;
			file.Read(scale);
			pBone->SetScale(scale);
		}
	}

	void OgreSkeletonSerialize::readBoneParent( FileStream& file, ResSkeletonImpl* pSkn)
	{
		IBone* pBone;
		IBone* pParent;
		u16 childHandle, parentHandle;

		file.Read(childHandle);
		file.Read(parentHandle);
		pParent = pSkn->GetBone(parentHandle);
		pBone = pSkn->GetBone(childHandle);
		if(NULL == pParent || NULL == pBone)
		{
			return;
		}
		pParent->AddChild(pBone);
	}

	void OgreSkeletonSerialize::readAnimation( FileStream& file, ResSkeletonImpl* pSkn)
	{
		tstring name;
		SerializeHelper::ReadString(file, name);
		f32 len;
		file.Read(len);

		Animation* pAni = (Animation*)pSkn->CreateAnimation(name, len);

		u16 streamID;
		while (!file.Eof())
		{
			streamID = readChunk(file);
			if (streamID == SKELETON_ANIMATION_TRACK)
			{
				readAnimationTrack(file, pAni, pSkn);
			}
			else
			{
				rollBackChunk(file);
				break;
			}
		}
	}

	void OgreSkeletonSerialize::readAnimationTrack( FileStream& file, Animation* pAni, ResSkeletonImpl* pSkn)
	{
		// unsigned short boneIndex     : Index of bone to apply to
		u16 boneHandle;
		file.Read(boneHandle);

		// find bone
		IBone* pBone = pSkn->GetBone(boneHandle);

		// create track
		INodeAnimationTrack* pTrack = pAni->CreateNodeTrack(boneHandle, pBone);

		u16 streamID;
		while (!file.Eof())
		{
			streamID = readChunk(file);
			if (streamID == SKELETON_ANIMATION_TRACK_KEYFRAME)
			{
				readKeyFrame(file, pTrack);
			}
			else if(streamID == SKELETON_ANIMATION_TRACK_KEYFRAME_OPTIMIZE)
			{
				readKeyFrameEx(file, pTrack);
			}
			else
			{
				rollBackChunk(file);
				break;
			}
		}
	}

	void OgreSkeletonSerialize::readKeyFrame( FileStream& file, INodeAnimationTrack* pTrack)
	{
		// float time                    : The time position (seconds)
		f32 time;
		file.Read(time);

		ITransformKeyFrame* keyFrame = (ITransformKeyFrame*)pTrack->CreateKeyFrame(time);

		// Quaternion rotate            : Rotation to apply at this keyframe
		Quaternion rot;
		file.Read(rot);
		rot.W = -rot.W;

		Vector3Df axis;
		//f32 angle;
		//rot.GetAngleAxis(axis, angle);

		//if(pTrack->GetHandle() != 0)
		//{
		//	rot = Quaternion::IDENTITY;
		//}
		keyFrame->SetRotation(rot);

		// Vector3 translate            : Translation to apply at this keyframe
		Vector3Df trans;
		file.Read(trans);
		keyFrame->SetTranslate(trans);

		// Do we have scale?
		if (mStreamLen > 38)
		{
			Vector3Df scale;
			file.Read(scale);
			keyFrame->SetScale(scale);
		}
	}

	void OgreSkeletonSerialize::readKeyFrameEx( FileStream& file, INodeAnimationTrack* pTrack )
	{
		u16 len;
		u16 flags;
		file.Read(len);
		file.Read(flags);
		f32 time;
		for (int i = 0; i < len; i++)
		{
			file.Read(time);

			ITransformKeyFrame* keyFrame = (ITransformKeyFrame*)pTrack->CreateKeyFrame(time);

			// Quaternion rotate            : Rotation to apply at this keyframe
			Quaternion rot = Quaternion::IDENTITY;;
			if(flags & 1)
			{
				file.Read(rot);
				rot.W = -rot.W;
			}
			keyFrame->SetRotation(rot);

			// Vector3 translate            : Translation to apply at this keyframe
			Vector3Df trans = Vector3Df::ZERO;
			if(flags & 2)
			{
				file.Read(trans);
			}
			keyFrame->SetTranslate(trans);

			// Do we have scale?
			if (flags & 4)
			{
				Vector3Df scale;
				file.Read(scale);
				keyFrame->SetScale(scale);
			}
		}
	}
	void OgreSkeletonSerialize::readSkeletonAnimationLink( FileStream& file )
	{

	}
}