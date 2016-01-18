//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/28 10:48:38_
// 描述:  
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
		ResourceMgr*		mResMgr;	// 资源管理器
		bool				mIsCreater;	// 是否为自定义创建的资源
		IResource*			mThis;		// 指向自己的指针
		tstring				mPath;		// 资源路径
		ResState::eValue	mResState;	// 资源的加载状态
		ResType::eValue		mResType;	// 资源类型
		void*				mUserData;	// 用户绑定数据
	};
}

#endif // _RESOURCEIMPL_2014228104838_