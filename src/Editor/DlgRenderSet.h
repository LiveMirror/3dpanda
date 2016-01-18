////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-4-29 21:20:50
// ����:  
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