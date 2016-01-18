#include "SubMeshObject.h"
#include "Resources/IResMesh.h"
#include "Resources/IMaterial.h"
#include "MeshObjectImpl.h"
#include "Scene/ISceneNode.h"
#include "../RenderSystem/RenderSystem.h"
#include "../Resource/VertexData.h"
#include "../Resource/IndexData.h"
#include "../Resource/ResMeshImpl.h"
#include "../Resource/SubMesh.h"

namespace panda
{
	SubMeshObject::SubMeshObject( MeshObjectImpl* parent )
		:mParent(parent)
	{

	}

	const Matrix44f& SubMeshObject::GetWorldTransforms( void ) const
	{
		return mParent->mParent->GetWorldMatrix();
	}

	AABBOX& SubMeshObject::GetBoundBox( void ) const
	{
		throw 0;
	}

	void SubMeshObject::RenderGeometry( RenderSystem* pRender ) const
	{
		// 共用顶点数据
		u32 vertexNum;
		if(mSubMesh->mUserSharedVertices)
		{
			ResMeshImpl* pImpl = (ResMeshImpl*)mParent->mResMesh->mImpl;
			pRender->SetVertexBuffer(pImpl->mVertexData);
			vertexNum = pImpl->mVertexData->mVertexCount;
		}
		else
		{
			pRender->SetVertexBuffer(mSubMesh->mVertexData);
			vertexNum = mSubMesh->mVertexData->mVertexCount;
		}
		pRender->SetIndexBuffer(mSubMesh->mIndexData);
		pRender->DrawIndexedPrimitive(mSubMesh->mRenderOp, vertexNum, _RenderNum(mSubMesh->mRenderOp, mSubMesh->mIndexData->mCount));
	}

	s32 SubMeshObject::_RenderNum( RenderOperation::eValue op, s32 indexCount )const
	{
		switch(op)
		{
		case RenderOperation::OT_TRIANGLE_LIST:
			{
				return indexCount / 3;
			}
		case RenderOperation::OT_LINE_LIST:
			{
				return indexCount / 2;
			}
		case RenderOperation::OT_LINE_STRIP:
			{
				return indexCount - 1;
			}
		}

		return 0;
	}
}