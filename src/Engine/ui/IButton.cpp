#include "ui/IButton.h"
#include "ButtonImpl.h"

namespace panda
{
	IButton::IButton( void )
		:IControl(new ButtonImpl)
	{

	}

	IButton::IButton( ButtonImpl* impl )
		:IControl(impl)
	{

	}
}