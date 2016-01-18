#include "ui/IToolBar.h"
#include "ToolBarImpl.h"
#include "ToolBarItemImpl.h"

namespace panda
{
	IToolBarItem::IToolBarItem( void ):IControl(new ToolBarItemImpl)
	{

	}

	IToolBarItem::IToolBarItem( ToolBarItemImpl* impl ):IControl(impl)
	{

	}

	/*************************************** IToolBarToggleButton **************************************************/

#define ImplPtr ((ToolBarToggleButton*)mImpl)

	IToolBarToggleButton::IToolBarToggleButton( ToolBarItemImpl* impl ):IToolBarItem(impl)
	{

	}

	bool IToolBarToggleButton::GetSelected( void )
	{
		return ImplPtr->mSelected;
	}

	void IToolBarToggleButton::SetSelected( bool select )
	{
		ImplPtr->mSelected = select;
	}

	EventCtrl& IToolBarToggleButton::OnSelectChanged( void )
	{
		return ImplPtr->mOnSelectChange;
	}

	/*****************************************************************************************/

#define Ptr ((ToolBarImpl*)mImpl)

	IToolBar::IToolBar( void ):IPanel(new ToolBarImpl)
	{

	}

	IToolBar::IToolBar( ToolBarImpl* impl ):IPanel(impl)
	{

	}

	IToolBarItem* IToolBar::AddToolItem( const tstring& item , IToolBarItem::Type type/* = IToolBarItem::ImageButton*/)
	{
		return Ptr->AddToolItem(item, type);
	}

	u32 IToolBar::GetItemNum( void ) const
	{
		return Ptr->mChilds.size();
	}

	IToolBarItem* IToolBar::GetItem( u32 index ) const
	{
		return Ptr->GetItem(index);
	}

	void IToolBar::RemoveItem( u32 index )
	{

	}

	void IToolBar::RemoveItem( IToolBarItem* item )
	{

	}
}