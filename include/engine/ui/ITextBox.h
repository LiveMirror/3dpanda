////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-3-2 23:32:08
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_201432233208_H_
#define	_Tian_201432233208_H_

#include "IControl.h"

namespace panda
{
	class TextBoxImpl;
	class ENGINE_API ITextBox:public IControl
	{
	public:
		ITextBox(void);
		ITextBox(TextBoxImpl* impl);

		virtual void	ReplaceSelectedText(const tstring& str);
		virtual void	Select(s32 beginIndex, s32 len);
		virtual void	SelectAll(void);
		virtual void	SetPasswordChar(tchar c);
		//     Scrolls the contents of the control to the current caret position.
		virtual void	ScrollToCaret(void);
		virtual void	SetReadOnly(bool readOnly);

		virtual void	Undo(void);
		virtual void	Copy(void);
		virtual void	Cut(void);
		virtual void	Paste(void);
	};
}

#endif _Tian_201432233208_H_