#include "Billboard.h"

namespace panda
{
	Billboard::Billboard( void )
	{

	}

	void Billboard::SetPosition( const Vector3Df& pos )
	{
		mPos = pos;
	}

	const Vector3Df& Billboard::GetPosition( void ) const
	{
		return mPos;
	}

	void Billboard::SetSize( const Vector2Df& size )
	{
		mSize = size;
	}

	const Vector2Df& Billboard::GetSize( void ) const
	{
		return mSize;
	}

	void Billboard::SetRotation( f32 rotation )
	{
		mRotation = rotation;
	}

	f32 Billboard::GetRotation( void ) const
	{
		return mRotation;
	}
}