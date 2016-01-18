//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 11:07:04_
// 描述:  
//

#ifndef _VERTEXDATA_201443110704_
#define _VERTEXDATA_201443110704_

#include <list>
#include <map>
#include "Base/Config.h"
#include "Base/Struct.h"
#include <d3dx9.h>

namespace panda
{
	class VertexData
	{
	public:
		VertexData(IDirect3DDevice9* pDevice);
		~VertexData(void);

		class HardwareBuffer
		{
		public:
			HardwareBuffer(s32 sourceID, u16 vertexSize);
			~HardwareBuffer();
			s32								mSourceID;
			u16								mVertexSize;
			IDirect3DVertexBuffer9*			mBuffer;
			void*							mTempBufferPtr;		// LockBuffer

			s32								mBufferLen;			// 缓存buffer长度

			void*							LockBuffer(void);
			void*							LockBuffer(u32 offset, u32 len);
			void							Unlock(void);
		};

		void							AddElement(s32 source, s32 offset, s8 dataType, s8 method, s8 usage, s8 usageIndex);

		void							InsertElement(u16 index, s32 source, s32 offset, s8 dataType, s8 method, s8 usage, s8 usageIndex);

		const VertexDeclare&			GetElement(u16 index);

		IDirect3DVertexDeclaration9*	GetDeclare(void);

		void*							LockBuffer(s32 sourceID);
		void							Unlock(s32 sourceID);

		HardwareBuffer*					CreateHardwareBuffer(s32 sourceID, u16 vertexSize);

		//! 绑定顶点数据到GPU
		void							BindStreamSource();

		//! 从VertexDeclare中找出顶点位置buffer
		HardwareBuffer*					_FindPosBuffer(s32& offset);

		void							_UpdateDeclare(void);
	public:
		IDirect3DDevice9*				mDevice;
		u32								mVertexCount;
		IDirect3DVertexDeclaration9*	mDecl;
		bool							mIsDeclDirty;

		typedef std::list<VertexDeclare> DeclareList;
		DeclareList						mDeclElments;

		typedef std::map<s32, HardwareBuffer*> BufferList;
		BufferList						mBuffers;
	};
}

#endif // _VERTEXDATA_201443110704_