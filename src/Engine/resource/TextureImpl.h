//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/28 11:04:02_
// 描述:  
//

#ifndef _TEXTUREIMPL_2014228110402_
#define _TEXTUREIMPL_2014228110402_

#include "ResourceImpl.h"
#include <d3dx9.h>

namespace panda
{
	class TextureImpl:public ResourceImpl
	{
	public:
		TextureImpl(ResourceMgr* resMgr);
		virtual ~TextureImpl(void);
		virtual bool	_Load(void);
		virtual void	_UnLoad(void);
		virtual void	_Save(const tchar* path);

		virtual	IDirect3DTexture9*		GetTexPtr(void);
	public:
		s32						mTexWidth;
		s32						mTexHeight;
	protected:
		IDirect3DTexture9*		mTexPtr;
	};
}

#endif // _TEXTUREIMPL_2014228110402_