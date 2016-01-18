//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 10:25:50_
// ����:  
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
		//! ����һ�������
		ICamera*			CreateCamera(void);

		//-----------------------------------------
		//! �������пɼ��Ķ���
		virtual void		FindVisibleObjects(ICamera* pCamera, RenderQueue* pQueue);

		//! �������ж���������
		void				UpdateAnimation(f32 time);

		//! ����һ���ƹ�
		IPointLight*		CreateLight(void);
		//! �ӳ������Ƴ�һ����Դ
		void				RemoveLight(IPointLight* pLight);

	public:
		ISceneMgr*		mThisPtr;
		ISceneNode*		mRootNode;

		typedef std::list<AniObject*>	AniObjectList;
		AniObjectList	mAnimations;

		Colorf			mAmbientColor;	// ��������ɫ
		Colorf			mDirColor;		// �������ɫ
		Colorf			mDirection;		// �ⷽ��

		typedef std::list<IPointLight*>	LightList;
		LightList		mLights;		// �����еĵ��Դ
	};
}

#endif // _SCENEMGRIMPL_201443102550_