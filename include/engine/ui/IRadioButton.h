//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/3/10 9:32:41_
// 描述:  
//

#ifndef _IRADIOBUTTON_201431093241_
#define _IRADIOBUTTON_201431093241_

#include "IControl.h"

namespace panda
{
	class RadioButtonImpl;
	class IRadioButton:public IControl
	{
	public:
		IRadioButton(void);
		IRadioButton(RadioButtonImpl* impl);

		virtual void	Check(void);
		virtual bool	GetChecked(void)const;
	};
}

#endif // _IRADIOBUTTON_201431093241_