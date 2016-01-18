//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/3/27 14:52:11_
// 描述:  流操作
//

#ifndef _BYTESTREAM_2013327145211_
#define _BYTESTREAM_2013327145211_

#include "Config.h"

namespace panda
{
	class ByteStreamImpl;
	class ByteStream
	{
	public:
		ByteStream(s32 len = 1024);
		ByteStream(byte* buf, s32 len);
		~ByteStream(void);

		byte*	Data(void);

		bool	Write(byte* buf, s32 len);
		template<typename T>
		bool	Write(T& v) { return Write((byte*)&v, sizeof(v)); }

		bool	Read(byte* buf, s32 len);
		template<typename T>
		bool	Read(T& v) { return Read((byte*)&v, sizeof(v)); }

		s32		Size(void);

		s32		GetCurPos(void);

		//! 设置当前位置,如果pos<0,将移动到数据的末尾
		void	SetCurPos(s32 pos);
	protected:
		ByteStreamImpl*	mImpl;
	};
}

#endif // _BYTESTREAM_2013327145211_