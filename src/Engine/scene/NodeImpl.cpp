#include "NodeImpl.h"
#include "scene/INode.h"

namespace panda
{
	NodeImpl::NodeImpl()
		:mParent(NULL),
		mWorldVer(0),
		mParentWorldVer(-1),
		mWorldDirty(true),
		mDirty(true)
	{
		mScale.x = 1;
		mScale.y = 1;
		mScale.z = 1;
	}

	NodeImpl::~NodeImpl(void)
	{
		NodeList::iterator itr = mChildren.begin();
		while (itr != mChildren.end())
		{
			delete *itr;
			itr++;
		}
	}


	void NodeImpl::SetPosition( const Vector3Df& sLocation )
	{
		SetPosition(sLocation.x, sLocation.y, sLocation.z);
	}

	void NodeImpl::SetPosition( f32 x, f32 y, f32 z )
	{
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
		mDirty = true;
	}

	const Vector3Df& NodeImpl::GetPosition( void ) const
	{
		return mPosition;
	}

	void NodeImpl::SetRotate( const Quaternion& sRotate )
	{
		mRotation = sRotate;
		mDirty = true;
	}

	const Quaternion& NodeImpl::GetRotate( void ) const
	{
		return mRotation;
	}

	void NodeImpl::SetScale( const Vector3Df& sScale )
	{
		if (sScale.x <= 0.0f || sScale.y <= 0.0f || sScale.z <= 0.0f)
		{
			return;
		}
		mScale = sScale;
		mDirty = true;
	}

	const Vector3Df& NodeImpl::GetScale( void ) const
	{
		return mScale;
	}

	void NodeImpl::RotateByX( f32 fDegrees, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		Rotate(fDegrees, Vector3Df::UNIT_X, relativeTo);
	}

	void NodeImpl::RotateByY( f32 fDegrees, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		Rotate(fDegrees, Vector3Df::UNIT_Y, relativeTo);
	}

	void NodeImpl::RotateByZ( f32 fDegrees, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		Rotate(fDegrees, Vector3Df::UNIT_Z, relativeTo);
	}

	void NodeImpl::Rotate( const Quaternion& sRotate, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		Quaternion qnorm = sRotate;
		qnorm.Normalize();
		switch(relativeTo)
		{
		case TransformSpace::TS_LOCAL:
			{
				mRotation = mRotation * qnorm;
				break;
			}
		case TransformSpace::TS_PARENT:
			{
				mRotation = qnorm * mRotation;
				break;
			}
		case TransformSpace::TS_WORLD:
			{
				break;
			}
		}
		mDirty = true;
	}

	void NodeImpl::Rotate( f32 fDegress, const Vector3Df& axis, TransformSpace::eValue relativeTo /*= TransformSpace::TS_LOCAL*/ )
	{
		Quaternion q(fDegress, axis);
		Rotate(q, relativeTo);
	}

	const Matrix44f& NodeImpl::GetTransformMatrix( void )
	{
		if(mDirty)
		{
			_UpdateTransformMatrix();
		}
		return mTransformMat;
	}

	void NodeImpl::_UpdateTransformMatrix( void )
	{
		mTransformMat = Matrix44f::NormalMat();
		mRotation.GetMatrix(mTransformMat);
		if (mScale != Vector3Df(1.0f, 1.0f, 1.0f))
		{
			Matrix44f smat;
			smat.Scaling(mScale);
			mTransformMat *= smat;
		}
		mTransformMat.Translation(mPosition);
		mDirty = false;
		mWorldDirty = true;
	}

	INode* NodeImpl::CreateChild( void )
	{
		NodeImpl* pImpl = new NodeImpl;
		pImpl->mParent = mThisPtr;
		INode* pNode = new INode(pImpl);
		mChildren.push_back(pNode);
		return pNode;
	}

	void NodeImpl::RemoveChild( INode* pNode )
	{
		if (mThisPtr == pNode->GetParent())
		{
			mChildren.remove(pNode);
			pNode->mImpl->mParent = NULL;
		}
	}

	const Matrix44f& NodeImpl::GetWorldMatrix( void )
	{
		bool isParentDirty = _IsParentDirty();
		if(mDirty || mWorldDirty)
		{
			if(mDirty)
			{
				_UpdateTransformMatrix();
			}
		}
		if (mWorldDirty || isParentDirty)
		{
			if(NULL != mParent)
			{
				mParentWorldVer = mParent->mImpl->mWorldVer;
				mWorldMat = mTransformMat * mParent->GetWorldMatrix();
			}
			else
			{
				mWorldMat = mTransformMat;
			}
			mWorldDirty = false;
			mWorldVer++;
		}
		return mWorldMat;
	}

	bool NodeImpl::_IsParentDirty( void )
	{
		if(NULL == mParent)
		{
			return false;
		}
		return mParent->mImpl->IsWorldDirty(mParentWorldVer);
	}

	bool NodeImpl::IsWorldDirty( s32 ver )
	{
		if(mWorldVer != ver 
			|| mDirty
			|| mWorldDirty
			|| _IsParentDirty())
		{
			return true;
		}
		return false;
	}

	void NodeImpl::Translate( const Vector3Df& d, TransformSpace::eValue relativeTo /*= TransformSpace::TS_PARENT*/ )
	{
		switch(relativeTo)
		{
		case TransformSpace::TS_LOCAL:
			{
				break;
			}
		case TransformSpace::TS_PARENT:
			{
				mPosition += d;
				break;
			}
		case TransformSpace::TS_WORLD:
			{
				if (NULL == mParent)
				{
					mPosition += d;
				}
				else
				{

				}
				break;
			}
		}
		mDirty = true;
	}

	void NodeImpl::SetInitialState( void )
	{
		mInitialPosition = mPosition;
		mInitialRotation = mRotation;
		mInitialScale = mScale;
	}

	void NodeImpl::ResetToInitialState( void )
	{
		mPosition = mInitialPosition;
		mRotation = mInitialRotation;
		mScale = mInitialScale;

		mDirty = true;
	}

	INode* NodeImpl::GetChild( u32 index ) const
	{
		if (index >= mChildren.size())
		{
			return NULL;
		}
		NodeList::const_iterator itr = mChildren.begin();
		for (u32 i = 0; i < index; i++)
		{
			itr++;
		}
		return *itr;
	}
}