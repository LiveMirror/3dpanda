#include "particleSystem/IColourAffector.h"
#include "ColourAffectorImpl.h"

#define Ptr		((ColourAffectorImpl*)mImpl)

namespace panda
{
	IColourAffector::IColourAffector( ColourAffectorImpl* impl )
		:IParticleAffector(impl)
	{

	}

	void IColourAffector::SetColor( const Colorf& color )
	{
		Ptr->mAddColor = color;
	}

	const Colorf& IColourAffector::GetColor( void ) const
	{
		return Ptr->mAddColor;
	}
}