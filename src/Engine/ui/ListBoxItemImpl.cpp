#include "ListBoxItemImpl.h"
#include "renderSystem/IGraph2D.h"
#include "resources/ITexture.h"

namespace panda
{
	ListBoxItemImpl::ListBoxItemImpl( void )
		:mItemHeight(25),
		mVisible(true),
		mUserData(0)
	{

	}

	void ListBoxItemImpl::OnRender( IGraph2D* graph, s32 posY, s32 width)
	{
		s32 x = 5;
		if(!mImage.IsNull())
		{
			graph->DrawImage(mImage.Get(), x, posY + 5, mItemHeight - 10, mItemHeight - 10);
			x += mItemHeight - 5;
		}
		graph->DrawString(mFont, x, posY, width - x, mItemHeight, mText, 0xffFFffFF, FontFormat::VCENTER);
	}

	s32 ListBoxItemImpl::GetItemTotalHeight( void )
	{
		return mItemHeight;
	}
}