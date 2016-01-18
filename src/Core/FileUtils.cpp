#include "FileUtils.h"
#include <shellapi.h>

namespace panda
{
	bool FileUtils::FileAssure( const tchar* path )
	{
		if(!FileUtils::FileIsExist(path))
		{
			return FileUtils::FileCreate(path);
		}
		return true;
	}

	bool FileUtils::FileIsExist( const tchar* path )
	{
		if(NULL == path)
		{
			return false;
		}
		DWORD r = ::GetFileAttributes(path);
		return 0 == (FILE_ATTRIBUTE_DIRECTORY & r)
			&& 0xFFFFFFFF != r; 
	}

	bool FileUtils::FileCreate( const tchar* path )
	{
		if(NULL == path)
		{
			return false;
		}

		HANDLE h = ::CreateFile( path, 0, FILE_SHARE_WRITE, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL );

		if ( INVALID_HANDLE_VALUE != h )
		{
			::CloseHandle( h );
			return true;
		}
		else
			return false;
	}

	bool FileUtils::FileRemove( const tchar* path )
	{
		return 0 == _tremove(path);
	}

	bool FileUtils::FileCopy( const tchar* srcPath, const tchar* destPath )
	{
		return 0 != CopyFile(srcPath, destPath, false);
	}

	bool FileUtils::FileFind( const tchar* path, const tchar* condition, std::list<tstring>& out )
	{
		return false;
	}

	bool FileUtils::DirAssure( const tchar* pszDir )
	{
		if (!FileUtils::DirIsExist(pszDir))
		{
			FileUtils::DirCreate(pszDir);
			return false;
		}
		return true;
	}

	bool FileUtils::DirIsExist( const tchar* path )
	{
		DWORD r = ::GetFileAttributes(path);
		return 0 != (FILE_ATTRIBUTE_DIRECTORY & r) 
			&& 0xFFFFFFFF != r;
	}

	bool FileUtils::DirCreate( const tchar* pszDir )
	{
		return 1 == ::CreateDirectory(pszDir, NULL);
	}

	bool FileUtils::DirRemove( const tchar* pszDir )
	{
		if(NULL == pszDir) return false;

		tchar	oldDir[MAX_PATH] = {END_STR}, newDir[MAX_PATH] = {END_STR};	// 新旧的目录
		DWORD	dwResult;

		// 获得旧当前目录
		dwResult = ::GetCurrentDirectory( MAX_PATH, oldDir );
		if ( !dwResult || dwResult > MAX_PATH )
			return false;

		// 设置新目录并获得全部路径
		dwResult = SetCurrentDirectory( pszDir );
		if ( !dwResult )
			return false;

		dwResult = GetCurrentDirectory( MAX_PATH, newDir );
		if ( !dwResult || dwResult > MAX_PATH )
			return false;

		// 删除全部文件
		SHFILEOPSTRUCT fileop;
		fileop.hwnd     = NULL;
		fileop.wFunc    = FO_DELETE;
		fileop.fFlags   = FOF_NOCONFIRMATION | FOF_SILENT;
		fileop.pFrom    = newDir;
		fileop.pTo      = NULL;
		fileop.fAnyOperationsAborted    = false;
		fileop.hNameMappings            = NULL;
		fileop.lpszProgressTitle        = TEXT("正在删除文件");
		dwResult = ::SHFileOperation( &fileop );

		::SetCurrentDirectory( oldDir );

		if ( !dwResult )
			return true;

		return false;
	}

	tstring FileUtils::DirGetCurrent( void )
	{
		int n = 0;
		tchar path[MAX_PATH];
		if ( 0 != (n=::GetCurrentDirectory(MAX_PATH, path)) )
		{
			if (n+1 < MAX_PATH)
			{
				path[n] = _T('/');
				path[n+1] = 0;
			}
			return path;
		}
		return _T("");
	}

	bool FileUtils::DirSetCurrent( const tchar* pszDir )
	{
		return 0 != ::SetCurrentDirectory(pszDir);
	}

	const tstring& FileUtils::DirGetRuningDir( void )
	{
		static tstring str;
		static bool once = true;
		if (once)
		{
			TCHAR path[MAX_PATH] = {0};
			GetModuleFileName( GetModuleHandle(NULL), path, MAX_PATH-1);
			str = path;
			str = str.substr(0, str.find_last_of('\\')+1);
			once = false;
		}
		return str;
	}

	void FileUtils::GetFileExtension( const tstring& path, tstring& outStr )
	{
		s32 nIndex = path.find_last_of(_T('.'));
		if(nIndex >= 0)
		{
			outStr = path.substr(nIndex + 1, path.size() - nIndex);
		}
		else
		{
			outStr = _T("");
		}
	}

	void FileUtils::GetFileName( const tstring& path, tstring& name, bool ext/* = true*/)
	{
		s32 nIndex = path.find_last_of(_T('\\'));
		s32 nIndex2 = path.find_last_of(_T('/'));
		nIndex = max(nIndex, nIndex2);

		if(nIndex >= 0)
		{
			name = path.substr(nIndex + 1, path.size() - nIndex);
		}
		else
		{
			name = path;
		}

		if(!ext)
		{
			nIndex = path.find_last_of(_T('.'));
			if(nIndex >= 0)
			{
				name = name.substr(0, nIndex);
			}
		}
	}

	void FileUtils::GetFileFolder( const tstring& path, tstring& name )
	{
		s32 nIndex = path.find_last_of(_T('\\'));
		s32 nIndex2 = path.find_last_of(_T('/'));
		nIndex = max(nIndex, nIndex2);

		if(nIndex >= 0)
		{
			name = path.substr(0, nIndex);
		}
		else
		{
			name = _T("");
		}
	}
}