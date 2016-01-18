#include "Font.h"

namespace panda
{
	void Font::MeasureString( tstring& str, Rect& outRect, s32 count/* = -1*/)
	{
		if(str.empty())
		{
			outRect.size.width = 0;
			outRect.size.height = 0;
			return;
		}

		s32 index = str.size() - 1;
		if(count > 0)
		{
			index = count - 1;
		}

		RECT r;
		// DT_CALCRECT 无法计算最后是空格的字符串
		// 所以这里把最后是空格的字符替换
#if defined(_UNICODE) || defined(UNICODE)
		if(str[index] == _T(' '))
		{
			str[index]  = _T(')');
			mDxFont->DrawTextW(NULL, str.c_str(), count, &r, DT_CALCRECT, 0);
			str[index]  = _T(' ');
		}
		else
		{
			mDxFont->DrawTextW(NULL, str.c_str(), count, &r, DT_CALCRECT, 0);
		}
#else
		if(str[index] == _T(' '))
		{
			str[index]  = _T(')');
			mDxFont->DrawTextA(NULL, str.c_str(), count, &r, DT_CALCRECT, 0);
			str[index]  = _T(' ');
		}
		else
		{
			mDxFont->DrawTextA(NULL, str.c_str(), count, &r, DT_CALCRECT, 0);
		}
#endif
		outRect.pos = Vector2Dn(r.left, r.top);
		outRect.size = Size(r.right - r.left, r.bottom - r.top);
	}

	void Font::MeasureChar( tchar c, Rect& outRect)
	{
		if(c == _T(' '))
		{
			c = _T(')');
		}
		RECT r;
#if defined(_UNICODE) || defined(UNICODE)
		mDxFont->DrawTextW(NULL, &c, 1, &r, DT_CALCRECT, 0);
#else
		mDxFont->DrawTextA(NULL, &c, 1, &r, DT_CALCRECT, 0);
#endif
		outRect.pos = Vector2Dn(r.left, r.top);
		outRect.size = Size(r.right - r.left, r.bottom - r.top);
	}

	void Font::DrawString( const Rect& r, const tstring& str, Color c, s32 format)
	{
		RECT rect;
		rect.left = r.pos.x;
		rect.top = r.pos.y;
		rect.right = r.pos.x + r.size.width;
		rect.bottom = r.pos.y + r.size.height;

#if defined(_UNICODE) || defined(UNICODE)
		mDxFont->DrawTextW(NULL, str.c_str(), -1, &rect, format, c.value);
#else
		mDxFont->DrawTextA(NULL, str.c_str(), 0, &rect, format, c.value);
#endif
	}
}