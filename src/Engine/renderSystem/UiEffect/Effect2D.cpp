#include "Effect2D.h"
#include "base/Vector2D.h"

namespace panda
{
	Effect2D::Effect2D( void )
	{

	}

	bool Effect2D::InitEffect(void)
	{
		mUiSizeHandle = mEffect->GetParameterByName("gUiSize", 0);
		return true;
	}

	void Effect2D::BeginEffect( D3DXHANDLE tech )
	{
		u32 numPass;
		mEffect->SetTechnique(tech);
		mEffect->Begin(&numPass, 0);
		mEffect->BeginPass(0);
	}

	void Effect2D::EndEffect( void )
	{
		mEffect->EndPass();
		mEffect->End();
	}

	void Effect2D::Set2DSize( s32 width, s32 height )
	{
		Vector2Df s((f32)width, (f32)height);
		mEffect->SetValue(mUiSizeHandle, &s, sizeof(s));
	}

	void Effect2D::DeviceLost( void )
	{
		mEffect->OnLostDevice();
	}

	void Effect2D::ResetDevice( void )
	{
		mEffect->OnResetDevice();
		InitEffect();
	}
}