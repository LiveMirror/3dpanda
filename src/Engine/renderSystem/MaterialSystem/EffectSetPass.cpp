#include "EffectSetPass.h"

namespace panda
{
	EffectSetPass::EffectSetPass( IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr )
		:Pass(d3dDevice, renderMgr)
	{

	}

	void EffectSetPass::SetWorldTransform( const Matrix44f& mat )
	{
		mVConstTable->SetMatrix(mD3dDevice, mHandleWorldMatrix, (const D3DXMATRIX*)&mat);
	}

	void EffectSetPass::_GetPsHandles( void )
	{
		mHandleColor = mPConstTable->GetConstantByName(0, "mEffectColor");
	}

	void EffectSetPass::SetColor( const Colorf& color )
	{
		mVConstTable->SetFloatArray(mD3dDevice, mHandleColor, (f32*)&color, 4);
	}
}