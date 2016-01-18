#include "scene/IBone.h"
#include "BoneImpl.h"

#define Ptr		((BoneImpl*)mImpl)

namespace panda
{
	IBone::IBone( BoneImpl* pImpl )
		:INode(pImpl)
	{

	}

	void IBone::AddChild( IBone* pBone )
	{
		Ptr->AddChild(pBone);
	}

	u16 IBone::GetHandle( void )const
	{
		return Ptr->mHandle;
	}

	const tstring& IBone::GetName( void )const
	{
		return Ptr->mName;
	}
}