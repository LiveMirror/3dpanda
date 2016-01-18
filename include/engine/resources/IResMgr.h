//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/2/28 10:42:41_
// ����:  
//

#ifndef _IRESMGR_2014228104241_
#define _IRESMGR_2014228104241_

#include "base/Config.h"
#include "ResRefDefine.h"
#include "Base/Struct.h"

namespace panda
{
	class IRenderTarget;
	/*
	* ��Դ������
	*/
	class IResMgr
	{
	public:
		//! ���ļ��м�������
		virtual ResTexture			LoadTexture(const tchar* strPath) = 0;

		//! ���ļ��м���ģ��
		//! ��Դ�����������ݺ�׺���ж�ģ�͸�ʽ
		//! ֧�ֵĸ�ʽ��: mesh,3dm,3ds
		virtual ResMesh				LoadMesh(const tchar* strPath) = 0;

		//! ����һ��ģ��
		virtual ResMesh				CreateMesh(void) = 0;

		//! ��������
		virtual ResTerrain			CreateTerrain(s32 width, s32 height, f32 tileSize) = 0;
		virtual ResTerrain			LoadTerrian(const tchar* strPath) = 0;

		//! ���ļ��м��ع�������
		//! ��Դ�����������ݺ�׺���ж�ģ�͸�ʽ
		//! ֧�ֵĸ�ʽ��: skeleton
		virtual ResSkeletion		LoadSkeleton(const tchar* strPath) = 0;

		//! ����һ������ϵͳ
		virtual ResParticleSys		CreateParticleSys(void) = 0;
		virtual ResParticleSys		LoadParticleSys(const tchar* strPath) = 0;

		//! ����һ����ȾĿ��
		virtual IRenderTarget*		CreateRenderTarget(s32 width, s32 height) = 0;

		//! ����һ������
		virtual ResMaterial			CreateMaterial(MaterialType::eValue type = MaterialType::Type_StaticMesh) = 0;

		//! ���ļ��м��ز���
		virtual ResMaterial			LoadMaterial(const tchar* strPath) = 0;
	};
}

#endif // _IRESMGR_2014228104241_