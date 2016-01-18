#include "SliderBarTag.h"

namespace panda
{
	SliderBarTag::SliderBarTag( void )
		:mUserData(0),
		mValue(-1),
		mColor(0xff676767)
	{

	}

	s32 SliderBarTag::GetValue( void ) const
	{
		return mValue;
	}

	void SliderBarTag::SetUserData( s32 data )
	{
		mUserData = data;
	}

	s32 SliderBarTag::GetUserData( void ) const
	{
		return mUserData;
	}

	void SliderBarTag::SetColor( const Color& c )
	{
		mColor = c;
	}

	Color SliderBarTag::GetColor( void ) const
	{
		return mColor;
	}
}