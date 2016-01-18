//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/3/11 16:39:23_
// ����:  
//

#ifndef _LISTBOXITEMIMPL_2014311163923_
#define _LISTBOXITEMIMPL_2014311163923_

#include "base/Rect.h"
#include "ui/CtrlDef.h"
#include "resources/ResRefDefine.h"

namespace panda
{
	class IGraph2D;
	class IFont;
	class ListBoxItemImpl
	{
	public:
		ListBoxItemImpl(void);

		virtual void	OnRender(IGraph2D* graph, s32 posY, s32 width);

		// return the height of the item include it's childs.
		virtual s32		GetItemTotalHeight(void);
	public:
		IFont*			mFont;
		tstring			mText;
		s32				mItemHeight;
		bool			mVisible;
		ResTexture		mImage;
		s32				mUserData;
	};
}

#endif // _LISTBOXITEMIMPL_2014311163923_