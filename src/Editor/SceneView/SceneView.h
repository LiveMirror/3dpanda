//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/16 15:24:42_
// 描述:  
//

#ifndef _SCENEVIEW_2014516152442_
#define _SCENEVIEW_2014516152442_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	class SceneView
	{
	public:
		virtual void	InitUI(IUiManager* uiMgr, ISceneNode* pNode);
		virtual void	OnOpenTer(ResTerrain ter);

		virtual void	OnMouseMove(MouseEventArgs& e);
		virtual void	OnMouseDown(MouseEventArgs& e);
		virtual void	OnMouseUp(MouseEventArgs& e);
	public:
		tstring			mName;
		ITabPage*		mPage;
	};
}

#endif // _SCENEVIEW_2014516152442_