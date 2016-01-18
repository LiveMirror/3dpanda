////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-21 23:18:13
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014421231813_H_
#define	_Tian_2014421231813_H_

#include "IPanda.h"
using namespace panda;

namespace editor
{
	class ResView
	{
	public:
		ResView(void);

		virtual void	InitUI(IUiManager* uiMgr);
		virtual void	OnResChoosed(Resource res);

		virtual void	Show(bool show);

		virtual void	OnMouseDown(MouseEventArgs& e);
		virtual void	OnMouseUp(MouseEventArgs& e);
		virtual void	OnMouseMove(MouseEventArgs& e);



		// 保存当前资源
		virtual void	OnSaveClick(void);

		
	public:
		IPanel*			mPanel;
		ISceneNode*		mSceneNode;
	};
}

#endif _Tian_2014421231813_H_