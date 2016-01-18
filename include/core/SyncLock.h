//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2013/3/21 10:20:44_
// ����:  ͬ����
//

#ifndef _LOCK_2013321102044_
#define _LOCK_2013321102044_

#include "ref.hpp"

namespace panda
{
	class SyncLock;
	/*
	* ����������
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

		//! ʹ�����ַ�ʽ��õ�SyncTokenRef, 
		// ������SyncObject�ͷ�֮ǰ�ͷ�, ����ϵͳ����
		SyncToken		GetToken();

		//! ǿ�ƽ���, ʹ�õ�ǰ�̶߳�������ͷ�
		void            ForceUnlock();

		//! ʹ�����ü����ķ�ʽ������
		//! ����һ��lock, ���̶߳��������ü���+1
		//! ����һ��unlock, ���̶߳��������ü���-1
		//! û�����ü���ʱ, ���̶߳�������
		void            Lock();
		void            Unlock();

		//! �ɹ�����ʱ����true, ����Ϊfalse�ѱ������߳�ռ��
		bool            TryLock();
	protected:
		CRITICAL_SECTION    mLock;
	};
}

#endif // _LOCK_2013321102044_