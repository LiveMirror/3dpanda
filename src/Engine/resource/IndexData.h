//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 11:04:02_
// 描述:  
//

#ifndef _INDEXDATA_201443110402_
#define _INDEXDATA_201443110402_

#include "Base/Config.h"
#include <d3d9.h>

namespace panda
{
	class IndexData
	{
	public:
		IndexData(IDirect3DDevice9* pDevice);
		~IndexData(void);

		void					CreateHardwareBuffer(u32 count, bool is32Bit);
		void*					LockBuffer(void);
		void					Unlock(void);		

		s32						GetBufferLen(void);
	public:
		IDirect3DDevice9*		mDevice;
		IDirect3DIndexBuffer9*	mBuffer;
		void*					mTempBufferPtr;		// LockBuffer
		s32						mBufferLen;
		bool					mIs32Bit;
		u32						mCount;
	};
}

#endif // _INDEXDATA_201443110402_