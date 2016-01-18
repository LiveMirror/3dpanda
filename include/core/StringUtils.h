//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/3/8 15:09:35_
// 描述:  
//

#ifndef _STRINGUTILS_201338150935_
#define _STRINGUTILS_201338150935_

#include "Config.h"

namespace panda
{
	class StringUtils
	{
	public:
		static s32  GetLength( const char* str );
		static s32  GetLength( const wchar_t* str );
		static bool Narrow2wide( const char* mbstr, s32 cSizeMbs, OUT std::wstring& vcstr );
		static bool Wide2narrow( const wchar_t* vcstr, s32 cSizeVcs, OUT std::string& mbstr );

		/*---------------------------
		!  convert string to number
		---------------------------*/
		static s32  StrToS32( const tchar* str );
		static s64  StrToS64( const tchar* str );
		static u32  StrToU32( const tchar* str );
		static u64  StrToU64( const tchar* str );
		static f32  StrToF32( const tchar* str );
		static f64  StrToF64( const tchar* str );

		/*---------------------------
		!  convert string to number; return the string of str
		---------------------------*/
		static const tchar*  S32ToStr( s32 value, OUT tstring& str );
		static const tchar*  S64ToStr( s64 value, OUT tstring& str );
		static const tchar*  U32ToStr( u32 value, OUT tstring& str );
		static const tchar*  U64ToStr( u64 value, OUT tstring& str );
		static const tchar*  F32ToStr( f32 value, OUT tstring& str, u32 precision = 6 ); // 最大精度为6.
		static const tchar*  F64ToStr( f64 value, OUT tstring& str, u32 precision = 6 ); // 最大精度为14.

		//! 获得系统最后一次错误的说明
		static void			 GetLastErrorMsg(tstring& msg);
	};
}

#endif // _STRINGUTILS_201338150935_