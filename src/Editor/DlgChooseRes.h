//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/16 14:46:49_
// 描述:  
//

#ifndef _DLGCHOOSERES_2014416144649_
#define _DLGCHOOSERES_2014416144649_

#include "IPanda.h"
#include "EditorDef.h"
using namespace panda;

namespace editor
{
	class DlgChooseRes
	{
	public:
		DlgChooseRes(void);

		void		Init(IUiManager* uiMgr);

		void		ShowDlg(s32 filter);

	protected:
		void		FindFolder(const tstring& path);
		void		DealFile(const tchar* path);
		
		// 后退到前一个文件夹
		void		GoBack(void);

		bool		OnBackClick(IControl* pCtrl);
		bool		OnNewClick(IControl* pCtrl);
		bool		OnListSelectChanged(IControl* pCtrl);
		bool		OnItemDClick(IControl* pItem);
	public:
		IDialog*		mDlg;
		IListBox*		mLbType;
		IListView*		mLvRes;
		IToolBar*		mToolBar;
		IToolBarItem*	mLbPath;
		IMenu*			mMenu;
		s32				mFilterType;
		ResTexture		mImgFolder;
		ResTexture		mImgMesh;
		ResTexture		mImgMat;
		ResTexture		mImgSkn;
		ResTexture		mImgTer;
		ResTexture		mImgEffect;
		tstring			mCurrentPath;
		EventRes		mOnResChoosed;
	};
}

#endif // _DLGCHOOSERES_2014416144649_