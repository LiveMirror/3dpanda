//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/3/8 11:41:19_
// 描述:  
//

#ifndef _CONFIG_201338114119_
#define _CONFIG_201338114119_

#include <Windows.h>
#include <tchar.h>
#include <string>

#define NULL 0

namespace panda
{
	typedef unsigned char       byte;
	typedef unsigned char       u8;
	typedef unsigned short      u16;
	typedef unsigned int		u32;
	typedef unsigned long long  u64;

	typedef char                s8;
	typedef short               s16;
	typedef int					s32;
	typedef long long           s64;

	typedef float               f32;
	typedef double              f64;

	typedef f32					real;

	typedef u32					IPv4;

#if defined(_UNICODE) || defined(UNICODE)
	typedef wchar_t             tchar;
	typedef std::wstring        tstring;
#define END_STR					L'0'
#else
	typedef char                tchar;
#define END_STR					0
	typedef std::string         tstring;
#endif // UNICODE

}

#endif // _CONFIG_201338114119_