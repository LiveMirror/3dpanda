//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/14 10:24:34_
// 描述:  
//

#ifndef _TREEVIEWIMPL_2014414102434_
#define _TREEVIEWIMPL_2014414102434_

#include "PanelImpl.h"
#include <vector>

namespace panda
{
	class ITreeViewItem;
	class TreeViewImpl:public PanelImpl
	{
	public:
		TreeViewImpl(void);
		virtual void		Draw(Rect& rect, IGraph2D* graph);
		virtual void		OnRender(IGraph2D* graph);
		
		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseDClick(s32 x, s32 y);
		virtual void		UpdateScrollValue(void);

		ITreeViewItem*		AddItem(const tstring& text);
		ITreeViewItem*		GetItemAt(s32 x, s32 y);
		void				Clear(void);

	public:
		typedef std::vector<ITreeViewItem*>	ItemVector;
		ItemVector		mChilds;
		ITreeViewItem*	mSelectItem;
		ITreeViewItem*	mMouseOnItem;
		s32				mItemHeight;
		EventCtrl		mOnSelectedChange;
	};
}

#endif // _TREEVIEWIMPL_2014414102434_