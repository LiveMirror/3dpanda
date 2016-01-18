////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-29 21:20:50
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014429212050_H_
#define	_Tian_2014429212050_H_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	/*
	*
	*/
	class DlgRenderSet
	{
	public:
		DlgRenderSet(void);

		void			InitUI(IUiManager* uiMgr);
		void			ShowDlg(void);
	public:
		IDialog*		mDlg;
		IListBox*		mLbEffects;
	};
}

#endif _Tian_2014429212050_H_