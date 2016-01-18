#include "ui/ISliderBar.h"
#include "sliderbarimpl.h"

#define Ptr	((SliderBarImpl*)mImpl)

namespace panda
{
	ISliderBar::ISliderBar( void )
		:IControl(new SliderBarImpl)
	{

	}

	ISliderBar::ISliderBar( SliderBarImpl* impl )
		:IControl(impl)
	{

	}

	void ISliderBar::SetMaximum( s32 v )
	{
		Ptr->SetMaximun(v);
	}

	s32 ISliderBar::GetMaximum( void ) const
	{
		return Ptr->mMaximun;
	}

	void ISliderBar::SetValue( s32 v )
	{
		Ptr->SetValue(v);
	}

	s32 ISliderBar::GetValue( void ) const
	{
		return Ptr->mValue;
	}


	EventCtrl& ISliderBar::OnValueChanged( void )
	{
		return Ptr->mOnValueChange;
	}

	ISliderBarTag* ISliderBar::AddTag( s32 v, s32 userData /*= 0*/ )
	{
		return Ptr->AddTag(v, userData);
	}

	u32 ISliderBar::GetTagNum( void ) const
	{
		return Ptr->mTags.size();
	}

	ISliderBarTag* ISliderBar::GetTagByValue( s32 v ) const
	{
		return 0;
	}

	ISliderBarTag* ISliderBar::GetTagByIndex( s32 index ) const
	{
		return 0;
	}

	void ISliderBar::RemoveTag( ISliderBarTag* tag )
	{

	}

	void ISliderBar::ClearTags( void )
	{
		Ptr->ClearTags();
	}
}