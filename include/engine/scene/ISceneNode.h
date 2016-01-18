//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/1 16:55:00_
// ����:  
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
	* �����ڵ�
	*/
	class ISceneNode:public INode
	{
	public:
		ISceneNode(SceneNodeImpl* pImpl);

		//! ���ӳ�������
		virtual void				AttachObject(ISceneObject* object);
		virtual void				DisAttachObject(ISceneObject* object);

		virtual u32					GetNumObject(void);
		virtual ISceneObject*		GetObject(u32 index)const;

		//! ����̽��
		virtual bool				Probe(const Ray& ray, ProbeResult& result);

		virtual void				SetVisible(bool visible);
		virtual bool				GetVisible(void)const;

		//! �ڵ�����
		virtual void				SetName(const tchar* name);
		virtual const tchar*		GetName(void);

		virtual ISceneMgr*			GetSceneMgr(void)const;

		virtual void				Release(void);
	};
}

#endif // _ISCENENODE_201441165500_