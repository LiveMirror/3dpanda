//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/9 10:51:47_
// ����:  
//

#ifndef _ANIMATIONCONTROLLER_201459105147_
#define _ANIMATIONCONTROLLER_201459105147_

#include "animation/IAnimationController.h"
#include "AniObject.h"
#include <vector>
#include "resources/ResRefDefine.h"


namespace panda
{
	class AnimationEntity;
	class AnimationController:public IAnimationController, public AniObject
	{
	public:
		AnimationController(SceneMgrImpl* sceneMgr);
		
		virtual void				Update(f32 tick);

		// blendTime:�ں�ʱ��
		virtual void				Play(IAnimationEntity* pAni, f32 blendTime);

		// ���ö���������
		virtual void				Reset(void);

		// �ֶ�ģʽ
		virtual void				ManualAdd(IAnimationEntity* entity);
		virtual void				ManualRemove(IAnimationEntity* entity);

		virtual IAnimationEntity*	GetEntity(const tstring& name)const;
		virtual IAnimationEntity*	GetEntity(u32 index)const;
		virtual u32					GetEntityNum(void)const;

		// �Զ�����
		virtual void				SetAutoUpdate(bool automatic);
		virtual bool				GetAutoUpdate(void)const;


		void				InitWithSkn(ResSkeletion skn);
		// Ӧ�ö���
		void				Apply(void);
		void				Release(void);

	public:
		typedef std::vector<AnimationEntity*>		EntityList;
		EntityList			mEntitys;
		EntityList			mCurEntity;
		bool				mAutoUpdate;			// �Զ�����
		//typedef std::vector<IAnimation*>	AniList;
		//AniList				mAnis;
	};
}

#endif // _ANIMATIONCONTROLLER_201459105147_