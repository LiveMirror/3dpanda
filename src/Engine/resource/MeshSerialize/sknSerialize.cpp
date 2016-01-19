#include "sknSerialize.h"
#include "../VertexData.h"
#include "../ResMeshImpl.h"
#include "Resources/IResMesh.h"
#include "../SubMesh.h"
#include "../ResourceMgr.h"
#include "../IndexData.h"

namespace shine
{
	bool sknSerialize::ImportMesh( CFileIO& file, IResMesh* pMesh )
	{
		s32 header;
		file.Read(header);

		s16 objNum;
		file.Read(objNum);

		file.Read(mSubNum);

		ResMeshImpl* pImpl = (ResMeshImpl*)pMesh->mImpl;
		ReadSubMeshInfo(file, pImpl);

		s32 indexNum;
		file.Read(indexNum);

		s32 vertexNum;
		file.Read(vertexNum);

		if(!ReadIndex(file, indexNum, pImpl))
		{
			return false;
		}
		if (!ReadVertex(file, vertexNum, pImpl))
		{
			return false;
		}
		return true;
	}

	void sknSerialize::ReadSubMeshInfo( CFileIO& file, ResMeshImpl* pImpl)
	{
		SubMeshInfo info;
		for(s16 i = 0; i < mSubNum; i++)
		{
			file.Read(info.index);			// index
			file.Read(info.buffer, 64);		// name
			file.Read(info.vPos);
			file.Read(info.vNum);
			file.Read(info.iPos);
			file.Read(info.iNum);
			mSubMeshs.push_back(info);
			SubMesh* pMesh = pImpl->CreateSubMesh();
			pMesh->mUserSharedVertices = false;
			pMesh->mVertexData = new VertexData(pImpl->mCreater->GetDevice());
			pMesh->mVertexData->mVertexCount = info.vNum;
			pMesh->mVertexData->AddElement(0, 0, DeclareType::DECLTYPE_FLOAT3, 0, DeclareUsage::DECLUSAGE_POSITION, 0);
			pMesh->mVertexData->AddElement(0, 12, DeclareType::DECLTYPE_UBYTE4, 0, DeclareUsage::DECLUSAGE_BLENDINDICES, 0);
			pMesh->mVertexData->AddElement(0, 16, DeclareType::DECLTYPE_FLOAT4, 0, DeclareUsage::DECLUSAGE_BLENDWEIGHT, 0);
			pMesh->mVertexData->AddElement(0, 32, DeclareType::DECLTYPE_FLOAT3, 0, DeclareUsage::DECLUSAGE_NORMAL, 0);
			pMesh->mVertexData->AddElement(0, 44, DeclareType::DECLTYPE_FLOAT2, 0, DeclareUsage::DECLUSAGE_TEXCOORD, 0);
			pMesh->mIndexData = new IndexData(pImpl->mCreater->GetDevice());
			pMesh->mIndexData->CreateHardwareBuffer(info.iNum, false);
		}
	}

	bool sknSerialize::ReadIndex( CFileIO& file, s32 indexNum, ResMeshImpl* pMesh)
	{
		s32 curIndex = 0;
		for(s16 i = 0; i < mSubNum; i++)
		{
			SubMeshInfo& info = mSubMeshs[i];
			SubMesh* subMesh = pMesh->mSubMeshs[i];
			if (curIndex != info.iPos)
			{
				return false;
			}
			void* pData = subMesh->mIndexData->LockBuffer();
			file.Read(pData, subMesh->mIndexData->GetBufferLen());
			subMesh->mIndexData->Unlock();
			curIndex += info.iNum;
		}

		if (curIndex != indexNum)
		{
			return false;
		}
		return true;
	}

	bool sknSerialize::ReadVertex( CFileIO& file, s32 vertexNum, ResMeshImpl* pMesh )
	{
		s32 curIndex = 0;
		for(s16 i = 0; i < mSubNum; i++)
		{
			SubMeshInfo& info = mSubMeshs[i];
			if (curIndex != info.iPos)
			{
				return false;
			}
			SubMesh* subMesh = pMesh->mSubMeshs[i];
			VertexData::HardwareBuffer* data = subMesh->mVertexData->CreateHardwareBuffer(0, 52);
			void* pBuf = data->LockBuffer();
			file.Read(pBuf, 52 * info.vNum);
			data->Unlock();
			curIndex += info.vNum;
		}

		if (curIndex != vertexNum)
		{
			return false;
		}
		return true;
	}
}