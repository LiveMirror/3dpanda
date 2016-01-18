#include "ImageEffect.h"
#include "base/Vector2D.h"
#include "../../resource/TextureImpl.h"
#include "resources/ITexture.h"

namespace panda
{
	bool ImageEffect::InitEffect( void )
	{
		__super::InitEffect();
		mTech = mEffect->GetTechniqueByName("NormalImage");
		mColorTech = mEffect->GetTechniqueByName("ColorImage");
		mSizeHandle = mEffect->GetParameterByName("gSize", 0);
		mPosHandle = mEffect->GetParameterByName("gPos", 0);
		mTexHandle = mEffect->GetParameterByName("gTexture", 0);
		mColorHandle = mEffect->GetParameterByName("gColor", 0);
		return true;
	}

	void ImageEffect::SetSize( s32 width, s32 height )
	{
		Vector2Df s((f32)width, (f32)height);
		mEffect->SetValue(mSizeHandle, &s, sizeof(s));
	}

	void ImageEffect::SetPos( s32 x, s32 y )
	{
		Vector2Df s((f32)x, (f32)y);
		mEffect->SetValue(mPosHandle, &s, sizeof(s));
	}

	void ImageEffect::SetTex( ITexture* tex )
	{
		TextureImpl* impl = (TextureImpl*)tex->mImpl;
		mEffect->SetTexture(mTexHandle, impl->GetTexPtr());
	}

	void ImageEffect::SetColor( const Color& c )
	{
		D3DXCOLOR v((f32)c.R / 255.0f, (f32)c.G / 255.0f, (f32)c.B / 255.0f, (f32)c.A / 255.0f);
		mEffect->SetValue(mColorHandle, &v, sizeof(v));
	}
}