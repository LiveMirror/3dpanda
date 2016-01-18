//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/26 16:35:12_
// 描述:  
//

#ifndef _RECTEFFECT_2014226163512_
#define _RECTEFFECT_2014226163512_

#include "Effect2D.h"
#include "base/Color.h"

namespace panda
{
	class RectEffect:public Effect2D
	{
	public:
		virtual bool	InitEffect(void);

		void			SetColor(const Color& c);
		void			SetColor2(const Color& c);
		void			SetSize(s32 width, s32 height);
		void			SetPos( s32 x, s32 y );
		void			SetVertical(bool vertical);
	public:
		D3DXHANDLE		mTech;
		D3DXHANDLE		mGradualTech;
		D3DXHANDLE		mColorHandle;
		D3DXHANDLE		mColorHandle2;
		D3DXHANDLE		mSizeHandle;
		D3DXHANDLE		mPosHandle;
		D3DXHANDLE		mVerticalHandle;
	};
}

#endif // _RECTEFFECT_2014226163512_