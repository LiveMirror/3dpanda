//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/13 9:14:47_
// ����:  ����ʵ��
//

#ifndef _IANIMATIONENTITY_201451391447_
#define _IANIMATIONENTITY_201451391447_

#include "base/Config.h"

namespace panda
{
	class IAnimationEntity
	{
	public:
		virtual	const tstring&		GetName(void)const = 0;
		virtual f32					GetLen(void)const  = 0;

		// ����
		virtual void				SetTimePos(f32 time) = 0;
		virtual f32					GetTimePos(void)const = 0;
		virtual bool				AddTime(f32 time) = 0;

		virtual void				SetWeight(f32 weiht) = 0;
		virtual f32					GetWeight(void)const = 0;
	};
}

#endif // _IANIMATIONENTITY_201451391447_