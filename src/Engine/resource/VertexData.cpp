#include "VertexData.h"

namespace panda
{
	VertexData::VertexData(IDirect3DDevice9* pDevice)
		:mDecl(NULL),
		mIsDeclDirty(true),
		mDevice(pDevice),
		mVertexCount(0)
	{

	}

	VertexData::~VertexData( void )
	{
		if(NULL != mDecl)
		{
			mDecl->Release();
		}
		BufferList::iterator itr = mBuffers.begin();
		while (itr != mBuffers.end())
		{
			delete itr->second;
			itr++;
		}
	}

	void VertexData::AddElement( s32 source, s32 offset, s8 dataType, s8 method, s8 usage, s8 usageIndex )
	{
		VertexDeclare declare;
		declare.Stream = source;
		declare.Offset = offset;
		declare.Type = dataType;
		declare.Method = method;
		declare.Usage = usage;
		declare.UsageIndex = usageIndex;
		mDeclElments.push_back(declare);
		mIsDeclDirty = true;
	}

	void VertexData::InsertElement( u16 index, s32 source, s32 offset, s8 dataType, s8 method, s8 usage, s8 usageIndex )
	{
		VertexDeclare declare;
		declare.Stream = source;
		declare.Offset = offset;
		declare.Type = dataType;
		declare.Method = method;
		declare.Usage = usage;
		declare.UsageIndex = usageIndex;

		if (index >= mDeclElments.size())
		{
			mDeclElments.push_back(declare);
		}
		else
		{
			DeclareList::iterator itr = mDeclElments.begin();
			for (u32 i = 0; i < index; i++)
			{
				itr++;
			}
			mDeclElments.insert(itr, declare);
		}
	}

	IDirect3DVertexDeclaration9* VertexData::GetDeclare( void )
	{
		if(mIsDeclDirty)
		{
			_UpdateDeclare();
		}
		return mDecl;
	}

	void VertexData::_UpdateDeclare( void )
	{
		if(NULL != mDecl)
		{
			mDecl->Release();
		}
		if (mDeclElments.empty())
		{
			mDecl = NULL;
			return;
		}
		s32 num = mDeclElments.size();

		D3DVERTEXELEMENT9* arr = new D3DVERTEXELEMENT9[num + 1];
		s32 index = 0;
		DeclareList::iterator itr = mDeclElments.begin();
		while (itr != mDeclElments.end())
		{
			arr[index].Method = (*itr).Method;
			arr[index].Offset = (*itr).Offset;
			arr[index].Stream = (*itr).Stream;
			arr[index].Type = (*itr).Type;
			arr[index].Usage = (*itr).Usage;
			arr[index].UsageIndex = (*itr).UsageIndex;
			index++;
			itr++;
		}

		arr[num].Method = VertexDeclare::DeclareEnd.Method;
		arr[num].Offset = VertexDeclare::DeclareEnd.Offset;
		arr[num].Stream = VertexDeclare::DeclareEnd.Stream;
		arr[num].Type = VertexDeclare::DeclareEnd.Type;
		arr[num].Usage = VertexDeclare::DeclareEnd.Usage;
		arr[num].UsageIndex = VertexDeclare::DeclareEnd.UsageIndex;

		mDevice->CreateVertexDeclaration(arr, &mDecl);
		delete[] arr;

		mIsDeclDirty = false;
	}	

	const VertexDeclare& VertexData::GetElement( u16 index )
	{
		DeclareList::iterator i = mDeclElments.begin();
		for (u16 n = 0; n < index; ++n)
			++i;

		return (*i);
	}

	VertexData::HardwareBuffer* VertexData::CreateHardwareBuffer( s32 sourceID, u16 vertexSize )
	{
		s32 len = mVertexCount * vertexSize;
		VertexData::HardwareBuffer* pBuffer = new VertexData::HardwareBuffer(sourceID, vertexSize);
		mDevice->CreateVertexBuffer(len, 0, 0, D3DPOOL_MANAGED, &pBuffer->mBuffer, NULL);
		pBuffer->mBufferLen = len;
		mBuffers[sourceID] = pBuffer;
		return pBuffer;
	}

	void VertexData::BindStreamSource()
	{
		BufferList::iterator itr = mBuffers.begin();
		while (itr != mBuffers.end())
		{
			HardwareBuffer* buffer = itr->second;
			mDevice->SetStreamSource(buffer->mSourceID, buffer->mBuffer, 0, buffer->mVertexSize);
			itr++;
		}
	}

	VertexData::HardwareBuffer* VertexData::_FindPosBuffer( s32& offset)
	{
		DeclareList::iterator itr = mDeclElments.begin();
		while (itr != mDeclElments.end())
		{
			if (itr->Usage == DeclareUsage::DECLUSAGE_POSITION)
			{
				s32 sourceID = itr->Stream;
				offset = itr->Offset;
				BufferList::iterator bi = mBuffers.find(sourceID);
				if (bi != mBuffers.end())
				{
					return bi->second;
				}
			}
			itr++;
		}
		return NULL;
	}

	void* VertexData::LockBuffer( s32 sourceID )
	{
		VertexData::BufferList::iterator itr = mBuffers.find(sourceID);
		if(itr != mBuffers.end())
		{
			return itr->second->LockBuffer();
		}
		return NULL;
	}

	void VertexData::Unlock( s32 sourceID )
	{
		VertexData::BufferList::iterator itr = mBuffers.find(sourceID);
		if(itr != mBuffers.end())
		{
			return itr->second->Unlock();
		}
	}

	VertexData::HardwareBuffer::HardwareBuffer(s32 sourceID, u16 vertexSize)
		:mBuffer(NULL),
		mSourceID(sourceID),
		mVertexSize(vertexSize)
	{

	}

	VertexData::HardwareBuffer::~HardwareBuffer()
	{
		if (NULL != mBuffer)
		{
			mBuffer->Release();
		}
	}

	void* VertexData::HardwareBuffer::LockBuffer( void )
	{
		mBuffer->Lock(0, 0, &mTempBufferPtr, 0);
		return mTempBufferPtr;
	}

	void* VertexData::HardwareBuffer::LockBuffer( u32 offset, u32 len )
	{
		mBuffer->Lock(offset, len, &mTempBufferPtr, 0);
		return mTempBufferPtr;
	}

	void VertexData::HardwareBuffer::Unlock( void )
	{
		mBuffer->Unlock();
	}
}