//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/2/28 10:45:05_
// ����:  
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
		//! ��������С
		virtual s32		GetWidth(void)const;
		virtual s32		GetHeight(void)const;
	};
}

#endif // _ITEXTURE_2014228104505_