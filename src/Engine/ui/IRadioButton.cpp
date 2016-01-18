#include "ui/IRadioButton.h"
#include "RadioButtonImpl.h"

namespace panda
{
	IRadioButton::IRadioButton( void )
		:IControl(new RadioButtonImpl)
	{

	}

	IRadioButton::IRadioButton( RadioButtonImpl* impl )
		:IControl(impl)
	{

	}

	void IRadioButton::Check( void )
	{

	}

	bool IRadioButton::GetChecked( void ) const
	{
		return false;
	}
}