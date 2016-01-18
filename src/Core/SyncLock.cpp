#include "SyncLock.h"

namespace panda
{
	ISyncToken::ISyncToken( SyncLock* creator )
		:mCreater(creator)
	{
		mCreater->Lock();
	}

	ISyncToken::~ISyncToken( void )
	{
		mCreater->Unlock();
	}

	SyncLock::SyncLock( void )
	{
		::InitializeCriticalSection(&mLock);
	}

	SyncLock::~SyncLock( void )
	{
		ForceUnlock();
		::DeleteCriticalSection(&mLock);
	}

	SyncToken SyncLock::GetToken()
	{
		return new ISyncToken(this);
	}

	void SyncLock::ForceUnlock()
	{
		while (-1 > mLock.LockCount && NULL != mLock.OwningThread)
		{
			::LeaveCriticalSection(&mLock);
		}
	}

	void SyncLock::Lock()
	{
		::EnterCriticalSection(&mLock);
	}

	void SyncLock::Unlock()
	{
		::LeaveCriticalSection(&mLock);
	}

	bool SyncLock::TryLock()
	{
		return 0 != ::TryEnterCriticalSection(&mLock);
	}
}