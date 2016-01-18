//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/16 9:10:58_
// 描述:  
//

#ifndef _RESPAGE_201441691058_
#define _RESPAGE_201441691058_

#include "../IAttrPage.h"
#include <map>

namespace editor
{
	class ResView;
	class ResPage:public IAttrPage
	{
	public:
		ResPage(void);
		virtual void	InitUI(ITabPage* page);
		virtual void	OnMouseDown(MouseEventArgs& e);
		virtual void	OnMouseUp(MouseEventArgs& e);
		virtual void	OnMouseMove(MouseEventArgs& e);
		virtual void	OnSelected(IAttrPage* prePage);
		virtual void	OnLostSelected(IAttrPage* curPage);
		void			RegestView(ResType::eValue type, ResView* pView);
	protected:
		bool			OnOpenClick(IControl* pCtrl);
		bool			OnNewClick(IControl* pCtrl);
		bool			OnSaveClick(IControl* pCtrl);
		void			OnResChoosed(Resource res);

		bool			OnNewMat(IControl* pCtrl);
		void			OnMatNameInput(const tstring& name);
		
		bool			OnNewEffect(IControl* pCtrl);
		void			OnEffNameInput(const tstring& name);
	public:
		IUiManager*		mUiMgr;
		IMenu*			mMenu;
		IToolBar*		mToolBar;
		IMeshObject*	mMeshObj;
		ResView*		mCurView;
		MaterialType::eValue	mNewType;
		std::map<s32, ResView*>	mViews;
	};
}

#endif // _RESPAGE_201441691058_