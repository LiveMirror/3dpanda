#include "ui/ICheckBox.h"
#include "CheckBoxImpl.h"

namespace panda
{
	ICheckBox::ICheckBox( void )
		:IControl(new CheckBoxImpl)
	{

	}

	ICheckBox::ICheckBox( CheckBoxImpl* impl )
		:IControl(impl)
	{

	}

	EventHandle& ICheckBox::OnCheckedChange( void )
	{
		return ((CheckBoxImpl*)mImpl)->mOnCheckedChange;
	}

	void ICheckBox::SetChecked( bool checked )
	{
		((CheckBoxImpl*)mImpl)->mChecked = checked;
	}

	bool ICheckBox::GetChecked( void ) const
	{
		return ((CheckBoxImpl*)mImpl)->mChecked;
	}
}