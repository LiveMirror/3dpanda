#include "BillboardRenderImpl.h"
#include "resources/ITexture.h"
#include "../rendersystem/Graph3D.h"

namespace panda
{
	BillboardRenderImpl::BillboardRenderImpl( void )
	{
		mType = ParticleRenderType::Billborad;
	}


	void BillboardRenderImpl::RenderParticle( Particle* p, Graph3D* graph3D )
	{
		graph3D->DrawPanel();
	}
}