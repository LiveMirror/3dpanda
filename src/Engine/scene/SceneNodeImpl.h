//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 9:44:20_
// ����:  
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

		//! �����ӽڵ�
		virtual INode*				CreateChild(void);

		void						AttachObject(ISceneObject* object);
		void						DisAttachObject(ISceneObject* object);
		//! ����̽��
		bool						Probe(const Ray& ray, ProbeResult& result);

		ISceneObject*				GetObject(u32 index)const;

		void						FindVisibleObjects(ICamera* pCamera, RenderQueue* pQueue, bool displayChild = true);
	protected:
		void						_ProbeWithBox(const Ray& ray, ObjectList& outList);
	public:
		tstring			mName;
		ISceneMgr*		mSceneMgr;		// creater
		ObjectList		mObjects;		// �ҽӶ���
		bool			mVisible;		// �ڵ��Ƿ�ɼ�
	};
}

#endif // _SCENENODEIMPL_20144394420_