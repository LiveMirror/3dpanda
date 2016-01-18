//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/28 10:50:13_
// 描述:  
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

		//! 从文件中加载纹理
		virtual ResTexture			LoadTexture(const tchar* strPath);

		//-----------------------------------------
		//! 从文件中加载模型
		//! 资源管理器将根据后缀名判断模型格式
		//! 支持的格式有: mesh,3dm,3ds
		virtual ResMesh				LoadMesh(const tchar* strPath);

		//! 创建一个模型
		virtual ResMesh				CreateMesh(void);

		//! 创建地形
		virtual ResTerrain			CreateTerrain(s32 width, s32 height, f32 tileSize);
		virtual ResTerrain			LoadTerrian(const tchar* strPath);

		//! 从文件中加载骨骼动画
		//! 资源管理器将根据后缀名判断模型格式
		//! 支持的格式有: skeleton
		virtual ResSkeletion		LoadSkeleton(const tchar* strPath);

		//! 创建一个渲染目标
		virtual IRenderTarget*		CreateRenderTarget(s32 width, s32 height);

		//! 创建一个材质
		virtual ResMaterial			CreateMaterial(MaterialType::eValue type = MaterialType::Type_StaticMesh);
		
		//! 从文件中加载材质
		virtual ResMaterial			LoadMaterial(const tchar* strPath);

		//! 创建一个粒子系统
		virtual ResParticleSys		CreateParticleSys(void);
		virtual ResParticleSys		LoadParticleSys(const tchar* strPath);

		void						BindDevice(IDirect3DDevice9* device);
		IDirect3DDevice9*			GetDevice(void);

		//! 获取默认材质
		ResMaterial					GetDefaultMat(void);

		void						_GetResName(tstring& name);
	public:
		IDirect3DDevice9*		mDevicePtr;
		typedef std::map<tstring, IResource*>	ResMap;
		ResMap					mResources;
		RenderSystem*			mRenderMgr;				// 渲染器
		s32						mResCreateCount;		// 创建资源的名字自增
		ResMaterial				mDefaultMat;			// 默认的材质
		PassMgr*				mPassMgr;
	};
}

#endif // _RESOURCEMGR_2014228105013_