#include "PropertyGridImpl.h"
#include "ui/IPropertyGrid.h"
#include "renderSystem/IGraph2D.h"
#include "propertygriditemimpl.h"

namespace panda
{
	PropertyGridImpl::PropertyGridImpl( void )
		:mItemHeight(25),
		mNameWidth(80)
	{

	}

	void PropertyGridImpl::OnRender( IGraph2D* graph )
	{
		s32 width = mRect.size.width;

		PropertyGridItemImpl* impl;
		s32 y = 0;
		tstring temp;
		Color gray = mBorderColor;
		gray.A /= 2;
		for(u32 i = 0; i < mItems.size(); i++)
		{
			impl = mItems[i]->mImpl;
			graph->DrawString(mFont, 3, y, mNameWidth - 6, mItemHeight, impl->mName, mTextColor, FontFormat::LEFT | FontFormat::VCENTER);
			graph->DrawString(mFont, mNameWidth + 1, y, width - mNameWidth- 2, mItemHeight, impl->mValueStr, mTextColor, FontFormat::LEFT | FontFormat::VCENTER);
			y += mItemHeight;
			graph->DrawLine(0, y, width, y, gray);
		}
		graph->DrawLine(mNameWidth, 0, mNameWidth, y, gray);
	}

	IPropertyGridItemS32* PropertyGridImpl::AddItemS32( const tstring& name )
	{
		IPropertyGridItemS32* item = new IPropertyGridItemS32;
		item->SetName(name);
		_AddItem(item);
		return item;
	}

	IPropertyGridItemF32* PropertyGridImpl::AddItemF32( const tstring& name )
	{
		IPropertyGridItemF32* item = new IPropertyGridItemF32;
		item->SetName(name);
		_AddItem(item);
		return item;
	}

	IPropertyGridItem3F* PropertyGridImpl::AddItem3F( const tstring& name )
	{
		IPropertyGridItem3F* item = new IPropertyGridItem3F;
		item->SetName(name);
		_AddItem(item);
		return item;
	}

	IPropertyGridItem4F* PropertyGridImpl::AddItem4F( const tstring& name )
	{
		IPropertyGridItem4F* item = new IPropertyGridItem4F;
		item->SetName(name);
		_AddItem(item);
		return item;
	}

	IPropertyGridItemString* PropertyGridImpl::AddItemString( const tstring& name )
	{
		IPropertyGridItemString* item = new IPropertyGridItemString;
		item->SetName(name);
		_AddItem(item);
		return item;
	}

	IPropertyGridItemBool* PropertyGridImpl::AddItemBool( const tstring& name )
	{
		IPropertyGridItemBool* item = new IPropertyGridItemBool;
		item->SetName(name);
		_AddItem(item);
		return item;
	}

	void PropertyGridImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);
		u32 index = e.y / mItemHeight;
		mChilds.clear();
		if(index < mItems.size())
		{
			PropertyGridItemImpl* impl = mItems[index]->mImpl;
			IControl* pCtrl = impl->GetEditorCtrl();
			pCtrl->SetSize(mRect.size.width - mNameWidth, mItemHeight);
			pCtrl->SetPos(mNameWidth, index * mItemHeight);
			MouseEventArgs ex;
			AddChild(pCtrl);
			ex = e;
			ex.x = e.x - mNameWidth;
			ex.y = e.y - pCtrl->GetPos().y;
			pCtrl->mImpl->OnMouseDown(ex);
			pCtrl->SetFocus();
		}
	}

	void PropertyGridImpl::_AddItem( IPropertyGridItem* item )
	{
		item->mImpl->mParent = this;
		item->mImpl->mEditorCtrl->SetUserData((s32)item);
		item->mImpl->OnBindUiMgr(mUiMgr);
		mItems.push_back(item);
	}

	void PropertyGridImpl::ClearItem( void )
	{
		GridItemList::iterator it = mItems.begin();
		while (it != mItems.end())
		{
			delete *it;
			it++;
		}
		mItems.clear();
	}
}