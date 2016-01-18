//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/1 16:52:36_
// ����:  
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
	* ��������
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

		//! ��ȡ����İ�Χ��
		virtual const AABBOX&		GetBindBox(void)const;

		//! �Ƿ����̽�⵽
		//! ֻӰ��˶����ڸ��ڵ��Probe, ��Ӱ��������Probe����
		virtual void				SetEnableProbe(bool enable);
		virtual bool				GetEnableProbe(void)const;

		virtual bool				Probe(const Ray& ray, ProbeResult& result);

		virtual void				Release(void);
	public:
		SceneObjectImpl*	mImpl;
	};
}

#endif // _ISCENEOBJECT_201441165236_