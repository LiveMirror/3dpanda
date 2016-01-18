#include "ThreadImpl.h"
#include "Thread.h"

namespace panda
{
	DWORD WINAPI ThreadImpl::Callback( LPVOID lpParam )
	{
		Thread* t = static_cast<Thread*>(lpParam);
		return t->OnInvoke(t->mImpl->mlpParam);
	}
}