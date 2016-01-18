#include "ToolBarImpl.h"
#include "ui/IToolBar.h"
#include "ToolBarItemImpl.h"

namespace panda
{
	ToolBarImpl::ToolBarImpl(void)
		:mCurWidth(1)
	{
		mRect.size.height = 25;
	}

	IToolBarItem* ToolBarImpl::AddToolItem( const tstring& text, IToolBarItem::Type type/* = IToolBarItem::ImageButton*/)
	{
		ToolBarItemImpl* impl;
		IToolBarItem* item = NULL;
		switch(type)
		{
		case IToolBarItem::ImageButton:
			{
				impl = new ToolBarButtonItemImpl;
				item = new IToolBarItem(impl);
				break;
			}
		case IToolBarItem::ToggleButton:
			{
				impl = new ToolBarToggleButton;
				item = (IToolBarItem*)new IToolBarToggleButton(impl);
				break;
			}
		case IToolBarItem::Label:
			{
				impl = new ToolBarItemImpl;
				item = new IToolBarItem(impl);
				break;
			}
		case IToolBarItem::Separator:
			{
				impl = new ToolBarSeparatorItemImpl;
				item = new IToolBarItem(impl);
				break;
			}
		}
		impl->mFont = mFont;
		impl->mUiMgr = mUiMgr;
		impl->mParent = (IPanel*)mThis;
		item->SetText(text);
		mChilds.push_back(item);

		impl->CalculateSize(mRect.size.height);
		item->SetPos(mCurWidth, 1);
		mCurWidth += item->GetSize().width + 2;
		return item;
	}

	IToolBarItem* ToolBarImpl::GetItem( u32 index )const
	{
		if(index < mChilds.size())
		{
			return (IToolBarItem*)mChilds[index];
		}
		return NULL;
	}

	void ToolBarImpl::RemoveItem( u32 index )
	{
		if(index < mChilds.size())
		{
			CtrlList::iterator it = mChilds.begin();
			it + index;
			mChilds.erase(it);
		}
	}

	void ToolBarImpl::RemoveItem( IToolBarItem* item )
	{
		CtrlList::iterator it = mChilds.begin();
		while(it != mChilds.end())
		{
			if(item == (IToolBarItem*)*it)
			{
				mChilds.erase(it);
				return;
			}
			it++;
		}
	}
}