#include "TreeViewItemImpl.h"
#include "renderSystem/IGraph2D.h"
#include "resources/ITexture.h"
#include "ui/ITreeView.h"
#include "TreeViewImpl.h"

namespace panda
{
	TreeViewItemImpl::TreeViewItemImpl( void )
		:mIsExpanded(true),
		mIsSelected(false),
		mUserData(NULL),
		mParentItem(NULL)
	{

	}

	s32 TreeViewItemImpl::OnRender( IGraph2D* graph, s32 posY, s32 width, s32 itemHeight, s32 layer)
	{
		s32 totalCount = 1;
		s32 x = 15 * layer + 5;
		s32 y;
		if(mIsSelected)
		{
			graph->DrawRect(0, posY - 1, width, itemHeight + 2, 0x4f2b7fdb, 2);
			graph->FillRect(0, posY, width, itemHeight, 0x8f2b7fdb);
		}

		if(mChilds.empty())
		{
			x += 15;
			graph->DrawString(mFont, x, posY, width - x, itemHeight, mText, 0xffFFffFF, FontFormat::VCENTER);
			
		}
		else
		{
			y = posY + itemHeight / 2;
			graph->FillRect(x - 2, y - 5, 10, 10, 0xff787878);

			if(mIsExpanded)
			{
				graph->DrawLine(x, y, x + 6, y, 0x6f0000FF);
				x += 15;
				graph->DrawString(mFont, x, posY, width - x, itemHeight, mText, 0xffFFffFF, FontFormat::VCENTER);
				TreeViewItemImpl* impl;
				s32 count;
				posY += itemHeight;
				for(u32 i = 0; i < mChilds.size(); i++)
				{
					impl = mChilds[i]->mImpl;
					count = impl->OnRender(graph, posY, width, itemHeight, layer + 1);
					totalCount += count;
					posY += count * itemHeight;
				}
			}
			else
			{
				graph->DrawLine(x, y, x + 6, y, 0x6f0000FF);
				graph->DrawLine(x + 3, y - 3, x + 3, y + 3, 0x6f0000FF);
				x += 15;
				graph->DrawString(mFont, x, posY, width - x, itemHeight, mText, 0xffFFffFF, FontFormat::VCENTER);
			}
		}
		return totalCount;
	}

	ITreeViewItem* TreeViewItemImpl::AddItem( const tstring& text )
	{
		ITreeViewItem* item = new ITreeViewItem;
		item->mImpl->mFont = mFont;
		item->mImpl->mParentItem = mThis;
		item->mImpl->mTreeView = mTreeView;
		item->SetText(text);
		mChilds.push_back(item);
		TreeViewImpl* impl = (TreeViewImpl*)mTreeView->mImpl;
		impl->UpdateScrollValue();
		return item;
	}

	ITreeViewItem* TreeViewItemImpl::GetItemAt( s32 itemHeight, s32& curY, s32 y)
	{
		if (mChilds.empty() || !mIsExpanded)
		{
			return NULL;
		}

		ITreeViewItem* item = NULL;
		for(u32 i = 0; i < mChilds.size(); i++)
		{
			item = mChilds[i];
			if(curY <= y && y < curY + itemHeight)
			{
				return item;
			}
			curY += itemHeight;
			item = item->mImpl->GetItemAt(itemHeight, curY, y);
			if(NULL != item)
			{
				return item;
			}
		}
		return NULL;
	}

	s32 TreeViewItemImpl::GetVisibleCount( void )
	{
		if(!mVisible)
		{
			return 0;
		}
		if (mChilds.empty() || !mIsExpanded)
		{
			return 1;
		}
		s32 count = 1;
		for(u32 i = 0; i < mChilds.size(); i++)
		{
			count += mChilds[i]->mImpl->GetVisibleCount();
		}
		return count;
	}

	void TreeViewItemImpl::SetExpand( bool expand )
	{
		if(expand != mIsExpanded)
		{
			mIsExpanded = expand;
			((TreeViewImpl*)mTreeView->mImpl)->UpdateScrollValue();
		}
	}

	void TreeViewItemImpl::SetVisible( bool visible )
	{
		if (visible != mVisible)
		{
			mVisible = visible;
			((TreeViewImpl*)mTreeView->mImpl)->UpdateScrollValue();
		}
	}
}