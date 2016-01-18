//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/20 11:33:09_
// 描述:  
//

#ifndef _DLGBLENDMAT_2014520113309_
#define _DLGBLENDMAT_2014520113309_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	class TerView;
	class DlgBlendMat
	{
	public:
		void			Init(IUiManager* uiMgr);
		void			ShowDlg(void);

	protected:
		bool			OnOkClick(IControl* pCtrl);
		bool			OnCancelClick(IControl* pCtrl);

		bool			OnTexClick(IControl* pCtrl);
		void			OnTextureChoosed(Resource res);
	public:
		IDialog*		mDlg;
		IPictureBox*	mPbImage;
		ITextBox*		mTbSclae;

		bool			mEditor;
		s32				mCurIndex;

		TerView*		mCreater;
	};
}

#endif // _DLGBLENDMAT_2014520113309_