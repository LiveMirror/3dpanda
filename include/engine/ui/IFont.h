////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-2-27 22:35:16
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014227223516_H_
#define	_Tian_2014227223516_H_

#include "base/Rect.h"

namespace panda
{
	/*
	*
	*/
	class IFont
	{
	public:
		virtual void	MeasureString(tstring& str, Rect& outRect, s32 count = -1) = 0;
		virtual void	MeasureChar(tchar c, Rect& outRect) = 0;
	};
}

#endif _Tian_2014227223516_H_