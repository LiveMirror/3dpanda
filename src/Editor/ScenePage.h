//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/15 17:54:32_
// 描述:  
//

#ifndef _SCENEPAGE_2014415175432_
#define _SCENEPAGE_2014415175432_

#include "IPanda.h"
#include "ILevel.h"
using namespace panda;
#include "IAttrPage.h"
#include <vector>

namespace editor
{
	class SceneView;
	class DlgTerInfo;
	class ScenePage:public IAttrPage
	{
	public:
		ScenePage();
		virtual void	InitUI(ITabPage* page);
		virtual void	OnMouseMove(MouseEventArgs& e);
		virtual void	OnMouseDown(MouseEventArgs& e);
		virtual void	OnMouseUp(MouseEventArgs& e);
	protected:
		void			OnOpenLevel(ILevel* pLevel);
		bool			OnOpenClick(IControl* pCtrl);
		bool			OnNewClick(IControl* pCtrl);
		bool			OnSaveClick(IControl* pCtrl);
		void			RegestView(SceneView* pView);

		void			OnResChoosed(Resource res);
	public:
		typedef std::vector<SceneView*>		ViewList;
		ViewList		mViews;
		IToolBar*		mToolBar;
		ITabCtrl*		mTabCtrl;
		DlgTerInfo*		mDlgTerInfo;
		SceneView*		mCurView;
	};
}

#endif // _SCENEPAGE_2014415175432_