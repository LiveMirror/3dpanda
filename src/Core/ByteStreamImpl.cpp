
#include "ByteStreamImpl.h"

namespace panda
{
	ByteStreamImpl::ByteStreamImpl( byte* buf, s32 len )
		:mBuf(buf),
		mBufLen(len),
		mCurPos(0),
		mDataLen(0)
	{
		if (NULL == mBuf)
		{
			mCanResize = true;
			mBuf = new byte[mBufLen];
		}
		else
		{
			mCanResize = false;
			mDataLen = len;
		}
	}

	ByteStreamImpl::~ByteStreamImpl( void )
	{
		if(mCanResize)
		{
			delete[] mBuf;
		}
	}


	bool ByteStreamImpl::Write( byte* buf, s32 len )
	{
		s32 capacity = mBufLen - mCurPos;
		if(capacity < len)
		{
			if(!mCanResize)
			{
				return false;
			}
			s32 newLen = (s32)(mBufLen * 1.5);
			byte* temp = new byte[newLen];
			memcpy(temp, mBuf, mDataLen);
			mBufLen = newLen;
			delete[] mBuf;
			mBuf = temp;
		}

		memcpy(mBuf + mCurPos, buf, len);
		mCurPos += len;
		if(mCurPos > mDataLen)
		{
			mDataLen = mCurPos;
		}
		return true;
	}

	bool ByteStreamImpl::Read( byte* buf, s32 len )
	{
		s32 dataLen = mDataLen - mCurPos;
		if(dataLen < len)
		{
			return false;
		}
		memcpy(buf, mBuf + mCurPos, len);
		mCurPos += len;
		return true;
	}

	void ByteStreamImpl::SetCurPos( s32 pos )
	{
		if(pos < 0 || pos > mDataLen)
		{
			mCurPos = mDataLen;
		}
		else
		{
			mCurPos = pos;
		}
	}
}