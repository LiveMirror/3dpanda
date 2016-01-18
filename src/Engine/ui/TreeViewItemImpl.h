//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/14 10:37:58_
// 描述:  
//

#ifndef _TREEVIEWITEMIMPL_2014414103758_
#define _TREEVIEWITEMIMPL_2014414103758_

#include "base/Config.h"
#include "resources/ResRefDefine.h"
#include <vector>

namespace panda
{
	class ITreeViewItem;
	class IGraph2D;
	class IFont;
	class ITreeView;

	class TreeViewItemImpl
	{
	public:
		TreeViewItemImpl(void);

		ITreeViewItem*		AddItem(const tstring& text);

		/*
		* 返回绘制的item数量,包括自身,用于父类计算高度
		*/
		virtual s32			OnRender(IGraph2D* graph, s32 posY, s32 width, s32 itemHeight, s32 layer);

		ITreeViewItem*		GetItemAt(s32 itemHeight, s32& curY, s32 y);
		
		/*
		* 返回绘制的item数量,包括自身,用于父类计算高度
		*/
		s32					GetVisibleCount(void);

		void				SetExpand(bool expand);
		void				SetVisible(bool visible);

	public:
		typedef std::vector<ITreeViewItem*>	ItemVector;
		ITreeViewItem*	mThis;
		ItemVector		mChilds;
		IFont*			mFont;
		tstring			mText;
		bool			mIsExpanded;
		bool			mVisible;
		bool			mIsSelected;
		ResTexture		mImage;
		s32				mUserData;
		ITreeViewItem*	mParentItem;
		ITreeView*		mTreeView;
	};
}

#endif // _TREEVIEWITEMIMPL_2014414103758_