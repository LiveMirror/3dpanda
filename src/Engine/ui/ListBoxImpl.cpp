#include "ListBoxImpl.h"
#include "ui/IListBox.h"
#include "listboxitemimpl.h"
#include "renderSystem/IGraph2D.h"
#include "ui/IScrollBar.h"

namespace panda
{
	ListBoxImpl::ListBoxImpl( void )
		:mSelIndex(-1)
	{
		mBackColor = 0xaf254e85;
		mRect.size = Size(100, 150);
	}

	IListBoxItem* ListBoxImpl::AddItem( const tstring& text )
	{
		IListBoxItem* item = new IListBoxItem;
		item->mImpl->mFont = mFont;
		item->SetText(text);
		mChilds.push_back(item);
		UpdateScrollValue();
		return item;
	}

	IListBoxItem* ListBoxImpl::InsertItem( const tstring& text, u32 index)
	{
		if(index >= mChilds.size())
		{
			return AddItem(text);
		}
		else
		{
			IListBoxItem* item = new IListBoxItem;
			item->mImpl->mFont = mFont;
			item->SetText(text);
			CtrlVector::iterator it = mChilds.begin();
			it + index;
			mChilds.insert(it, item);
			return item;
		}
	}


	void ListBoxImpl::OnRender( IGraph2D* graph )
	{
		if(!mEnable)
		{
			graph->FillRect(0, mCurY, mRect.size.width, mRect.size.height, 0xaf565656);
		}

		s32 index = 0;
		s32 posY = 0;
		ListBoxItemImpl* impl;
		for(u32 i = 0; i < mChilds.size(); i++)
		{
			impl = mChilds[i]->mImpl;
			if(!impl->mVisible)
			{
				continue;
			}
			if(index == mMouseOnIndex && mMouseOn)
			{
				graph->FillRect(0, posY, mRect.size.width, 25, 0x6f787800);
			}
			if(index == mSelIndex)
			{
				graph->FillRect(0, posY, mRect.size.width, 25, 0x6f000066);
			}
			
			impl->OnRender(graph, posY, mRect.size.width);
			posY += impl->GetItemTotalHeight();
			index++;
		}
	}

	void ListBoxImpl::OnMouseMove( MouseEventArgs& e )
	{
		mMouseOnIndex = (e.y + mCurY) / 25;
	}

	void ListBoxImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);
		s32 sel = mMouseOnIndex;
		if(mMouseOnIndex >= mChilds.size())
		{
			sel = -1;
		}
		if(sel != mSelIndex)
		{
			mSelIndex = sel;
			mOnSelectedChange(mThis);
		}
	}

	IListBoxItem* ListBoxImpl::GetSelItem( void ) const
	{
		if(mSelIndex < 0)
		{
			return NULL;
		}
		return mChilds[mSelIndex];
	}

	IListBoxItem* ListBoxImpl::GetItem( u32 index )const
	{
		if(index >= mChilds.size())
		{
			return NULL;
		}
		else
		{
			return mChilds[index];
		}
	}

	void ListBoxImpl::SetSelItemIndex( s32 index )
	{
		if(index >= mChilds.size())
		{
			return;
		}
		mSelIndex = index;
	}

	void ListBoxImpl::Clear( void )
	{
		mSelIndex = -1;
		mChilds.clear();
		UpdateScrollValue();
	}

	void ListBoxImpl::UpdateScrollValue( void )
	{
		s32 totalY = mChilds.size() * 25;

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

	void ListBoxImpl::RemoveItem( u32 index )
	{
		if(index < mChilds.size())
		{
			CtrlVector::iterator it = mChilds.begin();
			it + index;
			delete *it;
			mChilds.erase(it);
			if(index >= mChilds.size())
			{
				mSelIndex = index - 1;
			}
		}
	}
}