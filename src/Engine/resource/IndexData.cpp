#include "IndexData.h"

namespace panda
{
	IndexData::IndexData(IDirect3DDevice9* pDevice)
		:mDevice(pDevice),
		mBuffer(NULL)
	{

	}

	IndexData::~IndexData( void )
	{
		if (NULL != mBuffer)
		{
			mBuffer->Release();
		}
	}

	void* IndexData::LockBuffer( void )
	{
		mBuffer->Lock(0, 0, &mTempBufferPtr, 0);
		return mTempBufferPtr;
	}

	void IndexData::Unlock( void )
	{
		mBuffer->Unlock();
	}

	s32 IndexData::GetBufferLen( void )
	{
		return mBufferLen;
	}

	void IndexData::CreateHardwareBuffer( u32 count, bool is32Bit )
	{
		mCount = count;
		mIs32Bit = is32Bit;
		mBufferLen = mIs32Bit ? count * sizeof(s32) : count * sizeof(s16);

		if(is32Bit)
		{
			mDevice->CreateIndexBuffer(mBufferLen, D3DUSAGE_WRITEONLY, 
				D3DFMT_INDEX32,
				D3DPOOL_MANAGED,
				&mBuffer, NULL);
		}
		else
		{
			mDevice->CreateIndexBuffer(mBufferLen, D3DUSAGE_WRITEONLY, 
				D3DFMT_INDEX16,
				D3DPOOL_MANAGED,
				&mBuffer, NULL);
		}
	}
}