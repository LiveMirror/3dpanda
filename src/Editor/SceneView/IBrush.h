//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/16 17:05:10_
// 描述:  
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

		//! 获得点x,y到原点ox,oy的影响值
		f32					GetEffect(f32 ox, f32 oy, f32 x, f32 y);
	public:
		tstring			mName;
		s32				mRadius;			// 半径
		s32				mInsideRadius;		// 内径
		f32				mValue;
	};
}

#endif // _IBRUSH_2014516170510_