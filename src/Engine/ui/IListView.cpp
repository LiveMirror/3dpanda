#include "ui/IListView.h"
#include "ListViewImpl.h"
#include "ListViewItemImpl.h"

namespace panda
{

#define ImplPtr		((ListViewItemImpl*)mImpl)

	IListViewItem::IListViewItem( void ):IControl(new ListViewItemImpl)
	{

	}

	bool IListViewItem::GetSelected( void ) const
	{
		return ImplPtr->mSelected;
	}

	void IListViewItem::SetSize( s32 width, s32 height )
	{

	}

	void IListViewItem::SetPos( s32 x, s32 y )
	{

	}

	void IListViewItem::SetTitle( const tstring& title )
	{
		ImplPtr->mTitle = title;
	}

	const tstring& IListViewItem::GetTitle( void ) const
	{
		return ImplPtr->mTitle;
	}

	/***************************************** IListView *********************************************/

#define Ptr		((ListViewImpl*)mImpl)

	IListView::IListView( void ):IPanel(new ListViewImpl)
	{

	}

	IListView::IListView( ListViewImpl* impl ):IPanel(impl)
	{

	}

	IListViewItem* IListView::AddItem( const tstring& name )
	{
		return Ptr->AddItem(name);
	}

	IListViewItem* IListView::GetSelectedItem( void ) const
	{
		return Ptr->mSeletedItem;
	}

	void IListView::SetItemSize( s32 width, s32 height )
	{
		Ptr->SetItemSize(width, height);
	}

	void IListView::ClearAll( void )
	{
		Ptr->ClearAll();
	}
	
	EventCtrl& IListView::OnSelectChanged( void )
	{
		return Ptr->mOnSelectChanged;
	}

	EventCtrl& IListView::OnItemDClick( void )
	{
		return Ptr->mOnDClick;
	}
}