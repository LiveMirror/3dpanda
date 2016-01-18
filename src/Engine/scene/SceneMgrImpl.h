//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 10:25:50_
// 描述:  
//

#ifndef _SCENEMGRIMPL_201443102550_
#define _SCENEMGRIMPL_201443102550_

#include <list>
#include "Base/Config.h"
#include "Base/Color.h"

namespace panda
{
	class RenderQueue;
	class ISceneMgr;
	class ICamera;
	class ISceneNode;
	class IMeshObject;
	class AnimationState;
	class AniObject;
	class IPointLight;
	class IParticleObject;

	class SceneMgrImpl
	{
	public:
		SceneMgrImpl(ISceneMgr* pThis);
		~SceneMgrImpl(void);

		ISceneNode*			CreateNode( ISceneNode* pParent /*= NULL*/ );

		IMeshObject*		CreateMeshObject(void);

		IParticleObject*	CreateParticleObject(void);

		//-----------------------------------------
		//! 创建一个摄像机
		ICamera*			CreateCamera(void);

		//-----------------------------------------
		//! 查找所有可见的对象
		virtual void		FindVisibleObjects(ICamera* pCamera, RenderQueue* pQueue);

		//! 更新所有动画控制器
		void				UpdateAnimation(f32 time);

		//! 创建一个灯光
		IPointLight*		CreateLight(void);
		//! 从场景中移除一个光源
		void				RemoveLight(IPointLight* pLight);

	public:
		ISceneMgr*		mThisPtr;
		ISceneNode*		mRootNode;

		typedef std::list<AniObject*>	AniObjectList;
		AniObjectList	mAnimations;

		Colorf			mAmbientColor;	// 环境光颜色
		Colorf			mDirColor;		// 方向光颜色
		Colorf			mDirection;		// 光方向

		typedef std::list<IPointLight*>	LightList;
		LightList		mLights;		// 场景中的点光源
	};
}

#endif // _SCENEMGRIMPL_201443102550_