#include "renderSystem/ITechnique.h"
#include "TechniqueImpl.h"

namespace panda
{
	ITechnique::ITechnique( TechniqueImpl* pImpl )
		:mImpl(pImpl)
	{

	}

	ITechnique::~ITechnique( void )
	{
		delete mImpl;
	}

	u16 ITechnique::GetNumPasses( void )
	{
		return mImpl->GetNumPasses();
	}

	IPass* ITechnique::GetPass( s16 index )
	{
		return mImpl->GetPass(index);
	}

	IPass* ITechnique::CreatePass( void )
	{
		return mImpl->CreatePass();
	}

	void ITechnique::RemovePass( IPass* pass )
	{
		mImpl->RemovePass(pass);
	}
}

