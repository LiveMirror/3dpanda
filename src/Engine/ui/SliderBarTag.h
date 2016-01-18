////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-5-14 21:54:30
// ����:  
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