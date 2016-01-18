//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/1 16:52:36_
// 描述:  
//

#ifndef _ISCENEOBJECT_201441165236_
#define _ISCENEOBJECT_201441165236_

#include "Base/Ray.h"
#include "Base/AABBOX.h"
#include "Base/Struct.h"

namespace panda
{
	class ISceneNode;
	class ISceneMgr;
	class SceneObjectImpl;

	/*
	* 场景对象
	*/
	class ISceneObject
	{
	public:
		ISceneObject(SceneObjectImpl* pImpl);
		virtual ~ISceneObject(void);

		virtual ISceneMgr*			GetSceneMgr(void)const;
		virtual ISceneNode*			GetParentNode(void)const;

		virtual void				SetName(const tchar* name);
		virtual const tchar*		GetName(void)const;

		virtual bool				GetVisible(void)const;
		virtual void				SetVisible(bool visible);

		//! 获取对象的包围盒
		virtual const AABBOX&		GetBindBox(void)const;

		//! 是否可以探测到
		//! 只影响此对象在父节点的Probe, 不影响对象本身的Probe方法
		virtual void				SetEnableProbe(bool enable);
		virtual bool				GetEnableProbe(void)const;

		virtual bool				Probe(const Ray& ray, ProbeResult& result);

		virtual void				Release(void);
	public:
		SceneObjectImpl*	mImpl;
	};
}

#endif // _ISCENEOBJECT_201441165236_