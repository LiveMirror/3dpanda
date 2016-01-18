//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/28 10:42:41_
// 描述:  
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
	* 资源管理器
	*/
	class IResMgr
	{
	public:
		//! 从文件中加载纹理
		virtual ResTexture			LoadTexture(const tchar* strPath) = 0;

		//! 从文件中加载模型
		//! 资源管理器将根据后缀名判断模型格式
		//! 支持的格式有: mesh,3dm,3ds
		virtual ResMesh				LoadMesh(const tchar* strPath) = 0;

		//! 创建一个模型
		virtual ResMesh				CreateMesh(void) = 0;

		//! 创建地形
		virtual ResTerrain			CreateTerrain(s32 width, s32 height, f32 tileSize) = 0;
		virtual ResTerrain			LoadTerrian(const tchar* strPath) = 0;

		//! 从文件中加载骨骼动画
		//! 资源管理器将根据后缀名判断模型格式
		//! 支持的格式有: skeleton
		virtual ResSkeletion		LoadSkeleton(const tchar* strPath) = 0;

		//! 创建一个粒子系统
		virtual ResParticleSys		CreateParticleSys(void) = 0;
		virtual ResParticleSys		LoadParticleSys(const tchar* strPath) = 0;

		//! 创建一个渲染目标
		virtual IRenderTarget*		CreateRenderTarget(s32 width, s32 height) = 0;

		//! 创建一个材质
		virtual ResMaterial			CreateMaterial(MaterialType::eValue type = MaterialType::Type_StaticMesh) = 0;

		//! 从文件中加载材质
		virtual ResMaterial			LoadMaterial(const tchar* strPath) = 0;
	};
}

#endif // _IRESMGR_2014228104241_