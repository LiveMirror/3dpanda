//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/2/28 10:50:13_
// ����:  
//

#ifndef _RESOURCEMGR_2014228105013_
#define _RESOURCEMGR_2014228105013_

#include <map>
#include "resources/IResMgr.h"
#include "config.h"
#include <d3dx9.h>

namespace panda
{
	class RenderSystem;
	class PassMgr;
	class ResourceMgr:public IResMgr
	{
	public:
		ResourceMgr(void);
		~ResourceMgr(void);

		//! ���ļ��м�������
		virtual ResTexture			LoadTexture(const tchar* strPath);

		//-----------------------------------------
		//! ���ļ��м���ģ��
		//! ��Դ�����������ݺ�׺���ж�ģ�͸�ʽ
		//! ֧�ֵĸ�ʽ��: mesh,3dm,3ds
		virtual ResMesh				LoadMesh(const tchar* strPath);

		//! ����һ��ģ��
		virtual ResMesh				CreateMesh(void);

		//! ��������
		virtual ResTerrain			CreateTerrain(s32 width, s32 height, f32 tileSize);
		virtual ResTerrain			LoadTerrian(const tchar* strPath);

		//! ���ļ��м��ع�������
		//! ��Դ�����������ݺ�׺���ж�ģ�͸�ʽ
		//! ֧�ֵĸ�ʽ��: skeleton
		virtual ResSkeletion		LoadSkeleton(const tchar* strPath);

		//! ����һ����ȾĿ��
		virtual IRenderTarget*		CreateRenderTarget(s32 width, s32 height);

		//! ����һ������
		virtual ResMaterial			CreateMaterial(MaterialType::eValue type = MaterialType::Type_StaticMesh);
		
		//! ���ļ��м��ز���
		virtual ResMaterial			LoadMaterial(const tchar* strPath);

		//! ����һ������ϵͳ
		virtual ResParticleSys		CreateParticleSys(void);
		virtual ResParticleSys		LoadParticleSys(const tchar* strPath);

		void						BindDevice(IDirect3DDevice9* device);
		IDirect3DDevice9*			GetDevice(void);

		//! ��ȡĬ�ϲ���
		ResMaterial					GetDefaultMat(void);

		void						_GetResName(tstring& name);
	public:
		IDirect3DDevice9*		mDevicePtr;
		typedef std::map<tstring, IResource*>	ResMap;
		ResMap					mResources;
		RenderSystem*			mRenderMgr;				// ��Ⱦ��
		s32						mResCreateCount;		// ������Դ����������
		ResMaterial				mDefaultMat;			// Ĭ�ϵĲ���
		PassMgr*				mPassMgr;
	};
}

#endif // _RESOURCEMGR_2014228105013_