#include "FileStream.h"
#include <io.h>

namespace panda
{
	FileStream::FileStream(void):mFile(NULL)
	{
		
	}

	bool FileStream::Open( const tchar* strPath, bool bRead /*= true*/ )
	{
		mPath = strPath;
		if (bRead)
		{
			_tfopen_s(&mFile, strPath, _T("rb"));
			if (NULL == mFile)
			{
				return false;
			}
			_Size();
		}
		else
		{
			_tfopen_s(&mFile, strPath, _T("wb"));
			if (NULL == mFile)
			{
				return false;
			}
		}
		return true;
	}


	FileStream::~FileStream(void)
	{
		if(NULL != mFile)
		{
			fclose(mFile);
		}
	}

	void FileStream::Write( void* value, u32 nSize )
	{
		fwrite(value, nSize, 1, mFile);
	}
	

	void FileStream::WriteStr( const tstring& value )
	{
		u32 size = (u32)value.size();
		size = (size + 1)* sizeof(tchar);

		// 先写入尺寸
		Write(size);
		fwrite(value.c_str(), size, 1, mFile);
	}

	bool FileStream::Read( void* value, u32 nSize )
	{
		return nSize == fread(value, nSize, 1, mFile);
	}

	void FileStream::Seek( s32 offset, int origin /*= SEEK_CUR*/ )
	{
		fseek(mFile, offset, origin);
	}

	void FileStream::ReadStr( tstring& value )
	{
		u32 size;
		Read(size);
		u32 len = size / sizeof(tchar);
		tchar* buffer = new tchar[len + 1];

		fread(buffer, size, 1, mFile);

		value = buffer;
		delete[] buffer;
	}

	int FileStream::GetFileSize()
	{
		return mFileSize;
	}

	bool FileStream::Eof()
	{
		// 因为feof的工作原理,只有超出文件末尾才能判断
		// 所以加上当前位置与文件长度的比较
		return feof(mFile) != 0 || mFileSize == ftell(mFile);
	}

	void FileStream::GetFileName( const tstring& path, tstring& name )
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
	}

	void FileStream::GetFileFolder( const tstring& path, tstring& name )
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

	void FileStream::GetFileExtension( const tstring& path, tstring& outStr )
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

	s32 FileStream::Tell( void )
	{
		return ftell(mFile);
	}

	void FileStream::_Size()
	{
		mFileSize = _filelength(_fileno(mFile));
	}

	const tstring& FileStream::GetPath( void ) const
	{
		return mPath;
	}
}