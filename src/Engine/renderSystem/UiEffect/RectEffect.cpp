#include "RectEffect.h"
#include "base/Vector2D.h"

namespace panda
{
	bool RectEffect::InitEffect( void )
	{
		__super::InitEffect();
		mTech = mEffect->GetTechniqueByName("FillRect");
		mGradualTech = mEffect->GetTechniqueByName("GradualFillRect");
		mColorHandle = mEffect->GetParameterByName("gRectColor", 0);
		mColorHandle2 = mEffect->GetParameterByName("gRectColor2", 0);
		mSizeHandle = mEffect->GetParameterByName("gSize", 0);
		mPosHandle = mEffect->GetParameterByName("gPos", 0);
		mVerticalHandle = mEffect->GetParameterByName("gVertical", 0);
		return true;
	}

	void RectEffect::SetColor( const Color& c )
	{
		D3DXCOLOR v((f32)c.R / 255.0f, (f32)c.G / 255.0f, (f32)c.B / 255.0f, (f32)c.A / 255.0f);
		mEffect->SetValue(mColorHandle, &v, sizeof(v));
	}

	void RectEffect::SetSize( s32 width, s32 height )
	{
		Vector2Df s((f32)width, (f32)height);
		mEffect->SetValue(mSizeHandle, &s, sizeof(s));
	}

	void RectEffect::SetPos( s32 x, s32 y )
	{
		Vector2Df s((f32)x, (f32)y);
		mEffect->SetValue(mPosHandle, &s, sizeof(s));
	}

	void RectEffect::SetColor2( const Color& c )
	{
		D3DXCOLOR v((f32)c.R / 255.0f, (f32)c.G / 255.0f, (f32)c.B / 255.0f, (f32)c.A / 255.0f);
		mEffect->SetValue(mColorHandle2, &v, sizeof(v));
	}

	void RectEffect::SetVertical( bool vertical )
	{
		mEffect->SetBool(mVerticalHandle, vertical);
	}
}