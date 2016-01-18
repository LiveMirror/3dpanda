////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-15 23:43:51
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014415234351_H_
#define	_Tian_2014415234351_H_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	class DlgTerInfo
	{
	public:
		void		Init(IUiManager* uiMgr);
		void		ShowDlg(void);
	protected:
		bool		OnTexClick(IControl* pCtrl);
		bool		OnOkClick(IControl* pCtrl);
		bool		OnCancelClick(IControl* pCtrl);

		void		OnTextureChoosed(Resource res);
	public:
		IDialog*		mDlgNewTer;
		ITextBox*		mTbWidth;
		ITextBox*		mTbHeight;
		ITextBox*		mTbTileSize;
		ITextBox*		mTbSclae;
		IPictureBox*	mPbImage;
	};
}

#endif _Tian_2014415234351_H_