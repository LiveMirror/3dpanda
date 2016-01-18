////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2012-10-21 22:34:14
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_20121021223414_H_
#define	_Tian_20121021223414_H_

#include "Base/Config.h"
#include "Base/Struct.h"

namespace panda
{
	class ResourceImpl;
	/*
	* 资源
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

		//! 保存资源
		virtual bool				Save(const tchar* path = NULL);

		//----------------------------------------
		//! 是否加载
		virtual bool				IsLoaded(void)const;

		//----------------------------------------
		// 资源类型
		virtual ResType::eValue		GetResType(void)const;

		//----------------------------------------
		// 资源加载状态
		virtual ResState::eValue	GetState(void)const;

		//----------------------------------------
		// 用户自定义数据
		virtual void				SetData(void* pData);
		virtual void*				GetData(void)const;

		virtual void				Release(void);
	public:
		ResourceImpl*	mImpl;
		u32				mRefCount;	// 引用计数
	};
}

#endif _Tian_20121021223414_H_