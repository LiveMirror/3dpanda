//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/13 9:18:57_
// ����:  
//

#ifndef _ANIMATIONENTITY_201451391857_
#define _ANIMATIONENTITY_201451391857_

#include "animation/IAnimationEntity.h"

namespace panda
{
	class Animation;
	class AnimationEntity:public IAnimationEntity
	{
	public:
		AnimationEntity(void);

		virtual	const tstring&		GetName(void)const;
		virtual f32					GetLen(void)const;

		// ����
		virtual void				SetTimePos(f32 time);
		virtual f32					GetTimePos(void)const;
		virtual bool				AddTime(f32 time);

		virtual void				SetWeight(f32 weiht);
		virtual f32					GetWeight(void)const;

	public:
		void				Apply(void);

	public:
		tstring				mName;
		f32					mLen;
		f32					mCurPos;
		f32					mWeight;
		f32					mBlendTime;		// �ں���ʱ��
		bool				mFadeOut;		// ��������
		f32					mFadeTime;		// �ںϵ�ǰʱ��
		Animation*			mAni;
	};
}

#endif // _ANIMATIONENTITY_201451391857_