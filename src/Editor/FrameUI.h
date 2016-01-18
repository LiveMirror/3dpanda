////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-14 22:01:46
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014414220146_H_
#define	_Tian_2014414220146_H_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	class IAttrPage;
	class DlgCameraSet;
	class DlgEvnSet;
	class DlgRenderSet;
	/*
	*
	*/
	class FrameUI
	{
	public:
		FrameUI(IUiManager* uiMgr, IPanda* engine);

		void			AddAttriPage(const tstring& name, IAttrPage* page);
		void			InitUI(void);
	protected:
		void			InitToolBar(void);
		void			InitTabCtrl(void);

		bool			OnSelectedChanged(IControl* pCtrl);
		bool			OnPageSelChanged(IControl* pCtrl);
		bool			OnCameraSetClick(IControl* pCtrl);
		bool			OnEvnSetClick(IControl* pCtrl);
		bool			OnRenderSetClick(IControl* pCtrl);
		bool			OnGridClick(IControl* pCtrl);

		bool			OnMouseWheel(IControl* pCtrl, MouseEventArgs& e);
		bool			OnMouseMove(IControl* pCtrl, MouseEventArgs& e);
		bool			OnMouseDown(IControl* pCtrl, MouseEventArgs& e);
		bool			OnMouseUp(IControl* pCtrl, MouseEventArgs& e);
	public:
		IUiManager*		mUiMgr;
		IPanda*			mEngine;
		IPanel*			mBackGround;
		IToolBar*		mToolBar;
		ITabPage*		mOldPage;
		ITabCtrl*		mTabCtrl;
		Vector2Dn		mOldPoint;

		DlgCameraSet*	mDlgCameraSet;
		DlgEvnSet*		mDlgEvnSet;
		DlgRenderSet*	mDlgRenderSet;
		IToolBarToggleButton*	mSelectBtn;
	};
}

#endif _Tian_2014414220146_H_