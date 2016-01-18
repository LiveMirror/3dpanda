#include "SknPass.h"
#include "../../scene/SubMeshObject.h"
#include "../../scene/MeshObjectImpl.h"
#include "../../scene/CameraImpl.h"
#include "resources/IResSkeleton.h"

namespace panda
{
	SknPass::SknPass( IDirect3DDevice9* d3dDevice, RenderSystem* renderMgr)
		:Pass(d3dDevice, renderMgr)
	{

	}

	void SknPass::_GetVsHandles( void )
	{
		mHandleMatrixArray = mVConstTable->GetConstantByName(0, "mWorldMatrixArray");
	}

	void SknPass::_SetParam( MaterialImpl* mat, CameraImpl* pCamera, Renderable* pObject )
	{
		SubMeshObject* meshObj = (SubMeshObject*)pObject;

		if (!meshObj->mParent->mSkeletion.IsNull())
		{
			mVConstTable->SetMatrixArray(mD3dDevice, mHandleMatrixArray, 
				(const D3DXMATRIX*)meshObj->mParent->mBoneMatrixs, 
				meshObj->mParent->mSkeletion->GetNumBones());
		}
	}
}