//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/3/21 10:20:44_
// 描述:  同步锁
//

#ifndef _LOCK_2013321102044_
#define _LOCK_2013321102044_

#include "ref.hpp"

namespace panda
{
	class SyncLock;
	/*
	* 智能锁对象
	*/
	class ISyncToken:public IReference
	{
	public:
		ISyncToken(SyncLock* creator);
		virtual ~ISyncToken(void);
	protected:
		SyncLock* mCreater;
	};

	typedef Ref<ISyncToken>		SyncToken;

	class SyncLock
	{
	public:
		SyncLock(void);
		~SyncLock(void);

		//! 使用这种方式获得的SyncTokenRef, 
		// 必须在SyncObject释放之前释放, 否则系统崩溃
		SyncToken		GetToken();

		//! 强制解锁, 使得当前线程对这个锁释放
		void            ForceUnlock();

		//! 使用引用计数的方式进行锁
		//! 调用一次lock, 本线程对锁的引用计数+1
		//! 调用一次unlock, 本线程对锁的引用计数-1
		//! 没有引用计数时, 本线程对锁无锁
		void            Lock();
		void            Unlock();

		//! 成功锁定时返回true, 否则为false已被其他线程占用
		bool            TryLock();
	protected:
		CRITICAL_SECTION    mLock;
	};
}

#endif // _LOCK_2013321102044_