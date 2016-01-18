////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-14 23:26:16
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014514232616_H_
#define	_Tian_2014514232616_H_

#include "IPanda.h"
#include "EditorDef.h"
using namespace panda;

namespace editor
{
	class DlgInput
	{
	public:
		DlgInput(void);
		void				SetTitle(const tstring& title);
		EventString&		OnInputText(void);
	
		void				ShowDlg(void);
		void				ShowDlg(const tstring& text);

		void				InitUI(IUiManager* uiMgr);

	protected:
		bool				OnOkClick(IControl* pCtrl);
	protected:
		EventString			mOnInputText;
		IDialog*			mDlg;
		ITextBox*			mTbInput;
	};
}

#endif _Tian_2014514232616_H_