//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/1 16:55:00_
// 描述:  
//

#ifndef _ISCENENODE_201441165500_
#define _ISCENENODE_201441165500_

#include "Base/Ray.h"
#include "INode.h"

namespace panda
{
	class ISceneObject;
	class ISceneMgr;
	class SceneNodeImpl;

	/*
	* 场景节点
	*/
	class ISceneNode:public INode
	{
	public:
		ISceneNode(SceneNodeImpl* pImpl);

		//! 附加场景对象
		virtual void				AttachObject(ISceneObject* object);
		virtual void				DisAttachObject(ISceneObject* object);

		virtual u32					GetNumObject(void);
		virtual ISceneObject*		GetObject(u32 index)const;

		//! 射线探测
		virtual bool				Probe(const Ray& ray, ProbeResult& result);

		virtual void				SetVisible(bool visible);
		virtual bool				GetVisible(void)const;

		//! 节点名称
		virtual void				SetName(const tchar* name);
		virtual const tchar*		GetName(void);

		virtual ISceneMgr*			GetSceneMgr(void)const;

		virtual void				Release(void);
	};
}

#endif // _ISCENENODE_201441165500_