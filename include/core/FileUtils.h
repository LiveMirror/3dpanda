//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/3/8 15:40:47_
// 描述:  
//

#ifndef _FILEUTILS_201338154047_
#define _FILEUTILS_201338154047_

#include <list>
#include "Config.h"

namespace panda
{
	class FileUtils
	{
	public:
		// 文件
		static bool     FileAssure( const tchar* path );
		static bool     FileIsExist( const tchar* path );
		static bool     FileCreate( const tchar* path );
		static bool     FileRemove( const tchar* path );
		static bool     FileCopy( const tchar* srcPath, const tchar* destPath );

		static bool		FileFind(const tchar* path, const tchar* condition, std::list<tstring>& out);

		

		// 文件夹
		static bool     DirAssure( const tchar* pszDir );
		static bool     DirIsExist( const tchar* path );
		static bool     DirCreate( const tchar* pszDir );
		static bool     DirRemove( const tchar* pszDir );		//! [!WARNING]将会删除整个文件夹
		static tstring  DirGetCurrent(void);
		static bool     DirSetCurrent( const tchar* pszDir );	//! 设置当前process的工作目录
		static const tstring&   DirGetRuningDir(void);			//! 获得运行文件所在的位置
		
		static void		GetFileName(const tstring& path, tstring& name, bool ext = true);
		static void		GetFileFolder(const tstring& path, tstring& name);
		static void		GetFileExtension(const tstring& path, tstring& outStr);
	};
}

#endif // _FILEUTILS_201338154047_