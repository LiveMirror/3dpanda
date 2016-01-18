#include "ui/IMenu.h"
#include "MenuItemimpl.h"
#include "MenuImpl.h"

namespace panda
{
	IMenuItem::IMenuItem( MenuItemImpl* impl)
		:IPanel(impl)
	{

	}

	IMenuItem* IMenuItem::AddItem( const tstring& text )
	{
		return ((MenuItemImpl*) mImpl)->AddItem(text);
	}

	IMenu::IMenu( IUiManager* manager, MenuImpl* impl )
		:IMenuItem(impl)
	{
		if(NULL != impl)
		{
			impl->OnBindUiMgr((uiManager*)manager);
		}
	}

	void IMenu::ShowMenu( s32 x, s32 y )
	{
		((MenuImpl*)mImpl)->ShowMenu(x, y);
	}
}