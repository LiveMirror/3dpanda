#include "TreeViewImpl.h"
#include "ui/ITreeView.h"
#include "TreeViewItemImpl.h"
#include "renderSystem/IGraph2D.h"
#include "ui/IScrollBar.h"
#include "../renderSystem/Graph2D.h"

namespace panda
{
	TreeViewImpl::TreeViewImpl( void )
		:mSelectItem(NULL),
		mMouseOnItem(NULL),
		mItemHeight(20)
	{

	}
	
	void TreeViewImpl::OnRender( IGraph2D* graph )
	{
		TreeViewItemImpl* impl;
		s32 width = mRect.size.width;
		s32 posY = 0;
		s32 count;
		for(u32 i = 0; i < mChilds.size(); i++)
		{
			impl = mChilds[i]->mImpl;
			count = impl->OnRender(graph, posY, width, mItemHeight, 0);
			posY += count * mItemHeight;
			if(posY - mCurY > mRect.size.height)
			{
				return;
			}
		}
	}

	ITreeViewItem* TreeViewImpl::AddItem( const tstring& text )
	{
		ITreeViewItem* item = new ITreeViewItem;
		item->mImpl->mFont = mFont;
		item->mImpl->mTreeView = (ITreeView*)mThis;
		item->SetText(text);
		mChilds.push_back(item);
		UpdateScrollValue();
		return item;
	}

	void TreeViewImpl::OnMouseDown( MouseEventArgs& e)
	{
		__super::OnMouseDown(e);

		ITreeViewItem* item = GetItemAt(e.x, e.y);

		// 判断是否点击展开按钮
		if(item != NULL && item->GetItemNum() > 0)
		{
			s32 layer = 0;
			ITreeViewItem* parent = item->GetParentItem();
			while(NULL != parent)
			{
				layer++;
				parent = parent->GetParentItem();
			}
			s32 butX = layer * 15;
			if(e.x >= butX && e.x <= butX + 15)
			{
				item->Toggle();
				return;
			}
		}

		// 判断是否改变
		if(item != mSelectItem)
		{
			if(NULL != mSelectItem)
			{
				mSelectItem->mImpl->mIsSelected = false;
			}
			mSelectItem = item;
			if(NULL != mSelectItem)
			{
				mSelectItem->mImpl->mIsSelected = true;
			}
			mOnSelectedChange(mThis);
		}
	}

	ITreeViewItem* TreeViewImpl::GetItemAt( s32 x, s32 y )
	{
		ITreeViewItem* item = NULL;
		s32 curY = 0;
		for(u32 i = 0; i < mChilds.size(); i++)
		{
			item = mChilds[i];
			if(curY <= y && y < curY + mItemHeight)
			{
				return item;
			}
			curY += mItemHeight;
			item = item->mImpl->GetItemAt(mItemHeight, curY, y);
			if(NULL != item)
			{
				return item;
			}
		}
		return NULL;
	}

	void TreeViewImpl::OnMouseDClick( s32 x, s32 y )
	{
		ITreeViewItem* item = GetItemAt(x, y);
		// 判断是否点击展开按钮
		if(item != NULL && item->GetItemNum() > 0)
		{
			item->Toggle();
		}
	}

	void TreeViewImpl::UpdateScrollValue( void )
	{
		s32 totalY = 0;
		for(u32 i = 0; i < mChilds.size(); i++)
		{
			totalY += mChilds[i]->mImpl->GetVisibleCount() * mItemHeight;
		}

		if(totalY > mRect.size.height)
		{
			if(NULL == mScrollBar)
			{
				CreateScrollBar();
			}
			mScrollBar->SetVisible(true);
			mScrollBar->SetSize(mScrollBar->GetSize().width, mRect.size.height);
			mScrollBar->SetPos(mRect.size.width -  mScrollBar->GetSize().width, 0);
			mScrollBar->SetMaximun(totalY);
			mScrollBar->SetValue(mScrollBar->GetValue());
			mCurY = mScrollBar->GetValue();
			//mCurY = 0;
			//mScrollBar->SetValue(0);
		}
		else
		{
			if(NULL != mScrollBar)
			{
				mScrollBar->SetVisible(false);
				mCurY = 0;
			}
		}
	}

	void TreeViewImpl::Draw( Rect& rect, IGraph2D* graph )
	{
		// 控件不可见 不绘制
		// 与可见区域不相交，不绘制
		if(!mIsVisible || !rect.Intersect(mRect))
		{
			return;
		}
		Graph2D* g = (Graph2D*)graph;
		
		// 有滚动条,说明需要打开裁剪
		if(NULL != mScrollBar && mScrollBar->GetVisible())
		{
			graph->ScissorEnable(true);
			graph->SetScissor(mRect);
		}
		
		g->PushOffset(mRect.pos);

		Vector2Dn p(0, -mCurY);
		g->PushOffset(p);

		mThis->OnRender(graph);
		
		g->PopOffset(p);

		if(NULL != mScrollBar && mScrollBar->GetVisible())
		{
			mScrollBar->mImpl->Draw(mRect, graph);
			graph->ScissorEnable(false);
		}

		if(mDrawBorder)
		{
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, mBorderColor, mBorderSize);
		}
		g->PopOffset(mRect.pos);
	}

	void TreeViewImpl::Clear( void )
	{
		/*
		* ........
		*/
		mChilds.clear();

		UpdateScrollValue();
	}
}