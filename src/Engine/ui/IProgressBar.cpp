#include "ui/IProgressBar.h"
#include "progressbarimpl.h"

namespace panda
{
	IProgressBar::IProgressBar( void )
		:IControl(new ProgressBarImpl)
	{

	}

	IProgressBar::IProgressBar( ProgressBarImpl* impl )
		:IControl(impl)
	{

	}

	void IProgressBar::SetValue( f32 v )
	{
		((ProgressBarImpl*)mImpl)->mValue = v;
	}

	f32 IProgressBar::GetValue( void )
	{
		return ((ProgressBarImpl*)mImpl)->mValue;
	}
}