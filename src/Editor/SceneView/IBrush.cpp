#include "IBrush.h"

namespace editor
{
	IBrush::IBrush( void )
		:mRadius(100),
		mInsideRadius(0),
		mValue(2)
	{

	}

	void IBrush::SetRadius( s32 radius )
	{
		mRadius = radius;
	}

	void IBrush::SetInsideRadius( s32 radius )
	{
		mInsideRadius = radius;
	}

	f32 IBrush::GetEffect( f32 ox, f32 oy, f32 x, f32 y )
	{
		f32 len = (ox - x) * (ox - x) + (oy - y) * (oy - y);
		len = math::Sqrt(len);
		if (len <= mInsideRadius)
		{
			return 1;
		}
		else if(len <= mRadius)
		{
			return 1 - len / mRadius;
		}
		return 0;
	}

	s32 IBrush::GetRadius( void )const
	{
		return mRadius;
	}

	s32 IBrush::GetInsideRadius( void ) const
	{
		return mInsideRadius;
	}

	void IBrush::SetValue( f32 v )
	{
		mValue = v;
	}

	f32 IBrush::GetValue( void )
	{
		return mValue;
	}
}