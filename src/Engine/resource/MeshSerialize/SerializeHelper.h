//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2012/11/2 10:30:38_
// 描述:  
//

#ifndef _SERIALIZEHELPER_2012112103038_
#define _SERIALIZEHELPER_2012112103038_

#include "FileStream.h"

namespace panda
{
	class SerializeHelper
	{
	public:
		//! 读取字符串，存储方式以\0或\n结尾
		static void		ReadString(FileStream& file, tstring& outStr);


		static void		Narrow2wide(const char* mbstr, s32 cSizeMbs, std::wstring& vcstr);

		//! ogre的块头操作
		static u16		ReadOgreChunk(FileStream& file);
		static void		RollBackChunk(FileStream& file);
	};
}

#endif // _SERIALIZEHELPER_2012112103038_