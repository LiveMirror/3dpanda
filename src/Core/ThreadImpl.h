//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2013/3/21 14:34:31_
// ����:  
//

#ifndef _THREADIMPL_2013321143431_
#define _THREADIMPL_2013321143431_

#include "Config.h"

namespace panda
{
	class ThreadImpl
	{
	public:
		static DWORD WINAPI Callback(LPVOID lpParam);

	public:
		HANDLE      mhThread;
		void*		mlpParam;
		u32			mThreadID;
	};
}

#endif // _THREADIMPL_2013321143431_