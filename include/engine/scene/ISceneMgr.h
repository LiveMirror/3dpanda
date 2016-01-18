//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/1 16:54:24_
// ����:  
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

		//! ��ø��ڵ�
		virtual ISceneNode*			GetRootNode(void);

		//! if the parent is null, it will attach to the rootNode
		virtual ISceneNode*			CreateNode(ISceneNode* pParent = NULL);

		//! ����һ��ģ�Ͷ���
		virtual IMeshObject*		CreateMeshObject(void);

		//! ����һ�����Ӷ���
		virtual IParticleObject*	CreateParticleObject(void);

		//-----------------------------------------
		//! ����һ�������
		virtual ICamera*			CreateCamera(void);

		//! ������
		virtual void				SetAmbientLight(const Colorf& c);

		//! �ͷ���Դ
		virtual void				Release(void);
	public:
		SceneMgrImpl*		mImpl;
	};
}

#endif // _ISCENEMGR_201441165424_