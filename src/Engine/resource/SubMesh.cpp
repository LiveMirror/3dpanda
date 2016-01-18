#include "SubMesh.h"
#include "VertexData.h"
#include "IndexData.h"
#include "Resources/IResMesh.h"
#include "ResourceImpl.h"
#include "ResourceMgr.h"

namespace panda
{
	SubMesh::SubMesh(IResMesh* parent)
		:mParent(parent),
		mVertexData(NULL),
		mUserData(NULL),
		mIndexData(NULL),
		mRenderOp(RenderOperation::OT_TRIANGLE_LIST)
	{

	}

	SubMesh::~SubMesh( void )
	{
		if (NULL != mVertexData)
		{
			delete mVertexData;
		}
		if (NULL != mIndexData)
		{
			delete mIndexData;
		}
	}

	void SubMesh::SetRenderOperation( RenderOperation::eValue op )
	{
		mRenderOp = op;
	}

	RenderOperation::eValue SubMesh::GetRenderOperation( void ) const
	{
		return mRenderOp;
	}

	void SubMesh::SetVertexCount( s32 count )
	{
		mVertexData = new VertexData(mParent->mImpl->mResMgr->GetDevice());
		mVertexData->mVertexCount = count;
	}

	void SubMesh::AddElement( s32 source, s32 offset, s8 dataType, s8 usage, s8 usageIndex )
	{
		if(NULL != mVertexData)
		{
			mVertexData->AddElement(source, offset, dataType, 0, usage, usageIndex);
		}
	}

	void SubMesh::CreateVertexBuffer(s32 sourceID, s32 vertexSize)
	{
		if(NULL != mVertexData)
		{
			mVertexData->CreateHardwareBuffer(sourceID, vertexSize);
		}
	}

	void* SubMesh::LockVertexBuffer( s32 sourceID )
	{
		if(NULL != mVertexData)
		{
			return mVertexData->LockBuffer(sourceID);
		}
		return NULL;
	}

	void SubMesh::UnLockVertexBuffer( s32 sourceID )
	{
		if(NULL != mVertexData)
		{
			mVertexData->Unlock(sourceID);
		}
	}

	void SubMesh::SetIndexCount( s32 count, bool is32Bit )
	{
		mIndexData = new IndexData(mParent->mImpl->mResMgr->GetDevice());
		mIndexData->CreateHardwareBuffer(count, is32Bit);
	}

	void* SubMesh::LockIndexBuffer( void )
	{
		if(NULL != mIndexData)
		{
			return mIndexData->LockBuffer();
		}
		return NULL;
	}

	void SubMesh::UnLockIndexBuffer( void )
	{
		if(NULL != mIndexData)
		{
			mIndexData->Unlock();
		}
	}
}