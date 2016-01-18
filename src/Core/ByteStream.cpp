#include "ByteStream.h"
#include "ByteStreamImpl.h"

namespace panda
{
	ByteStream::ByteStream( s32 len /*= 1024*/ )
	{
		mImpl = new ByteStreamImpl(NULL, len);
	}

	ByteStream::ByteStream( byte* buf, s32 len )
	{
		mImpl = new ByteStreamImpl(buf, len);
	}

	ByteStream::~ByteStream( void )
	{
		delete mImpl;
	}

	byte* ByteStream::Data( void )
	{
		return mImpl->mBuf;
	}

	bool ByteStream::Write( byte* buf, s32 len )
	{
		return mImpl->Write(buf, len);
	}

	bool ByteStream::Read( byte* buf, s32 len )
	{
		return mImpl->Read(buf, len);
	}

	s32 ByteStream::Size( void )
	{
		return mImpl->mDataLen;
	}

	s32 ByteStream::GetCurPos( void )
	{
		return mImpl->mCurPos;
	}

	void ByteStream::SetCurPos( s32 pos )
	{
		mImpl->SetCurPos(pos);
	}
}