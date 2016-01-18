#include "RenderTargetImpl.h"
#include "../Resource/ResourceMgr.h"
#include <d3d9.h>

namespace panda
{
	RenderTargetImpl::RenderTargetImpl( ResourceMgr* resMgr )
		:TextureImpl(resMgr),
		mSurfaceIndex(0),mTexDirty(true),mSurface(NULL)
	{

	}

	RenderTargetImpl::~RenderTargetImpl( void )
	{
		mSurface->Release();
	}

	void RenderTargetImpl::Resize( void )
	{
		if(NULL != mSurface && NULL != mTexPtr)
		{
			mSurface->Release();
			mTexPtr->Release();
		}

		// 要使用多重采样时需要CreateRenderTarget来生成Surface
		mTexPtr = NULL;

		mResMgr->mDevicePtr->CreateRenderTarget(mTexWidth,
			mTexHeight,
			D3DFMT_A16B16G16R16F,		// D3DFMT_A8R8G8B8
			D3DMULTISAMPLE_NONE,		// D3DMULTISAMPLE_NONE
			0,
			false,
			&mSurface,
			NULL);

		mResMgr->mDevicePtr->CreateDepthStencilSurface(mTexWidth, mTexHeight, 
			D3DFMT_D24X8,				// D3DFMT_D24X8
			D3DMULTISAMPLE_NONE,		// D3DMULTISAMPLE_4_SAMPLES,
			0,
			false, &mDepthSurface, NULL);

		mResMgr->mDevicePtr->CreateTexture(mTexWidth,
			mTexHeight,
			1,
			D3DUSAGE_RENDERTARGET,
			D3DFMT_A16B16G16R16F,
			D3DPOOL_DEFAULT,
			&mTexPtr,
			NULL);
		mTexPtr->GetSurfaceLevel(0, &mTexSurface);
	}

	void RenderTargetImpl::SetTexDirty( void )
	{
		mTexDirty = true;
	}

	IDirect3DTexture9* RenderTargetImpl::GetTexPtr( void )
	{
		if(mTexDirty)
		{
			mResMgr->mDevicePtr->StretchRect(mSurface, NULL, mTexSurface, NULL, D3DTEXF_POINT);
			mTexDirty = false;
		}
		return mTexPtr;
	}

	IDirect3DSurface9* RenderTargetImpl::GetSurface( void )
	{
		return mSurface;
	}

	IDirect3DSurface9* RenderTargetImpl::GetDepthSurface( void )
	{
		return mDepthSurface;
	}
}