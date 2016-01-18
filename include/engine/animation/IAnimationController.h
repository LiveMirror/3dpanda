//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/8 14:47:59_
// ����:  ����������
//

#ifndef _IANIMATIONCONTROLLER_201458144759_
#define _IANIMATIONCONTROLLER_201458144759_

#include "base/Config.h"

namespace panda
{
	class IAnimationEntity;
	class IAnimationController
	{
	public:
		// blendTime:�ں�ʱ��
		virtual void				Play(IAnimationEntity* pAni, f32 blendTime) = 0;

		// ���ö���������
		virtual void				Reset(void) = 0;

		// �ֶ�ģʽ
		virtual void				ManualAdd(IAnimationEntity* entity) = 0;
		virtual void				ManualRemove(IAnimationEntity* entity) = 0;

		// if you know the entity's index, please use index to get it. Because it faster than name
		virtual IAnimationEntity*	GetEntity(const tstring& name)const = 0;
		virtual IAnimationEntity*	GetEntity(u32 index)const = 0;
		virtual u32					GetEntityNum(void)const = 0;

		// �Զ�����
		virtual void				SetAutoUpdate(bool automatic) = 0;
		virtual bool				GetAutoUpdate(void)const = 0;
	};
}

#endif // _IANIMATIONCONTROLLER_201458144759_