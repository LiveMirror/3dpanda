//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/2/28 10:48:38_
// ����:  
//

#ifndef _RESOURCEIMPL_2014228104838_
#define _RESOURCEIMPL_2014228104838_

#include "base/Config.h"
#include "base/Struct.h"

namespace panda
{
	class IResource;
	class ResourceMgr;
	class ResourceImpl
	{
	public:
		ResourceImpl(ResourceMgr* resMgr);
		virtual ~ResourceImpl(void);

		virtual void	BindThis(IResource* ptr);

		bool	Load(void);
		void	UnLoad(void);
		void	Save(const tchar* path = NULL);
		virtual bool	_Load(void) = 0;
		virtual void	_UnLoad(void) = 0;
		virtual void	_Save(const tchar* path) = 0;

	public:
		ResourceMgr*		mResMgr;	// ��Դ������
		bool				mIsCreater;	// �Ƿ�Ϊ�Զ��崴������Դ
		IResource*			mThis;		// ָ���Լ���ָ��
		tstring				mPath;		// ��Դ·��
		ResState::eValue	mResState;	// ��Դ�ļ���״̬
		ResType::eValue		mResType;	// ��Դ����
		void*				mUserData;	// �û�������
	};
}

#endif // _RESOURCEIMPL_2014228104838_