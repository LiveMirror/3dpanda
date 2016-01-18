//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-6-2 23:13:49
// ����:  ���Ӳ��ſ�����
//

#ifndef	_Tian_201462231349_H_
#define	_Tian_201462231349_H_

#include "../animation/AniObject.h"

namespace panda
{
	/*
	*
	*/
	class ParticleController:public AniObject
	{
	public:
		ParticleController(SceneMgrImpl* sceneMgr);

		virtual void	Update(f32 time);

		f32				GetTick(void);
	public:
		f32			mTotalTime;
		f32			mCurTime;
		f32			mTick;
		bool		mLoop;
	};
}

#endif _Tian_201462231349_H_