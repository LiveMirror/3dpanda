////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-8 23:32:43
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201438233243_H_
#define	_Tian_201438233243_H_

#include "IControl.h"

namespace panda
{
	class ISliderBarTag
	{
	public:
		virtual s32		GetValue(void)const = 0;

		virtual void	SetUserData(s32 data) = 0;
		virtual s32		GetUserData(void)const = 0;

		virtual void	SetColor(const Color& v) = 0;
		virtual Color	GetColor(void)const = 0;
	};

	class SliderBarImpl;
	class ISliderBar:public IControl
	{
	public:
		ISliderBar(void);
		ISliderBar(SliderBarImpl* impl);

		virtual void	SetMaximum(s32 v);
		virtual s32		GetMaximum(void)const;
		virtual void	SetValue(s32 v);
		virtual s32		GetValue(void)const;

		virtual ISliderBarTag*	AddTag(s32 v, s32 userData = 0);
		virtual u32				GetTagNum(void)const;
		virtual ISliderBarTag*	GetTagByValue(s32 v)const;
		virtual ISliderBarTag*	GetTagByIndex(s32 index)const;
		virtual void			RemoveTag(ISliderBarTag* tag);
		virtual void			ClearTags(void);

		virtual EventCtrl&		OnValueChanged(void);
	};
}

#endif _Tian_201438233243_H_