//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 10:09:23_
// 描述:  
//

#ifndef _SCENEOBJECTIMPL_201443100923_
#define _SCENEOBJECTIMPL_201443100923_

#include "Base/Config.h"
#include "Base/Ray.h"
#include "Base/AABBOX.h"
#include "Base/Struct.h"

namespace panda
{
	class ICamera;
	class RenderQueue;
	class ISceneObject;
	class ISceneNode;
	class ISceneMgr;

	class SceneObjectImpl
	{
	public:
		SceneObjectImpl(ISceneMgr* pCreator);
		virtual ~SceneObjectImpl(void);

		virtual void	SetVisible(bool visible);
		virtual void	UpdateRenderQueue(ICamera* pCamera, RenderQueue* pQueue);

		virtual bool	Probe(const Ray& ray, ProbeResult& result);

		// 精确的碰撞检测
		virtual bool	Intersects(const Ray& ray, ProbeResult& result, bool transformRay = true);

		// 检查是否与包围盒相交
		virtual bool	ProbeBindBox(const Ray& ray, bool transformRay = true);

	public:
		tstring			mName;
		bool			mEnableProbe;
		AABBOX			mBindBox;	// 包围盒
		ISceneObject*	mThisPtr;
		ISceneMgr*		mCreator;	// 场景管理器
		ISceneNode*		mParent;	// 挂接到的场景节点

		bool			mVisible;	// 对象是否可见
	};
}

#endif // _SCENEOBJECTIMPL_201443100923_