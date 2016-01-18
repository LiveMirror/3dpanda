////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2011-6-23 10:31:05
// 描述: 智能对象
////////////////////////////////////////////////////////

#ifndef	_Tian_2014623103105_H_
#define	_Tian_2014623103105_H_

#include "Config.h"

namespace panda
{
	class IReference
	{
	public:
		IReference(){ mRefCount = 0;}
		virtual ~IReference(){}
		virtual void	Release(void) { delete this; }
		s32 mRefCount;
	};

	template<typename T>
	class Ref
	{
	public:
		Ref():mPtr(NULL)						{ }
		Ref(T* p)								{ mPtr = p;_AddRef(); }
		Ref(const Ref<T>& other)				{ mPtr = static_cast<T*>(other.mPtr); _AddRef(); }
		template<typename Q>
		Ref(const Ref<Q>& other)				{ mPtr = static_cast<T*>(other.mPtr); _AddRef(); }

		~Ref()									{ _deleteRef(); }
		void operator=(const Ref<T>& other)		{ _deleteRef(); mPtr = other.mPtr; _AddRef(); }
		template<typename Q>
		void operator = (const Ref<Q>& other)	{ _deleteRef();	mPtr = static_cast<T*>(other.mPtr);	_AddRef();
		}

		bool operator == (const Ref<T>& other)	{ return mPtr == other.mPtr; }
		bool operator != (const Ref<T>& other)	{ return mPtr != other.mPtr; }
		template<typename Q>
		bool operator == (const Ref<Q>& other)	{ return mPtr == static_cast<T*>(other.mPtr); }
		template<typename Q>
		bool operator != (const Ref<Q>& other)	{ return mPtr != static_cast<T*>(other.mPtr); }
		
		T* operator ->()						{ return mPtr; }
		T* Get()								{ return mPtr; }
		T* operator *()							{ return mPtr; }
		bool IsNull()							{ return NULL == mPtr; }
		static Ref<T>& Null()					{ static Ref<T> objNull; return objNull; }

	private:
		void	_AddRef()						{ if(NULL != mPtr){mPtr->mRefCount++;} }
		void	_deleteRef()
		{
			if (NULL != mPtr)
			{
				mPtr->mRefCount--;
				if (mPtr->mRefCount <= 0)
				{
					if (NULL != mPtr)
					{
						mPtr->Release();
					}
				}
			}
		}
	public:
		T*		mPtr;
	};
}

#endif // _Tian_2014623103105_H_