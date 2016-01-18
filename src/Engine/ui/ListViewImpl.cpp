#include "ListViewImpl.h"
#include "ui/IListView.h"
#include "ListViewItemImpl.h"
#include "uiManager.h"
#include "ui/IScrollBar.h"

namespace panda
{
	ListViewImpl::ListViewImpl( void )
		:mSeletedItem(NULL)
	{
		mTileSize.width = 60;
		mTileSize.height = 60;
	}

	IListViewItem* ListViewImpl::AddItem( const tstring& name )
	{
		IListViewItem* item = new IListViewItem;
		ListViewItemImpl* impl = (ListViewItemImpl*)item->mImpl;
		impl->mParent = (IPanel*)mThis;
		impl->mUiMgr = mUiMgr;
		impl->mFont = mFont;
		impl->mTitle = name;
		impl->SetSize(mTileSize.width, mTileSize.height);
		Vector2Dn pos;
		CalculatePos(mChilds.size(), pos);
		impl->SetPos(pos.x, pos.y);

		mChilds.push_back(item);

		UpdateScrollValue();
		return item;
	}

	void ListViewImpl::CalculatePos( s32 index, Vector2Dn& pos )
	{
		s32 rowCount = (mRect.size.width - 10) / (mTileSize.width + 10);
		if(rowCount == 0)
		{
			rowCount = 1;
		}
		s32 row = index / rowCount;
		s32 col = index % rowCount;
		pos.x = col * (mTileSize.width + 10) + 10;
		pos.y = row * (mTileSize.height + 10) + 10;
	}

	void ListViewImpl::NoticItemSelected( IListViewItem* item )
	{
		if(item != mSeletedItem)
		{
			if(NULL != mSeletedItem)
			{
				((ListViewItemImpl*)mSeletedItem->mImpl)->mSelected = false;
			}
			mSeletedItem = item;
			mOnSelectChanged(mSeletedItem);
		}
		if(NULL != mScrollBar)
		{
			mScrollBar->SetFocus();
		}
	}

	void ListViewImpl::SetItemSize( s32 width, s32 height )
	{
		mTileSize.width = width;
		mTileSize.height = height;
		ReCalculate();
	}

	void ListViewImpl::ReCalculate()
	{
		ListViewItemImpl* impl;
		Vector2Dn pos;

		CtrlList::iterator it = mChilds.begin();
		while(it != mChilds.end())
		{
			impl = (ListViewItemImpl*)(*it)->mImpl;
			CalculatePos(mChilds.size(), pos);
			impl->SetPos(pos.x, pos.y);
			it++;
		}

		UpdateScrollValue();
	}

	void ListViewImpl::SetSize( s32 width, s32 height )
	{
		__super::SetSize(width, height);
		ReCalculate();
	}

	void ListViewImpl::ClearAll( void )
	{
		mSeletedItem = NULL;
		CtrlList::iterator it = mChilds.begin();
		while(it != mChilds.end())
		{
			if(mUiMgr->mMouseOn == *it)
			{
				mUiMgr->mMouseOn = NULL;
			}
			delete (*it);
			it = mChilds.begin();
		}
		mChilds.clear();
		UpdateScrollValue();
	}

	void ListViewImpl::NoticItemDClick( IListViewItem* item )
	{
		mOnDClick(item);
	}
}