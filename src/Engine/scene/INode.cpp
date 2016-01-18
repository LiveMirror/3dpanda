#include "scene/INode.h"
#include "NodeImpl.h"

namespace panda
{
	INode::INode( NodeImpl* pImpl )
		:mImpl(pImpl)
	{
		if (NULL != mImpl)
		{
			mImpl->mThisPtr = this;
		}
	}

	INode::~INode( void )
	{
		delete mImpl;
	}

	void INode::SetPosition( const Vector3Df& sPos )
	{
		mImpl->SetPosition(sPos);
	}

	void INode::SetPosition( f32 x, f32 y, f32 z )
	{
		mImpl->SetPosition(x, y, z);
	}

	const Vector3Df& INode::GetPosition( void ) const
	{
		return mImpl->GetPosition();
	}

	void INode::SetRotate( const Quaternion& sRotate )
	{
		mImpl->SetRotate(sRotate);
	}

	const Quaternion& INode::GetRotate( void ) const
	{
		return mImpl->GetRotate();
	}

	void INode::SetScale( const Vector3Df& sScale )
	{
		mImpl->SetScale(sScale);
	}

	const Vector3Df& INode::GetScale( void ) const
	{
		return mImpl->GetScale();
	}

	void INode::RotateByX( f32 fDegrees, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		mImpl->RotateByX(fDegrees, relativeTo);
	}

	void INode::RotateByY( f32 fDegrees, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		mImpl->RotateByY(fDegrees, relativeTo);
	}

	void INode::RotateByZ( f32 fDegrees, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		mImpl->RotateByZ(fDegrees, relativeTo);
	}

	void INode::Rotate( f32 fDegress, const Vector3Df& axis, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		mImpl->Rotate(fDegress, axis, relativeTo);
	}

	void INode::Rotate( const Quaternion& sRotate, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		mImpl->Rotate(sRotate, relativeTo);
	}

	INode* INode::CreateChild( void )
	{
		return mImpl->CreateChild();
	}

	INode* INode::GetParent( void )
	{
		return mImpl->mParent;
	}

	const Matrix44f& INode::GetWorldMatrix( void )
	{
		return mImpl->GetWorldMatrix();
	}

	void INode::Translate( const Vector3Df& d, TransformSpace::eValue relativeTo /*= TransformSpace::TS_PARENT*/ )
	{
		mImpl->Translate(d, relativeTo);
	}

	void INode::SetInitialState( void )
	{

	}

	void INode::ResetToInitialState( void )
	{
		mImpl->ResetToInitialState();
	}

	u32 INode::GetNumChildren( void ) const
	{
		return mImpl->mChildren.size();
	}

	INode* INode::GetChild( u32 index ) const
	{
		return mImpl->GetChild(index);
	}
}