#include "resources/ITexture.h"
#include "TextureImpl.h"

#define Ptr ((TextureImpl*)mImpl)

namespace panda
{
	ITexture::ITexture( TextureImpl* pImpl )
		:IResource(pImpl)
	{

	}

	ITexture::~ITexture( void )
	{

	}

	s32 ITexture::GetWidth( void ) const
	{
		return 0;
	}

	s32 ITexture::GetHeight( void ) const
	{
		return 0;
	}
}