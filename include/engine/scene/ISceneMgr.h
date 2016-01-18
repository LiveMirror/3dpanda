//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/1 16:54:24_
// 描述:  
//

#ifndef _ISCENEMGR_201441165424_
#define _ISCENEMGR_201441165424_

#include "Base/Config.h"
#include "base/Color.h"

namespace panda
{
	class ICamera;
	class ISceneNode;
	class SceneMgrImpl;
	class IMeshObject;
	class IParticleObject;

	class ISceneMgr
	{
	public:
		ISceneMgr(void);
		ISceneMgr(SceneMgrImpl* pImpl);
		virtual ~ISceneMgr(void);

		//! 获得根节点
		virtual ISceneNode*			GetRootNode(void);

		//! if the parent is null, it will attach to the rootNode
		virtual ISceneNode*			CreateNode(ISceneNode* pParent = NULL);

		//! 创建一个模型对象
		virtual IMeshObject*		CreateMeshObject(void);

		//! 创建一个粒子对象
		virtual IParticleObject*	CreateParticleObject(void);

		//-----------------------------------------
		//! 创建一个摄像机
		virtual ICamera*			CreateCamera(void);

		//! 环境光
		virtual void				SetAmbientLight(const Colorf& c);

		//! 释放资源
		virtual void				Release(void);
	public:
		SceneMgrImpl*		mImpl;
	};
}

#endif // _ISCENEMGR_201441165424_