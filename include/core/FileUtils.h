//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2013/3/8 15:40:47_
// ����:  
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
		// �ļ�
		static bool     FileAssure( const tchar* path );
		static bool     FileIsExist( const tchar* path );
		static bool     FileCreate( const tchar* path );
		static bool     FileRemove( const tchar* path );
		static bool     FileCopy( const tchar* srcPath, const tchar* destPath );

		static bool		FileFind(const tchar* path, const tchar* condition, std::list<tstring>& out);

		

		// �ļ���
		static bool     DirAssure( const tchar* pszDir );
		static bool     DirIsExist( const tchar* path );
		static bool     DirCreate( const tchar* pszDir );
		static bool     DirRemove( const tchar* pszDir );		//! [!WARNING]����ɾ�������ļ���
		static tstring  DirGetCurrent(void);
		static bool     DirSetCurrent( const tchar* pszDir );	//! ���õ�ǰprocess�Ĺ���Ŀ¼
		static const tstring&   DirGetRuningDir(void);			//! ��������ļ����ڵ�λ��
		
		static void		GetFileName(const tstring& path, tstring& name, bool ext = true);
		static void		GetFileFolder(const tstring& path, tstring& name);
		static void		GetFileExtension(const tstring& path, tstring& outStr);
	};
}

#endif // _FILEUTILS_201338154047_