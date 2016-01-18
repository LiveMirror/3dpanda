////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-2-27 22:38:36
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014227223836_H_
#define	_Tian_2014227223836_H_

#include "ui/IFont.h"
#include <d3dx9.h>
#include "base/Color.h"

namespace panda
{
	/*
	*
	*/
	class Font:public IFont
	{
	public:
		virtual void	MeasureString(tstring& str, Rect& outRect, s32 count = -1);
		virtual void	MeasureChar(tchar c, Rect& outRect);
		void			DrawString(const Rect& r, const tstring& str, Color c, s32 format);

	public:
		ID3DXFont*		mDxFont;
	};
}

#endif _Tian_2014227223836_H_