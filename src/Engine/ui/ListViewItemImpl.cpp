#include "ListViewItemImpl.h"
#include "renderSystem/IGraph2D.h"
#include "ListViewImpl.h"
#include "ui/IPanel.h"

namespace panda
{
	ListViewItemImpl::ListViewItemImpl( void )
		:mSelected(false)
	{
		//mDrawBorder = false;
	}

	void ListViewItemImpl::OnRender( IGraph2D* graph )
	{
		graph->FillRect(0, 0, mRect.size.width, mRect.size.height, mBackColor);
		
		if(mSelected)
		{
			graph->FillRect(0, 0, mRect.size.width, mRect.size.height, mBackColor, mBackColor2);
		}

		if(!mBackImage.IsNull())
		{
			graph->DrawImage(mBackImage.Get(), 10, 0, mRect.size.width - 20, mRect.size.height - 20);
		}

		graph->DrawString(mFont, 0, mRect.size.height - 20, mRect.size.width, 20, mTitle, mTextColor);

		if(mMouseOn)
		{
			Color temp = mBorderColor;
			temp.A /= 2;
			graph->DrawRect(-1, -1, mRect.size.width + 2, mRect.size.height + 2, temp, 2);
		}
	}

	void ListViewItemImpl::OnMouseDown( MouseEventArgs& e )
	{
		mSelected = true;
		((ListViewImpl*)mParent->mImpl)->NoticItemSelected((IListViewItem*)mThis);
	}

	void ListViewItemImpl::OnMouseDClick( MouseEventArgs& e )
	{
		((ListViewImpl*)mParent->mImpl)->NoticItemDClick((IListViewItem*)mThis);
	}
}