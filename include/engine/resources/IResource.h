////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2012-10-21 22:34:14
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_20121021223414_H_
#define	_Tian_20121021223414_H_

#include "Base/Config.h"
#include "Base/Struct.h"

namespace panda
{
	class ResourceImpl;
	/*
	* ��Դ
	*/
	class IResource
	{
	public:
		IResource(ResourceImpl*	pImpl);
		virtual ~IResource(void);

		virtual const tchar*		GetResPath(void)const;

		//! set the path of the res
		//! it could work just when the res be created.
		virtual void				SetPath(const tchar* path);

		virtual bool				Load(void);
		virtual void				Reload(void);
		virtual void				UnLoad(void);

		//! ������Դ
		virtual bool				Save(const tchar* path = NULL);

		//----------------------------------------
		//! �Ƿ����
		virtual bool				IsLoaded(void)const;

		//----------------------------------------
		// ��Դ����
		virtual ResType::eValue		GetResType(void)const;

		//----------------------------------------
		// ��Դ����״̬
		virtual ResState::eValue	GetState(void)const;

		//----------------------------------------
		// �û��Զ�������
		virtual void				SetData(void* pData);
		virtual void*				GetData(void)const;

		virtual void				Release(void);
	public:
		ResourceImpl*	mImpl;
		u32				mRefCount;	// ���ü���
	};
}

#endif _Tian_20121021223414_H_