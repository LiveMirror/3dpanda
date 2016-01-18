//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 16:00:12_
// ����:  
//

#ifndef _RENDERTARGETIMPL_201443160012_
#define _RENDERTARGETIMPL_201443160012_

#include "../Resource/TextureImpl.h"

namespace panda
{
	class RenderTargetImpl:public TextureImpl
	{
	public:
		RenderTargetImpl(ResourceMgr* resMgr);
		virtual ~RenderTargetImpl(void);

		void		Resize(void);
		void		SetTexDirty(void);
		virtual	IDirect3DTexture9*		GetTexPtr(void);
		IDirect3DSurface9*				GetSurface(void);
		IDirect3DSurface9*				GetDepthSurface(void);
	public:
		s32					mSurfaceIndex;
		bool				mTexDirty;

	protected:
		IDirect3DSurface9*	mSurface;
		IDirect3DSurface9*	mDepthSurface;
		IDirect3DSurface9*	mTexSurface;
	};
}
#endif // _RENDERTARGETIMPL_201443160012_