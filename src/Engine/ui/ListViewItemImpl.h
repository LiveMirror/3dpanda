//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/16 9:49:22_
// ����:  
//

#ifndef _TREELISTITEMIMPL_201441694922_
#define _TREELISTITEMIMPL_201441694922_

#include "ControlImpl.h"

namespace panda
{
	class ListViewItemImpl:public ControlImpl
	{
	public:
		ListViewItemImpl(void);
		virtual void		OnRender(IGraph2D* graph);

		virtual void		OnMouseDown(MouseEventArgs& e);
		virtual void		OnMouseDClick(MouseEventArgs& e);
	public:
		bool		mSelected;
		tstring		mTitle;
	};
}

#endif // _TREELISTITEMIMPL_201441694922_