#include "CircleEffect.h"
#include "base/Vector2D.h"

namespace panda
{
	bool CircleEffect::InitEffect( void )
	{
		__super::InitEffect();
		mFillTech = mEffect->GetTechniqueByName("FillCircle");
		mDrawTech = mEffect->GetTechniqueByName("DrawCircle");
		mColorHandle = mEffect->GetParameterByName("gCircleColor", 0);
		mCenterHandle = mEffect->GetParameterByName("gCenter", 0);
		mRadiusHandle = mEffect->GetParameterByName("gRadius", 0);
		return true;
	}

	void CircleEffect::SetColor( const Color& c )
	{
		D3DXCOLOR v((f32)c.R / 255.0f, (f32)c.G / 255.0f, (f32)c.B / 255.0f, (f32)c.A / 255.0f);
		mEffect->SetValue(mColorHandle, &v, sizeof(v));
	}

	void CircleEffect::SetCenter( s32 x, s32 y )
	{
		Vector2Df s((f32)x, (f32)y);
		mEffect->SetValue(mCenterHandle, &s, sizeof(s));
	}

	void CircleEffect::SetRadius( f32 r )
	{
		mEffect->SetFloat(mRadiusHandle, r);
	}
}