////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-2-27 22:35:16
// ����:  
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