#include "ui/IScrollBar.h"
#include "Scrollbarimpl.h"

#define Ptr		((ScrollBarImpl*)mImpl)
namespace panda
{
	IScrollBar::IScrollBar( void )
		:IControl(new ScrollBarImpl)
	{

	}

	IScrollBar::IScrollBar( ScrollBarImpl* impl )
		:IControl(impl)
	{

	}

	void IScrollBar::SetMaximun( s32 v )
	{
		Ptr->SetMaximun(v);
	}

	s32 IScrollBar::GetMaximun( void )
	{
		return Ptr->mMaximun;
	}

	void IScrollBar::SetValue( s32 v )
	{
		Ptr->SetValue(v);
	}

	s32 IScrollBar::GetValue( void )
	{
		return Ptr->mValue;
	}

	EventHandle& IScrollBar::OnValueChange( void )
	{
		return Ptr->mOnValueChange;
	}
}