//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/3/21 14:30:56_
// 描述:  
//

#ifndef _THREAD_2013321143056_
#define _THREAD_2013321143056_

#include "Config.h"

namespace panda
{
	class ThreadImpl;
	class Thread
	{
	public:
		Thread(void* lpParam = NULL);
		virtual ~Thread(void);

		//! start or resume thread
		bool            start();

		//! 线程的挂起只能由线程自身调用
		bool            suspend();

		//! 获取当前线程的句柄
		HANDLE			getHandle();

		/*---------------------------
			对当前线程的操作
		---------------------------*/
		virtual s32     OnInvoke(void* lpParam) = 0;

	public:
		ThreadImpl*		mImpl;
	public:
		static s32		CurThreadId();
		static void		Sleep( u32 milliseconds );
	};
}

#endif // _THREAD_2013321143056_