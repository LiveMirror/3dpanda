#include "ui/ITabCtrl.h"
#include "TabCtrlImpl.h"
#include "tabpageimpl.h"

namespace panda
{
	ITabPage::ITabPage( void )
		:IPanel(new TabPageImpl)
	{

	}

	ITabPage::ITabPage( TabPageImpl* impl )
		:IPanel(impl)
	{

	}

	ITabCtrl::ITabCtrl( void )
		:IPanel(new TabCtrlImpl)
	{

	}

	ITabCtrl::ITabCtrl( TabCtrlImpl* impl )
		:IPanel(impl)
	{

	}

	ITabPage* ITabCtrl::AddPage( const tstring& name )
	{
		return ((TabCtrlImpl*)mImpl)->AddPage(name);
	}

	u32 ITabCtrl::GetPageNum( void ) const
	{
		return ((TabCtrlImpl*)mImpl)->mChilds.size();
	}

	ITabPage* ITabCtrl::GetPage( u32 index ) const
	{
		return ((TabCtrlImpl*)mImpl)->GetPage(index);
	}

	void ITabCtrl::SetSelPage( u32 index )
	{
		((TabCtrlImpl*)mImpl)->mSelectIndex = index;
	}

	ITabPage* ITabCtrl::GetSelPage( void )const
	{
		return ((TabCtrlImpl*)mImpl)->GetSelPage();
	}

	EventCtrl& ITabCtrl::OnSelPageChanged( void )
	{
		return ((TabCtrlImpl*)mImpl)->mOnSelPageChanged;
	}

	s32 ITabCtrl::GetSelIndex( void ) const
	{
		return ((TabCtrlImpl*)mImpl)->mSelectIndex;
	}
}