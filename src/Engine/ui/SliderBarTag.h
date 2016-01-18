////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-14 21:54:30
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014514215430_H_
#define	_Tian_2014514215430_H_

#include "ui/ISliderBar.h"

namespace panda
{
	/*
	*
	*/
	class SliderBarTag:public ISliderBarTag
	{
	public:
		SliderBarTag(void);

		virtual s32		GetValue(void)const;

		virtual void	SetUserData(s32 data);
		virtual s32		GetUserData(void)const;

		virtual void	SetColor(const Color& c);
		virtual Color	GetColor(void)const;

	public:
		Color		mColor;
		s32			mValue;
		s32			mUserData;
	};
}

#endif _Tian_2014514215430_H_