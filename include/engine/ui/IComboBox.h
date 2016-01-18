//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/3/2 11:54:06_
// 描述:  
//

#ifndef _ICOMBOBOX_201432115406_
#define _ICOMBOBOX_201432115406_

#include "IControl.h"

namespace panda
{
	class IListBoxItem;
	class ComboBoxImpl;
	class ENGINE_API IComboBox:public IControl
	{
	public:
		IComboBox(void);
		IComboBox(ComboBoxImpl* impl);
		virtual IListBoxItem*	AddItem(const tstring& text);
		virtual s32				GetItemNum(void)const;
		virtual IListBoxItem*	GetItem(s32 index)const;
		virtual IListBoxItem*	GetSelItem(void)const;
		virtual void			SetSelItem(IListBoxItem* item);
		virtual void			SetSelItem(s32 index);
		virtual void			Clear(void);
		virtual EventCtrl&		OnSelectedChange(void);
		virtual u32				GetNumOfShow(void);
		virtual void			SetNumOfShow(u32 num);
	};
}

#endif // _ICOMBOBOX_201432115406_