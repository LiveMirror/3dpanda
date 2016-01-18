//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/15 17:10:04_
// 描述:  
//

#ifndef _IATTRPAGE_2014415171004_
#define _IATTRPAGE_2014415171004_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	class IAttrPage
	{
	public:
		IAttrPage(void);
		virtual void	SetNode(ISceneNode* node);
		virtual void	InitUI(ITabPage* page);
		virtual void	OnSelected(IAttrPage* prePage);
		virtual void	OnLostSelected(IAttrPage* curPage);

		virtual void	OnMouseDown(MouseEventArgs& e);
		virtual void	OnMouseUp(MouseEventArgs& e);
		virtual void	OnMouseMove(MouseEventArgs& e);

	public:
		ITabPage*		mPage;
		ISceneNode*		mRootNode;		// 用于挂接各个模块的模型
	};
}

#endif // _IATTRPAGE_2014415171004_