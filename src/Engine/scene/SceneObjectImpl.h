//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 10:09:23_
// ����:  
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

		// ��ȷ����ײ���
		virtual bool	Intersects(const Ray& ray, ProbeResult& result, bool transformRay = true);

		// ����Ƿ����Χ���ཻ
		virtual bool	ProbeBindBox(const Ray& ray, bool transformRay = true);

	public:
		tstring			mName;
		bool			mEnableProbe;
		AABBOX			mBindBox;	// ��Χ��
		ISceneObject*	mThisPtr;
		ISceneMgr*		mCreator;	// ����������
		ISceneNode*		mParent;	// �ҽӵ��ĳ����ڵ�

		bool			mVisible;	// �����Ƿ�ɼ�
	};
}

#endif // _SCENEOBJECTIMPL_201443100923_