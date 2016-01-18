#include "Thread.h"
#include "ThreadImpl.h"

namespace panda
{
	Thread::Thread( void* lpParam /*= NULL*/ )
	{
		mImpl = new ThreadImpl;
		mImpl->mlpParam = lpParam;
		DWORD id;
		mImpl->mhThread = ::CreateThread(NULL, 0, ThreadImpl::Callback, this, CREATE_SUSPENDED, &id);
		mImpl->mThreadID = id;
	}

	Thread::~Thread( void )
	{
		delete mImpl;
	}

	bool Thread::start()
	{
		if( 0xFFFFFFFF == ::ResumeThread(mImpl->mhThread))
		{
			return false;
		}
		return true;
		
	}

	bool Thread::suspend()
	{
		if( 0xFFFFFFFF == ::SuspendThread(mImpl->mhThread))
		{
			return false;
		}
		return true;
	}

	s32 Thread::CurThreadId()
	{
		return ::GetCurrentThreadId();
	}

	void Thread::Sleep( u32 milliseconds )
	{
		::Sleep( milliseconds );
	}

	HANDLE Thread::getHandle()
	{
		return mImpl->mhThread;
	}

	
}