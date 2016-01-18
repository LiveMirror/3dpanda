//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/3/27 15:06:18_
// 描述:  
//

#ifndef _BYTESTREAMIMPL_2013327150618_
#define _BYTESTREAMIMPL_2013327150618_

#include "Config.h"

namespace panda
{
	class ByteStreamImpl
	{
	public:
		ByteStreamImpl(byte* buf, s32 len);
		~ByteStreamImpl(void);

		bool	Write(byte* buf, s32 len);
		bool	Read(byte* buf, s32 len);
		void	SetCurPos(s32 pos);
	public:
		byte*	mBuf;			// 缓冲区
		s32		mBufLen;		// 缓冲区大小
		bool	mCanResize;		// 由外部指定buf时,不会重新分配空间
		s32		mCurPos;		// 当前位置
		s32		mDataLen;		// 数据大小
	};
}

#endif // _BYTESTREAMIMPL_2013327150618_