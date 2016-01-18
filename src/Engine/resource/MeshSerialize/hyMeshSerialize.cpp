#include "Resources/IResMesh.h"
#include "../ResMeshImpl.h"
#include "../../resource/VertexData.h"
#include "../../resource/submesh.h"
#include "../../resource/indexdata.h"
#include "../ResourceMgr.h"
#include "hyMeshSerialize.h"

#define MESH_VER 0

namespace panda
{
	bool hyMeshSerialize::ExportMesh( FileStream& file, IResMesh* pMesh )
	{
		return WriteMesh(file, pMesh);
	}

	bool hyMeshSerialize::ImportMesh( FileStream& file, IResMesh* pMesh )
	{
		if(!ReadHeader(file))
		{
			return false;
		}

		ResMeshImpl* pImpl = (ResMeshImpl*)pMesh->mImpl;

		while (!file.Eof())
		{
			file.Read(mChuckID);
			file.Read(mChunkLen);
			switch(mChuckID)
			{
			case 1:
				{
					file.Read(mNumSubMesh);
					break;
				}
			case 2:
				{
					pImpl->mVertexData = new VertexData(pImpl->mResMgr->GetDevice());
					ReadGeomety(file, pImpl, pImpl->mVertexData);
					break;
				}
			case 3:
				{
					ReadSubMesh(file, pImpl);
					break;
				}
			}
		}
		return true;
	}

	bool hyMeshSerialize::WriteMesh( FileStream& file, IResMesh* pMesh )
	{
		char c = 'h';
		file.Write(c);
		c = 'y';
		file.Write(c);
		c = 'm';
		file.Write(c);
		c = 'e';
		file.Write(c);

		s8 ver = MESH_VER;
		file.Write(ver);

		// write mesh
		mChuckID = 1;
		file.Write(mChuckID);
		mChunkLen = 7;
		file.Write(mChunkLen);

		u16 numSubMesh = pMesh->GetSubSetNum();
		file.Write(numSubMesh);

		// write geomety if exist
		ResMeshImpl* pImpl = (ResMeshImpl*)pMesh->mImpl;
		if (NULL != pImpl->mVertexData)
		{
			mChuckID = 2;
			file.Write(mChuckID);
			mChunkLen = CalcGeometySize(pImpl->mVertexData);
			mChunkLen += 5;
			file.Write(mChunkLen);
			if(!WriteGeomety(file, pImpl->mVertexData))
			{
				return false;
			}
		}

		// write submesh
		ResMeshImpl::SubMeshList::iterator i = pImpl->mSubMeshs.begin();
		while (i != pImpl->mSubMeshs.end())
		{
			mChuckID = 3;
			file.Write(mChuckID);
			mChunkLen = CalcSubMeshSize(*i);
			mChunkLen += 5;
			file.Write(mChunkLen);
			if (!WriteSubMesh(file, *i))
			{
				return false;
			}
			i++;
		}
		
		return true;
	}

	bool hyMeshSerialize::WriteGeomety( FileStream& file, VertexData* pData )
	{
		u32 num = pData->mVertexCount;
		file.Write(num);

		u8 numDel = pData->mDeclElments.size();
		file.Write(numDel);

		VertexData::DeclareList::iterator i = pData->mDeclElments.begin();
		while (i != pData->mDeclElments.end())
		{
			VertexDeclare& temp = *i;
			file.Write(temp.Stream);
			file.Write(temp.Offset);
			file.Write(temp.Type);
			file.Write(temp.Usage);
			file.Write(temp.UsageIndex);
			i++;
		}

		u8 numBuf = pData->mBuffers.size();
		file.Write(numBuf);

		VertexData::BufferList::iterator bi = pData->mBuffers.begin();

		std::vector<f32> uv;

		while (bi != pData->mBuffers.end())
		{
			VertexData::HardwareBuffer* buf = bi->second;
			file.Write(buf->mVertexSize);
			file.Write(buf->mSourceID);
			s32 len = pData->mVertexCount * buf->mVertexSize;

			f32* test = (f32*)buf->LockBuffer();
			file.Write(test, len);
			int size = buf->mVertexSize / 4;
			for(u32 n = 0; n < num; n++)
			{
				uv.push_back(test[size * n + 6]);
				uv.push_back(test[size * n + 7]);
			}

			buf->Unlock();
			bi++;
		}
		return true;
	}

