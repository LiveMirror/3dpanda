//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/27 10:13:19_
// 描述:  
//

#ifndef _CIRCLEEFFECT_2014227101319_
#define _CIRCLEEFFECT_2014227101319_

#include "Effect2D.h"
#include "base/Color.h"

namespace panda
{
	class CircleEffect:public Effect2D
	{
	public:
		virtual bool	InitEffect(void);

		void			SetColor(const Color& c);
		void			SetRadius(f32 r);
		void			SetCenter(s32 x, s32 y );

	public:
		D3DXHANDLE		mFillTech;
		D3DXHANDLE		mDrawTech;
		D3DXHANDLE		mColorHandle;
		D3DXHANDLE		mCenterHandle;
		D3DXHANDLE		mRadiusHandle;
	};
}

#endif // _CIRCLEEFFECT_2014227101319_