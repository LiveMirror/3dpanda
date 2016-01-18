//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/25 10:56:38_
// ����:  
//

#ifndef _DLGEVNSET_2014425105638_
#define _DLGEVNSET_2014425105638_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	class DlgEvnSet
	{
	public:
		DlgEvnSet(void);

		void			InitUI(IUiManager* uiMgr);
		void			ShowDlg(void);

	protected:
		bool			OnBtnBlendTimeClick(IControl* pCtrl);
	public:
		IDialog*		mDlg;
		ICheckBox*		mCbLight;
		ITextBox*		mTbBlendTime;
		ILabel*			mLbDepth;
		ISliderBar*		mSbDepth;
	};
}

#endif // _DLGEVNSET_2014425105638_