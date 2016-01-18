//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/24 10:36:22_
// 描述:  
//

#ifndef _DLGCAMERASET_2014424103622_
#define _DLGCAMERASET_2014424103622_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	class DlgCameraSet
	{
	public:
		DlgCameraSet(void);

		void			InitUI(IUiManager* uiMgr);
		void			ShowDlg(void);

	protected:
		bool			OnMoveChange(IControl* pCtrl);
		bool			OnWheelChange(IControl* pCtrl);
		bool			OnRotateChange(IControl* pCtrl);
	public:
		IDialog*		mDlg;
		ISliderBar*		mMoveStep;
		ILabel*			mLbMove;
		ISliderBar*		mWheelStep;
		ILabel*			mLbWheel;
		ISliderBar*		mRotateStep;
		ILabel*			mLbRotate;
	};
}

#endif // _DLGCAMERASET_2014424103622_