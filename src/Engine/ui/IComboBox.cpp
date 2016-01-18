#include "ui/IComboBox.h"
#include "ComboboxImpl.h"

#define Ptr	((ComboBoxImpl*)mImpl)

namespace panda
{
	IComboBox::IComboBox( void )
		:IControl(new ComboBoxImpl)
	{

	}

	IComboBox::IComboBox( ComboBoxImpl* impl )
		:IControl(impl)
	{

	}

	IListBoxItem* IComboBox::AddItem( const tstring& text )
	{
		return Ptr->AddItem(text);
	}

	s32 IComboBox::GetItemNum( void ) const
	{
		return 0;
	}

	IListBoxItem* IComboBox::GetItem( s32 index ) const
	{
		return NULL;
	}

	IListBoxItem* IComboBox::GetSelItem( void ) const
	{
		return Ptr->mSelItem;
	}

	void IComboBox::SetSelItem( IListBoxItem* item )
	{
		Ptr->SetSelItem(item);
	}

	void IComboBox::SetSelItem( s32 index )
	{
		Ptr->SetSelItem(index);
	}

	void IComboBox::Clear( void )
	{
		Ptr->Clear();
	}

	EventCtrl& IComboBox::OnSelectedChange( void )
	{
		return Ptr->mOnSelChange;
	}

	u32 IComboBox::GetNumOfShow( void )
	{
		return Ptr->mNumOfShow;
	}

	void IComboBox::SetNumOfShow( u32 num )
	{
		Ptr->SetNumOfShow(num);
	}
}