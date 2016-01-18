//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2012/11/2 10:30:38_
// ����:  
//

#ifndef _SERIALIZEHELPER_2012112103038_
#define _SERIALIZEHELPER_2012112103038_

#include "FileStream.h"

namespace panda
{
	class SerializeHelper
	{
	public:
		//! ��ȡ�ַ������洢��ʽ��\0��\n��β
		static void		ReadString(FileStream& file, tstring& outStr);


		static void		Narrow2wide(const char* mbstr, s32 cSizeMbs, std::wstring& vcstr);

		//! ogre�Ŀ�ͷ����
		static u16		ReadOgreChunk(FileStream& file);
		static void		RollBackChunk(FileStream& file);
	};
}

#endif // _SERIALIZEHELPER_2012112103038_