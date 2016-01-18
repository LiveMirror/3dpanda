//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/16 17:05:10_
// ����:  
//

#ifndef _IBRUSH_2014516170510_
#define _IBRUSH_2014516170510_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	class IBrush
	{
	public:
		IBrush(void);

		virtual	void		OnPaint(f32 x, f32 y) = 0;

		virtual void		SetValue(f32 v);
		void				SetRadius(s32 radius);
		virtual void		SetInsideRadius(s32 radius);

		s32					GetRadius(void)const;
		s32					GetInsideRadius(void)const;
		f32					GetValue(void);

		//! ��õ�x,y��ԭ��ox,oy��Ӱ��ֵ
		f32					GetEffect(f32 ox, f32 oy, f32 x, f32 y);
	public:
		tstring			mName;
		s32				mRadius;			// �뾶
		s32				mInsideRadius;		// �ھ�
		f32				mValue;
	};
}

#endif // _IBRUSH_2014516170510_