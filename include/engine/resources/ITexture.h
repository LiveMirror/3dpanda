//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/28 10:45:05_
// 描述:  
//

#ifndef _ITEXTURE_2014228104505_
#define _ITEXTURE_2014228104505_

#include "IResource.h"

namespace panda
{
	class TextureImpl;
	class ITexture:public IResource
	{
	public:
		ITexture(TextureImpl* pImpl);
		virtual ~ITexture(void);

		//-----------------------------
		//! 获得纹理大小
		virtual s32		GetWidth(void)const;
		virtual s32		GetHeight(void)const;
	};
}

#endif // _ITEXTURE_2014228104505_