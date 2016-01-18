#include "TerPass.h"
#include "resources/ITexture.h"
#include "../../resource/terrainmaterialimpl.h"
#include "../../scene/CameraImpl.h"
#include "../../resource/TextureImpl.h"

namespace panda
{
	TerPass::TerPass( IDirect3DDevice9* d3dDevice , RenderSystem* renderMgr)
		:Pass(d3dDevice, renderMgr)
	{

	}

	void TerPass::_GetPsHandles( void )
	{
		//mHandleDetailTex = mPConstTable->GetConstantByName(0, "DetailTexSampler");
		mHandleLightDir = mPConstTable->GetConstantByName(0, "mLightDir");
		mHandleTextureNum = mPConstTable->GetConstantByName(0, "mTextureNum");
		mHandlDifScale = mPConstTable->GetConstantByName(0, "mDiffuseScale");
		mHandleTex1 = mPConstTable->GetConstantByName(0, "Tex1Sampler");
		mHandleTex2 = mPConstTable->GetConstantByName(0, "Tex2Sampler");
		mHandleTex3 = mPConstTable->GetConstantByName(0, "Tex3Sampler");
		mHandleTex4 = mPConstTable->GetConstantByName(0, "Tex4Sampler");

		mHandleScale1 = mPConstTable->GetConstantByName(0, "mTexScale1");
		mHandleScale2 = mPConstTable->GetConstantByName(0, "mTexScale2");
		mHandleScale3 = mPConstTable->GetConstantByName(0, "mTexScale3");
		mHandleScale4 = mPConstTable->GetConstantByName(0, "mTexScale4");
	}

	void TerPass::_GetVsHandles( void )
	{
		mHandleEyePos = mVConstTable->GetConstantByName(0, "mEyePos");
	}

	void TerPass::_SetParam( MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject )
	{
		TerrainMaterialImpl* terMat = (TerrainMaterialImpl*)mat;
		/*if (!terMat->mDetailTex.IsNull())
		{
		IDirect3DTexture9* tex = ((TextureImpl*)terMat->mDetailTex->mImpl)->mTexPtr;
		SetPsTex(mHandleDetailTex, tex);
		}*/

		// ÉèÖÃÉãÏñ»úÎ»ÖÃ
		mVConstTable->SetFloatArray(mD3dDevice, mHandleEyePos, (f32*)&pCamera->mPosition, 3);
		mPConstTable->SetFloatArray(mD3dDevice, mHandleLightDir, (f32*)&terMat->mLightDir, 3);
		mPConstTable->SetInt(mD3dDevice, mHandleTextureNum, terMat->mTextures.size());
		mPConstTable->SetFloat(mD3dDevice, mHandlDifScale, terMat->mDiffuseScale);
		if(terMat->mTextures.size() > 0)
		{
			IDirect3DTexture9* tex = ((TextureImpl*)terMat->mTextures[0].img->mImpl)->GetTexPtr();
			SetPsTex(mHandleTex1, tex);
			mPConstTable->SetFloat(mD3dDevice, mHandleScale1, terMat->mTextures[0].scale);
		}
		if(terMat->mTextures.size() > 1)
		{
			IDirect3DTexture9* tex = ((TextureImpl*)terMat->mTextures[1].img->mImpl)->GetTexPtr();
			SetPsTex(mHandleTex2, tex);
			mPConstTable->SetFloat(mD3dDevice, mHandleScale2, terMat->mTextures[1].scale);
		}
		if(terMat->mTextures.size() > 2)
		{
			IDirect3DTexture9* tex = ((TextureImpl*)terMat->mTextures[2].img->mImpl)->GetTexPtr();
			SetPsTex(mHandleTex3, tex);
			mPConstTable->SetFloat(mD3dDevice, mHandleScale3, terMat->mTextures[2].scale);
		}
		if(terMat->mTextures.size() > 3)
		{
			IDirect3DTexture9* tex = ((TextureImpl*)terMat->mTextures[3].img->mImpl)->GetTexPtr();
			SetPsTex(mHandleTex4, tex);
			mPConstTable->SetFloat(mD3dDevice, mHandleScale4, terMat->mTextures[3].scale);
		}
	}
}