#include "ui/IFoldPanel.h"
#include "FoldPanelImpl.h"

#define ImplPtr		((FoldPageImpl*)mImpl)

namespace panda
{
	IFoldPage::IFoldPage( void )
	{

	}

	IFoldPage::IFoldPage( FoldPageImpl* impl )
	{

	}

	/******************************************* IFoldPanel *********************************************/

#define Ptr		((FoldPanelImpl*)mImpl)

	IFoldPanel::IFoldPanel( void )
		:IPanel(new FoldPanelImpl)
	{

	}

	IFoldPanel::IFoldPanel( FoldPanelImpl* impl )
		:IPanel(impl)
	{

	}

	IFoldPage* IFoldPanel::AddPage( const tstring& name )
	{
		return Ptr->AddPage(name);
	}

	u32 IFoldPanel::GetPageNum( void ) const
	{
		return Ptr->mChilds.size();
	}

	IFoldPage* IFoldPanel::GetPage( u32 index ) const
	{
		throw 0;
	}

	void IFoldPanel::SetSelPage( u32 index )
	{

	}

	s32 IFoldPanel::GetSelIndex( void ) const
	{
		return Ptr->mSelectIndex;
	}

	IFoldPage* IFoldPanel::GetSelPage( void ) const
	{
		throw 0;
	}

	EventCtrl& IFoldPanel::OnSelPageChanged( void )
	{
		throw 0;
	}
}

