#include "BoneImpl.h"
#include <d3dx9.h>
#include "scene/IBone.h"
#include "base/Matrix44.h"

namespace panda
{
	BoneImpl::BoneImpl( IResSkeleton* creater )
		:mCreater(creater),
		mName(_T(""))
	{

	}

	void BoneImpl::AddChild( IBone* pBone )
	{
		BoneImpl* pImpl = (BoneImpl*)pBone->mImpl;
		if(NULL != pBone->GetParent())
		{
			pBone->GetParent()->mImpl->RemoveChild(pBone);
		}
		pImpl->mParent = mThisPtr;
		mChildren.push_back(pBone);
	}

	INode* BoneImpl::CreateChild( void )
	{
		return NULL;
	}

	void BoneImpl::SetBindPose( void )
	{
		SetInitialState();
		const Matrix44f& m = GetWorldMatrix();
		D3DXMatrixInverse((D3DXMATRIX*)&mOffsetTransform, 0, (D3DXMATRIX*)&m);
	}

	void BoneImpl::GetOffsetTransform( Matrix44f& m )
	{
		m = mOffsetTransform * GetWorldMatrix();
	}
}