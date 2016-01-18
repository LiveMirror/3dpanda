#include "LinePass.h"
#include "../../scene/CameraImpl.h"
#include "../../scene/SubMeshObject.h"

namespace panda
{
	LinePass::LinePass( IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr)
		:Pass(d3dDevice, renderMgr)
	{

	}

	void LinePass::SetParam( MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject )
	{
		// set viewpro matrix
		mVConstTable->SetMatrix(mD3dDevice, mHandleViewProj, (const D3DXMATRIX*)&pCamera->GetViewProMatrix());

		// set the world matrix
		SubMeshObject* meshObj = (SubMeshObject*)pObject;
		mVConstTable->SetMatrix(mD3dDevice, mHandleWorldMatrix, (const D3DXMATRIX*)&meshObj->GetWorldTransforms());
	}

	void LinePass::GetPsHandles( void )
	{

	}
}