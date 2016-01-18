#include "ui/ITreeView.h"
#include "TreeViewImpl.h"
#include "TreeViewItemImpl.h"

namespace panda
{
	ITreeViewItem::ITreeViewItem( void )
		:mImpl(new TreeViewItemImpl)
	{
		mImpl->mThis = this;
	}

	ITreeView* ITreeViewItem::GetTreeView( void ) const
	{
		throw 0;
	}

	bool ITreeViewItem::IsSelected( void ) const
	{
		return mImpl->mIsSelected;
	}

	bool ITreeViewItem::IsExpanded( void ) const
	{
		return mImpl->mIsExpanded;
	}

	void ITreeViewItem::Expand( void )
	{
		mImpl->SetExpand(true);
	}

	void ITreeViewItem::ExpandAll( void )
	{

	}

	bool ITreeViewItem::GetVisible( void ) const
	{
		return mImpl->mVisible;
	}

	void ITreeViewItem::SetVisible( bool visible )
	{
		
	}

	void ITreeViewItem::SetText( const tstring& text )
	{
		mImpl->mText = text;
	}

	const tstring& ITreeViewItem::GetText( void ) const
	{
		return mImpl->mText;
	}

	s32 ITreeViewItem::GetItemNum( void ) const
	{
		return mImpl->mChilds.size();
	}

	ITreeViewItem* ITreeViewItem::AddItem( const tstring& str )
	{
		return mImpl->AddItem(str);
	}

	ITreeViewItem* ITreeViewItem::InsertItem( const tstring& str, u32 index )
	{
		return NULL;
	}

	void ITreeViewItem::Collapse( void )
	{
		mImpl->SetExpand(false);
	}

	void ITreeViewItem::Toggle( void )
	{
		mImpl->SetExpand(!mImpl->mIsExpanded);
	}

	void ITreeViewItem::SetUserData( s32 data )
	{
		mImpl->mUserData = data;
	}

	s32 ITreeViewItem::GetUserData( void ) const
	{
		return mImpl->mUserData;
	}

	ITreeViewItem* ITreeViewItem::GetParentItem( void ) const
	{
		return mImpl->mParentItem;
	}




	/****************************************  ITreeView *****************************************/

#define Ptr ((TreeViewImpl*)mImpl)

	ITreeView::ITreeView( void )
		:IPanel(new TreeViewImpl)
	{

	}

	ITreeView::ITreeView( TreeViewImpl* impl )
		:IPanel(impl)
	{

	}

	s32 ITreeView::GetItemNum( void ) const
	{
		return Ptr->mChilds.size();
	}

	ITreeViewItem* ITreeView::AddItem( const tstring& str )
	{
		return Ptr->AddItem(str);
	}

	ITreeViewItem* ITreeView::InsertItem( const tstring& str, u32 index )
	{
		throw 0;
	}

	ITreeViewItem* ITreeView::GetItem( u32 index )
	{
		throw 0;
	}

	ITreeViewItem* ITreeView::GetItemAt( s32 x, s32 y )
	{
		return Ptr->GetItemAt(x, y);
	}

	void ITreeView::ExpandAll( void )
	{

	}

	void ITreeView::Clear( void )
	{
		Ptr->Clear();
	}

	EventCtrl& ITreeView::OnSelectedChange( void )
	{
		return Ptr->mOnSelectedChange;
	}

	ITreeViewItem* ITreeView::GetSelected( void )
	{
		return Ptr->mSelectItem;
	}
}

