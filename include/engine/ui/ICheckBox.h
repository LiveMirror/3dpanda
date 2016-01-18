////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-4 23:49:25
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201434234925_H_
#define	_Tian_201434234925_H_

#include "IControl.h"

namespace panda
{
	class CheckBoxImpl;
	/*
	*
	*/
	class ICheckBox:public IControl
	{
	public:
		ICheckBox(void);
		ICheckBox(CheckBoxImpl* impl);

		virtual EventHandle&	OnCheckedChange(void);

		virtual void			SetChecked(bool checked);
		virtual bool			GetChecked(void)const;
	};
}

#endif _Tian_201434234925_H_