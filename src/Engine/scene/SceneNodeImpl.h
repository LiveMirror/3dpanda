//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 9:44:20_
// 描述:  
//

#ifndef _SCENENODEIMPL_20144394420_
#define _SCENENODEIMPL_20144394420_

#include "Base/Ray.h"
#include "NodeImpl.h"

namespace panda
{
	class RenderQueue;
	class ISceneNode;
	class ISceneObject;
	class ISceneMgr;
	class ICamera;

	class SceneNodeImpl:public NodeImpl
	{
	public:
		typedef std::list<ISceneObject*>	ObjectList;
		SceneNodeImpl(ISceneMgr* pSceneMgr);
		virtual ~SceneNodeImpl(void);

		//! 创建子节点
		virtual INode*				CreateChild(void);

		void						AttachObject(ISceneObject* object);
		void						DisAttachObject(ISceneObject* object);
		//! 射线探测
		bool						Probe(const Ray& ray, ProbeResult& result);

		ISceneObject*				GetObject(u32 index)const;

		void						FindVisibleObjects(ICamera* pCamera, RenderQueue* pQueue, bool displayChild = true);
	protected:
		void						_ProbeWithBox(const Ray& ray, ObjectList& outList);
	public:
		tstring			mName;
		ISceneMgr*		mSceneMgr;		// creater
		ObjectList		mObjects;		// 挂接对象
		bool			mVisible;		// 节点是否可见
	};
}

#endif // _SCENENODEIMPL_20144394420_