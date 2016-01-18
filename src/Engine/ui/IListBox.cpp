#include "ui/IListBox.h"
#include "Listboximpl.h"
#include "ListboxItemImpl.h"
#include "resources/ITexture.h"

namespace panda
{
	IListBoxItem::IListBoxItem( void )
		:mImpl(new ListBoxItemImpl)
	{

	}

	IListBoxItem::IListBoxItem( ListBoxItemImpl* impl )
		:mImpl(impl)
	{

	}

	void IListBoxItem::SetText( const tstring& text )
	{
		mImpl->mText = text;
	}

	IListBoxItem* IListBoxItem::AddItem( const tstring& text )
	{
		throw 0;
	}

	u32 IListBoxItem::GetItemNum( void ) const
	{
		throw 0;
	}

	IListBoxItem* IListBoxItem::GetItem( u32 index ) const
	{
		throw 0;
	}

	const tstring& IListBoxItem::GetText( void ) const
	{
		return mImpl->mText;
	}

	void IListBoxItem::SetImage( ResTexture img )
	{
		mImpl->mImage = img;
	}

	ResTexture IListBoxItem::GetImage( void ) const
	{
		return mImpl->mImage;
	}

	bool IListBoxItem::GetVisible( void ) const
	{
		return mImpl->mVisible;
	}

	void IListBoxItem::SetVisible( bool visible )
	{
		mImpl->mVisible = visible;
	}

	void IListBoxItem::SetUserData( s32 data )
	{
		mImpl->mUserData = data;
	}

	s32 IListBoxItem::GetUserData( void ) const
	{
		return mImpl->mUserData;
	}

	/*********************************** IListBox ******************************************/
	IListBox::IListBox( void )
		:IPanel(new ListBoxImpl)
	{

	}

	IListBox::IListBox( ListBoxImpl* impl )
		:IPanel(impl)
	{

	}

	IListBoxItem* IListBox::AddItem( const tstring& text )
	{
		return ((ListBoxImpl*)mImpl)->AddItem(text);
	}


	IListBoxItem* IListBox::InsertItem( const tstring& text, u32 index)
	{
		return ((ListBoxImpl*)mImpl)->InsertItem(text, index);
	}


	u32 IListBox::GetItemNum( void ) const
	{
		return ((ListBoxImpl*)mImpl)->mChilds.size();
	}

	IListBoxItem* IListBox::GetItem( u32 index ) const
	{
		return ((ListBoxImpl*)mImpl)->GetItem(index);
	}

	EventCtrl& IListBox::OnSelectedChange( void )
	{
		return ((ListBoxImpl*)mImpl)->mOnSelectedChange;
	}

	s32 IListBox::GetSelItemIndex( void ) const
	{
		return ((ListBoxImpl*)mImpl)->mSelIndex;
	}

	IListBoxItem* IListBox::GetSelItem( void ) const
	{
		return ((ListBoxImpl*)mImpl)->GetSelItem();
	}

	void IListBox::SetSelItemIndex( s32 index )
	{
		((ListBoxImpl*)mImpl)->SetSelItemIndex(index);
	}

	void IListBox::Clear( void )
	{
		((ListBoxImpl*)mImpl)->Clear();
	}

	void IListBox::RemoveItem( u32 index )
	{
		((ListBoxImpl*)mImpl)->RemoveItem(index);
	}
}