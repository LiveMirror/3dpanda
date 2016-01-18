//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2013/3/26 9:22:24_
// ����:  �ڴ��
//

#ifndef _MEMORYPOOL_201332692224_
#define _MEMORYPOOL_201332692224_

#include "config.h"
#include "SyncLock.h"

namespace panda
{
	template<typename T>
	class MemoryPool
	{
	public:
		class Node
		{
		public:
			Node()
			{
				mNextNode = NULL;
				mData = NULL;
			}
		public:
			T*		mData;
			Node*	mNextNode;
		};

	public:
		MemoryPool(s32 count)
		{
			mListCount = count;
			mPtr = new Node[count];
			mDataBegin = &mPtr[0];
			mDataEnd = mDataBegin;
			mLength = 0;
			mAvailableNum = 0;
			mListEnd = mDataBegin;

			// ���б�����
			for(s32 i = 1; i < count; i++)
			{
				mListEnd->mNextNode = &mPtr[i];
				mListEnd = &mPtr[i];
			}
			_newNode(count / 5);
		}

		~MemoryPool(void)
		{
			delete[] mPtr;
		}

		T*		Create(void)
		{
			SyncToken token = mLock.GetToken();
			if (0 == mAvailableNum)
			{
				_newNode(mListCount / 5);
			}
			mAvailableNum--;
			Node* temp = mDataBegin;
			mDataBegin = temp->mNextNode;
			temp->mNextNode = NULL;
			if(0 == mAvailableNum)
			{
				mDataEnd = mDataBegin;
			}

			// ���˽ڵ�ҽӵ��б�ĩβ
			mListEnd->mNextNode = temp;
			mListEnd = temp;
			
			return temp->mData;
		}

		
		void	Recycle(T* buf)
		{
			if(mAvailableNum < mListCount)
			{
				// ���ù��캯��
				// �ڻ���ʱ���ù��캯��,���Է�ֹ���캯���ظ�����
				new (buf)T();
				mDataEnd = mDataEnd->mNextNode;
				mDataEnd->mData = buf;
				mAvailableNum++;
			}
			else
			{
				// ����б�����,������buf
				delete buf;
			}
		}

		s32		AvailableNum()	{ return mAvailableNum; }
		s32		Length()		{ return mLength; }

	protected:
		void	_newNode(s32 count) 
		{
			if (0 == mAvailableNum)
			{
				mDataBegin->mData = new T;
				mAvailableNum++;
				mLength++;
				count--;
			}

			for(s32 i = 0; i < count; i++)
			{
				mDataEnd = mDataEnd->mNextNode;
				mDataEnd->mData = new T;
			}
			mAvailableNum += count;
			mLength += count;
		}
	protected:
		SyncLock	mLock;
		Node*	mPtr;			// �ڴ�ռ���׵�ַ
		s32		mListCount;
		s32		mLength;		// �ܳ���
		s32		mAvailableNum;	// ���ó���
		Node*	mDataBegin;
		Node*	mDataEnd;

		Node*	mListEnd;		// �б�����
	};
}

#endif // _MEMORYPOOL_201332692224_