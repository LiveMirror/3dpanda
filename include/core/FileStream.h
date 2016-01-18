////////////////////////////////////////////////////////
// Copyright(c) 1986-2006, TT, All Rights Reserved
// Author:  Hu Tianzhi
// Created: 2010-8-21 2:44:59
// Describe:二进制文件流
////////////////////////////////////////////////////////

#ifndef	_Tian_201082124459_H_	
#define	_Tian_201082124459_H_

#include "Config.h"

namespace panda
{
	class FileStream
	{
	public:
		FileStream(void);
		~FileStream(void);

		bool	Open(const tchar* strPath, bool bRead = true);

		s32		GetFileSize();
		
		template<typename T>
		void	Write(const T& value)
		{
			Write((void*)&value, sizeof(T));
		}
		void	Write(void* value, u32 nSize);

		void	WriteStr(const tstring& value);

		void	Seek(s32 offset, int origin = SEEK_CUR);
		s32		Tell(void);

		template<typename T>
		bool	Read(T& value)
		{
			return Read((void*)&value, sizeof(T));
		}

		bool	Read(void* value, u32 nSize);
		void	ReadStr(tstring& value);

		const tstring&	GetPath(void)const;

		bool	Eof();


		static void	GetFileName(const tstring& path, tstring& name);
		static void	GetFileFolder(const tstring& path, tstring& name);

		//-----------------------------------------
		//! 获取路径的后缀名
		static void GetFileExtension(const tstring& path, tstring& outStr);

	protected:
		void	_Size();
	protected:
		tstring mPath;
		FILE*	mFile;
		s32		mFileSize;
	};
}

#endif