	bool hyMeshSerialize::WriteSubMesh( FileStream& file, SubMesh* pSubMesh )
	{
		file.Write(pSubMesh->mUserSharedVertices);
		u16 op = (u16)pSubMesh->mRenderOp;
		file.Write(op);
		file.Write(pSubMesh->mIndexData->mCount);
		file.Write(pSubMesh->mIndexData->mIs32Bit);
		s32 len = pSubMesh->mIndexData->GetBufferLen();
		file.Write(pSubMesh->mIndexData->LockBuffer(), len);
		pSubMesh->mIndexData->Unlock();

		if (!pSubMesh->mUserSharedVertices)
		{
			WriteGeomety(file, pSubMesh->mVertexData);
		}
		return true;
	}

	s32 hyMeshSerialize::CalcGeometySize( VertexData* pData )
	{
		s32 size = 4;	// numVertex
		size += 1;		// num of declare
		// n * declare
		size += 11 * pData->mDeclElments.size();
		size += 1;		// num of buffer

		VertexData::BufferList::iterator itr = pData->mBuffers.begin();
		while (itr != pData->mBuffers.end())
		{
			size += 2;	// vertexSize
			size += 4;	// stream index
			size += pData->mVertexCount * itr->second->mVertexSize;	// data
			itr++;
		}
		return size;
	}

	s32 hyMeshSerialize::CalcSubMeshSize( SubMesh* pSubMesh )
	{
		s32 size = 1;	// shared vertices
		size += 2;		// render operation
		size += 4;		// index count
		size += 1;		// is32bit
		size += pSubMesh->mIndexData->GetBufferLen();		// index data

		// geomety if exist
		if (!pSubMesh->mUserSharedVertices)
		{
			size += CalcGeometySize(pSubMesh->mVertexData);
		}
		return size;
	}

	bool hyMeshSerialize::ReadHeader( FileStream& file )
	{
		char c[4];
		file.Read(c[0]);
		file.Read(c[1]);
		file.Read(c[2]);
		file.Read(c[3]);
		if (c[0] != 'h' ||
			c[1] != 'y' ||
			c[2] != 'm' ||
			c[3] != 'e')
		{
			return false;
		}
		s8 ver;
		file.Read(ver);
		if (ver != MESH_VER)
		{
			return false;
		}
		return true;
	}

	void hyMeshSerialize::ReadGeomety( FileStream& file, ResMeshImpl* pMesh, VertexData* pData )
	{
		file.Read(pData->mVertexCount);
		s8 numDeclare;
		file.Read(numDeclare);
		s32 streamID, offset;
		s8 type, usage, usageIndex;
		for (s8 i = 0; i < numDeclare; i++)
		{
			file.Read(streamID);
			file.Read(offset);
			file.Read(type);
			file.Read(usage);
			file.Read(usageIndex);
			pData->AddElement(streamID, offset, type, 0, usage, usageIndex);
		}
		u8 numBuffer;
		file.Read(numBuffer);
		for (s8 i = 0; i < numBuffer; i++)
		{
			ReadVertexData(file, pMesh, pData);
		}
	}

	void hyMeshSerialize::ReadSubMesh( FileStream& file, ResMeshImpl* pMesh )
	{
		SubMesh* pSM = pMesh->CreateSubMesh();
		file.Read(pSM->mUserSharedVertices);
		u16 renderOp;
		file.Read(renderOp);
		pSM->mRenderOp = (RenderOperation::eValue)renderOp;

		pSM->mIndexData = new IndexData(pMesh->mResMgr->GetDevice());
		u32 count;
		file.Read(count);
		bool is32Bit;
		file.Read(is32Bit);

		// ¶¥µãË÷Òý
		if(count > 0)
		{
			pSM->mIndexData->CreateHardwareBuffer(count, is32Bit);
			void* buffer = pSM->mIndexData->LockBuffer();
			file.Read(buffer, pSM->mIndexData->GetBufferLen());
			pSM->mIndexData->Unlock();
		}

		if (!pSM->mUserSharedVertices)
		{
			pSM->mVertexData = new VertexData(pMesh->mResMgr->GetDevice());
			ReadGeomety(file, pMesh, pSM->mVertexData);
		}
	}

	void hyMeshSerialize::ReadVertexData( FileStream& file, ResMeshImpl* pMesh, VertexData* dest )
	{
		u16 vertexSize;
		file.Read(vertexSize);				//  Per-vertex size, must agree with declaration at this index
		u32 bindIndex;
		file.Read(bindIndex);				//  Index to bind this buffer to

		VertexData::HardwareBuffer* data = dest->CreateHardwareBuffer(bindIndex, vertexSize);
		u32 size = dest->mVertexCount * vertexSize;
		void* buffer = data->LockBuffer();
		file.Read(buffer, size);
		data->Unlock();
	}
}