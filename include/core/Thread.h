//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2013/3/21 14:30:56_
// ����:  
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

		//! �̵߳Ĺ���ֻ�����߳��������
		bool            suspend();

		//! ��ȡ��ǰ�̵߳ľ��
		HANDLE			getHandle();

		/*---------------------------
			�Ե�ǰ�̵߳Ĳ���
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