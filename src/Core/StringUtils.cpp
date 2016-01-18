
#include "StringUtils.h"

namespace panda
{
	bool StringUtils::Narrow2wide( const char* mbstr, s32 cSizeMbs, OUT std::wstring& vcstr )
	{
		// check parameters
		if ( NULL == mbstr || !cSizeMbs )
		{
			return false;
		}
		wchar_t* pBuf = new wchar_t[cSizeMbs+1];
		s32 c = MultiByteToWideChar( CP_ACP, MB_PRECOMPOSED, mbstr, cSizeMbs, pBuf, cSizeMbs + 1);
		pBuf[c] = 0;
		vcstr = pBuf;
		delete[] pBuf;
		return ( c != 0 );
	}

	bool StringUtils::Wide2narrow( const wchar_t* vcstr, s32 cSizeVcs, OUT std::string& mbstr )
	{
		// check parameters
		if ( NULL == vcstr || !cSizeVcs )
		{
			return false;
		}
		s32 len = cSizeVcs*2;
		char* pBuf = new char[len+1];
		BOOL r;
		s32 c = WideCharToMultiByte(CP_ACP, WC_NO_BEST_FIT_CHARS, vcstr, cSizeVcs, pBuf, len, "?", &r );
		if (r || c == 0)
		{
			return false;
		}
		pBuf[c] = 0;
		mbstr = pBuf;
		delete[] pBuf;
		return true;
	}

	s32 StringUtils::GetLength( const char* str )
	{
		return strlen(str);
	}

	s32 StringUtils::GetLength( const wchar_t* str )
	{
		return wcslen(str);
	}
	s32 StringUtils::StrToS32( const tchar* str )
	{
		return _ttoi(str);
	}

	s64 StringUtils::StrToS64( const tchar* str )
	{
		return _ttoi64(str);
	}

	u32 StringUtils::StrToU32( const tchar* str )
	{
		return _tcstoul(str, NULL, 0);
	}

	u64 StringUtils::StrToU64( const tchar* str )
	{
		return _tcstoui64(str, NULL, 0);
	}

	f32 StringUtils::StrToF32( const tchar* str )
	{
		return (f32)_tstof(str);
	}

	f64 StringUtils::StrToF64( const tchar* str )
	{
		return _tstof(str);
	}

	const tchar* StringUtils::S32ToStr( s32 value, OUT tstring& str )
	{
		tchar buf[12] = {0};
		_stprintf_s(buf, 12, _T("%d"), value);
		str = buf;
		return str.c_str();
	}

	const tchar* StringUtils::S64ToStr( s64 value, OUT tstring& str )
	{
		tchar buf[20] = {0};
		_stprintf_s(buf, 20, _T("%lld"), value);
		str = buf;
		return str.c_str();
	}

	const tchar* StringUtils::U32ToStr( u32 value, OUT tstring& str )
	{
		tchar buf[12] = {0};
		_stprintf_s(buf, 12, _T("%u"), value);
		str = buf;
		return str.c_str();
	}

	const tchar* StringUtils::U64ToStr( u64 value, OUT tstring& str )
	{
		tchar buf[20] = {0};
		_stprintf_s(buf, 20, _T("%llu"), value);
		str = buf;
		return str.c_str();
	}

	const tchar* StringUtils::F32ToStr( f32 value, OUT tstring& str, u32 precision /*= 6 */ )
	{
		tchar buf[50] = {0};
		if (precision > 6)  precision = 6;
		if (6 == precision)
			_stprintf_s(buf, 50, _T("%f"), value);
		else
		{
			tstring s;
			StringUtils::U32ToStr(precision, s);
			s = _T("%.") + s + _T("f");
			_stprintf_s(buf, 50, s.c_str(), value);
		}
		str = buf;
		return str.c_str();
	}

	const tchar* StringUtils::F64ToStr( f64 value, OUT tstring& str, u32 precision /*= 6 */ )
	{
		tchar buf[350] = {0};
		if (precision > 14)  precision = 14;
		if (6 == precision)
			_stprintf_s(buf, 350, _T("%lf"), value);
		else
		{
			tstring s;
			StringUtils::U32ToStr(precision, s);
			s = _T("%.") + s + _T("lf");
			_stprintf_s(buf, 350, s.c_str(), value);
		}
		str = buf;
		return str.c_str();
	}

	void StringUtils::GetLastErrorMsg( tstring& msg )
	{
		int error=GetLastError();
		//TCHAR szBuf[80]; 
		LPVOID lpMsgBuf;
		DWORD dw = GetLastError();
		FormatMessage(
			FORMAT_MESSAGE_ALLOCATE_BUFFER | 
			FORMAT_MESSAGE_FROM_SYSTEM,
			NULL,
			dw,
			MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
			(LPTSTR) &lpMsgBuf,
			0, NULL );
		msg = (LPCTSTR)lpMsgBuf;
		//MessageBox((LPCTSTR)lpMsgBuf,_T("¥ÌŒÛÃ· æ"), MB_OK|MB_ICONSTOP);
		LocalFree(lpMsgBuf);
	}
}