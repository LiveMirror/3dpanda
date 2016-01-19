#include "SklSerialize.h"
#include "scene/IBone.h"
#include "../ResSkeletonImpl.h"
#include "../serializehelper.h"
#include "resources/ianimationtrack.h"
#include "resources/ianimation.h"
#include "resources/ikeyframe.h"

namespace shine
{
	bool SklSerialize::ImportSkeleton( CFileIO& file, ResSkeletonImpl* pSkn )
	{
		// 文件类型标识
		char head[8];
		file.Read(head, 8);
		if(head[0] != 'r' || head[1] != '3'
			|| head[2] != 'd' || head[3] != '2'
			|| head[4] != 's' || head[5] != 'k'
			|| head[6] != 'l' || head[7] != 't')
		{
			return false;
		}

		// Obj数量(不知道什么作用)
		s32 objNum;
		file.Read(objNum);

		// 意义不详(不知道什么作用)
		s32 num;
		file.Read(num);

		// 骨骼数量
		s32 boneNum;
		file.Read(boneNum);

		for(int i = 0; i < boneNum; i++)
		{
			readBone(file);
		}

		buildBones(pSkn);

		ImportAnm(file.GetPath(), pSkn);
		return true;
	}

	void SklSerialize::readBone( CFileIO& file)
	{
		SklBone bone;
		// 骨骼名称
		char name[32];
		file.Read(name, 32);
		tstring str = _T("");
		SerializeHelper::Narrow2wide(name, 32, str);
		bone.name = str;

		// 父节点
		file.Read(bone.parent);

		// 缩放
		file.Read(bone.scale);

		// 变换矩阵 3*4 最后一排0 0 0 1
		s32 index;
		Matrix44f mat;
		for(s32 col = 0; col < 3; col++)
		{
			for(s32 row = 0; row < 4; row++)
			{
				index = row * 4 + col;
				file.Read(bone.mat.m_value[index]);
			}
		}

		/*for(s32 row = 0; row < 4; row++)
		{
			for(s32 col = 0; col < 3; col++)
			{
				index = row * 4 + col;
				file.Read(bone.mat.m_value[index]);
			}
		}*/

		f32 s = 1 / bone.scale;
		//mat.Scaling(s, s, s);
		mBones.push_back(bone);
	}

	void SklSerialize::buildBones( ResSkeletonImpl* pSkn )
	{
		s32 num = mBones.size();
		for(s32 i = 0; i < num; i++)
		{
			SklBone& bone = mBones[i];
			IBone* pBone = pSkn->CreateBone(bone.name, i);
			Matrix44f mat = bone.mat;
			/*if(bone.parent >= 0)
			{
				IBone* parent = pSkn->GetBone(bone.parent);
				parent->AddChild(pBone);
				Matrix44f pMat = mBones[bone.parent].mat;
				pMat.Inverse();
				mat = mat * pMat;
				bone.mat = mat;
			}*/
			Vector3Df pos = mat.GetTransltion();
			Quaternion rot;
			rot = mat;
			pBone->SetPosition(pos);
			pBone->SetRotate(rot);
		}
	}

	void SklSerialize::ImportAnm( const tstring& path, ResSkeletonImpl* pSkn )
	{
		CFileIO::GetFileFolder(path, mFolderPath);

		_ImportAnm(_T("idle"), pSkn);
		_ImportAnm(_T("idle2"), pSkn);
	}

	void SklSerialize::_ImportAnm(const tchar* name, ResSkeletonImpl* pSkn )
	{
		CFileIO file;
		tstring path = mFolderPath + _T("/");
		path += name;
		path += _T(".anm");
		if(!file.Open(path.c_str()))
		{
			return;
		}

		// 文件类型标识
		char head[8];
		file.Read(head, 8);
		if(head[0] != 'r' || head[1] != '3'
			|| head[2] != 'd' || head[3] != '2'
			|| head[4] != 'a' || head[5] != 'n'
			|| head[6] != 'm' || head[7] != 'd')
		{
			return;
		}

		// 格式版本
		s32 ver;
		file.Read(ver);

		// 意义不详(不知道什么作用)
		s32 num;
		file.Read(num);

		// 骨骼数量
		u32 boneNum;
		file.Read(boneNum);

		// 动画帧数
		u32 frameNum;
		file.Read(frameNum);

		// 动画帧频
		u32 frameRate;
		file.Read(frameRate);
		
		f32 len = (f32)frameNum / frameRate;
		
		IAnimation* pAni = pSkn->CreateAnimation(name, len);

		for(u32 i = 0; i < boneNum; i++)
		{
			_readBoneAnm(file, pSkn, pAni, frameNum);
		}
	}

	void SklSerialize::_readBoneAnm( CFileIO& file, ResSkeletonImpl* pSkn, IAnimation* pAni, u32 frameNum )
	{
		char name[32];
		file.Read(name, 32);
		tstring str = _T("");
		SerializeHelper::Narrow2wide(name, 32, str);
		IBone* pBone = pSkn->GetBone(str);

		INodeAnimationTrack* track = pAni->CreateNodeTrack(pBone->GetHandle(), pBone);
		s32 type;
		file.Read(type);
		Quaternion rot;
		Vector3Df pos;

		f32 time;
		for(u32 i = 0; i < frameNum; i++)
		{
			time = (f32)i / 30;
			ITransformKeyFrame* keyFrame = (ITransformKeyFrame*)track->CreateKeyFrame(time);
			file.Read(rot);
			file.Read(pos);
			keyFrame->SetTranslate(pos);

			rot.Normalize();
			keyFrame->SetRotation(rot);
		}
	}
}