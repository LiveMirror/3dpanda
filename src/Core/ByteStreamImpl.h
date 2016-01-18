//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2013/3/27 15:06:18_
// ����:  
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
		byte*	mBuf;			// ������
		s32		mBufLen;		// ��������С
		bool	mCanResize;		// ���ⲿָ��bufʱ,�������·���ռ�
		s32		mCurPos;		// ��ǰλ��
		s32		mDataLen;		// ���ݴ�С
	};
}

#endif // _BYTESTREAMIMPL_2013327150618_