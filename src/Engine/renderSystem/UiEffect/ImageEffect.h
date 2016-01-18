//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/26 15:19:21_
// 描述:  
//

#ifndef _LINEEFFECT_2014226151921_
#define _LINEEFFECT_2014226151921_

#include "Effect2D.h"
#include "base/Color.h"

namespace panda
{
	class ITexture;
	class ImageEffect:public Effect2D
	{
	public:
		virtual bool	InitEffect(void);
		void			SetSize(s32 width, s32 height);
		void			SetPos( s32 x, s32 y );
		void			SetTex(ITexture* tex);
		void			SetColor(const Color& c);
	public:
		D3DXHANDLE		mTech;
		D3DXHANDLE		mColorTech;
		D3DXHANDLE		mSizeHandle;
		D3DXHANDLE		mPosHandle;
		D3DXHANDLE		mTexHandle;
		D3DXHANDLE		mColorHandle;
	};
}

#endif // _LINEEFFECT_2014226151921_