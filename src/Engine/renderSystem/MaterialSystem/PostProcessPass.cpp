#include "PostProcessPass.h"
#include "RenderSystem/IRenderTarget.h"
#include "../../resource/TextureImpl.h"
#include "Effect.h"

namespace panda
{
	PostProcessPass::PostProcessPass( IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr)
		:Pass(d3dDevice, renderMgr),
		mScale(1.0f), mKernel(0), mUvScale(1.0f)
		,mVectorArr(NULL)
	{

	}

	PostProcessPass::~PostProcessPass()
	{
		if(NULL != mVectorArr)
		{
			delete[] mVectorArr;
		}
	}

	void PostProcessPass::SetParam( MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject )
	{
		// do nothing
	}

	void PostProcessPass::PPSetParam( Effect* effect )
	{
		IDirect3DTexture9* tex;

		tex = ((TextureImpl*)effect->GetBackSurface()->mImpl)->GetTexPtr();
		SetPsTex(mHandleDiffuseTex, tex);

		if(mHandleNormalTex)
		{
			tex = ((TextureImpl*)effect->mNormalMap->mImpl)->GetTexPtr();
			SetPsTex(mHandleNormalTex, tex);
		}

		if(mHandleColorTex)
		{
			tex = ((TextureImpl*)effect->mColorMap->mImpl)->GetTexPtr();
			SetPsTex(mHandleColorTex, tex);
		}

		// ÉèÖÃËõ·Å
		mVConstTable->SetFloat(mD3dDevice, mHandleScale, mScale);
		mVConstTable->SetFloat(mD3dDevice, mHandleUvScale, mUvScale);
		if(NULL != mHandlePixeKernel)
		{
			mPConstTable->SetVectorArray(mD3dDevice, mHandlePixeKernel, mVectorArr, mKernel);
		}
	}

	void PostProcessPass::GetPsHandles( void )
	{
		mHandleDiffuseTex = mPConstTable->GetConstantByName(0, "SamSrcSampler");
		mHandleNormalTex = mPConstTable->GetConstantByName(0, "SrcNormalSampler");
		mHandleColorTex = mPConstTable->GetConstantByName(0, "SrcColorSampler");

		mHandlePixeKernel = mPConstTable->GetConstantByName(0, "PixelKernel");
	}

	void PostProcessPass::GetVsHandles( void )
	{
		mHandleScale = mVConstTable->GetConstantByName(0, "mSacle");
		mHandleUvScale = mVConstTable->GetConstantByName(0, "mUvScale");
	}

	void PostProcessPass::Resize( s32 width, s32 height )
	{
		for(u32 i = 0; i < mKernel; i++)
		{
			mVectorArr[i].x = mvKernel[i].x / width;
			mVectorArr[i].y = mvKernel[i].y / height;
			mVectorArr[i].z = 0;
			mVectorArr[i].w = 1;
		}
		mPConstTable->SetVectorArray(mD3dDevice, mHandlePixeKernel, mVectorArr, mKernel);
	}

	void PostProcessPass::SetKernel( u32 count, Vector2Df* vArr)
	{
		mKernel = count;
		mVectorArr = new D3DXVECTOR4[count];
		mvKernel = vArr;
	}

	void PostProcessPass::SetScale( f32 scale )
	{
		mScale = scale;
	}

	void PostProcessPass::SetUVScale( f32 scale )
	{
		mUvScale = scale;
	}
}