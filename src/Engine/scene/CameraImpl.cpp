#include "CameraImpl.h"
#include "Base/Math.h"
#include <d3dx9.h>

namespace panda
{
	CameraImpl::CameraImpl(ISceneMgr* pCreator):SceneObjectImpl(pCreator)
	{
		mUp = Vector3Df(0, 1, 0);
		mRotation = Quaternion(0, Vector3Df(1,0,0));
		mFov = PI * 0.25f;
		mNearDistance = 1.0f;
		mFarDistance = 10000.0f;
		mAspect = 4 / 3;
		mIsViewDirty = true;
		mIsProDirty = true;
		mIsViewProDirty = true;
	}


	CameraImpl::~CameraImpl( void )
	{

	}


	void CameraImpl::SetPos( f32 x, f32 y, f32 z )
	{
		mPosition.x = x;
		mPosition.y = y;
		mPosition.z = z;
		mIsViewDirty = true;
		mIsViewProDirty = true;
	}

	void CameraImpl::SetLookAt( f32 x, f32 y, f32 z )
	{
		mLookAt.x = x;
		mLookAt.y = y;
		mLookAt.z = z;
		mIsViewDirty = true;
		mIsViewProDirty = true;
	}

	void CameraImpl::SetUp( f32 x, f32 y, f32 z )
	{
		mUp.x = x;
		mUp.y = y;
		mUp.z = z;
		mIsViewDirty = true;
		mIsViewProDirty = true;
	}

	void CameraImpl::SetFarDistance( f32 fDistance )
	{
		mFarDistance = fDistance;
		mIsProDirty = true;
		mIsViewProDirty = true;
	}

	void CameraImpl::SetNearDistance( f32 fDistance )
	{
		mNearDistance = fDistance;
		mIsProDirty = true;
		mIsViewProDirty = true;
	}

	Matrix44f& CameraImpl::GetViewMatrix( void )
	{
		if(mIsViewDirty)
		{
			_UpdateViewMatrix();
		}
		return mViewMatrix;
	}

	Matrix44f& CameraImpl::GetProMatrix( void )
	{
		if(mIsProDirty)
		{
			_UpdateProMatrix();
		}
		return mProj;
	}

	void CameraImpl::_UpdateViewMatrix( void )
	{
		// 更新矩阵
		D3DXMatrixLookAtLH((D3DXMATRIX*)&mViewMatrix, 
			(const D3DXVECTOR3 *)&mPosition,
			(const D3DXVECTOR3 *)&mLookAt,
			(const D3DXVECTOR3 *)&mUp);
		mIsViewDirty = false;
	}

	void CameraImpl::_UpdateProMatrix( void )
	{
		// 投影矩阵
		mAspect = (f32)mScreenX / (f32)mScreenY;
		D3DXMatrixPerspectiveFovLH(
			(D3DXMATRIX*)&mProj,
			mFov, 
			mAspect,
			mNearDistance,
			mFarDistance);
		mIsProDirty = false;
	}

	Ray CameraImpl::MakeRay( s32 x, s32 y )
	{
		if(mIsProDirty)
		{
			_UpdateProMatrix();
		}
		if(mIsViewDirty)
		{
			_UpdateViewMatrix();
		}
		Ray ray;

		ray.sDirction.x = ((2.0f * x) / mScreenX - 1)/mProj._11;
		ray.sDirction.y = -((2.0f * y) / mScreenY - 1)/mProj._22;
		ray.sDirction.z = 1.0f;

		// 求摄像机的逆变化矩阵
		D3DXMATRIX m;
		D3DXMatrixInverse(&m, NULL, (const D3DXMATRIX*)&mViewMatrix);

		// 转换到世界坐标系
		D3DXVec3TransformCoord(
			(D3DXVECTOR3*)&ray.sPosition,
			(const D3DXVECTOR3*)&ray.sPosition,
			&m);

		D3DXVec3TransformNormal(
			(D3DXVECTOR3*)&ray.sDirction,
			(const D3DXVECTOR3*)&ray.sDirction,
			&m);

		ray.sDirction.Normalize();

		return ray;
	}

	void CameraImpl::SetFov( f32 fov )
	{
		mFov = fov;
		mIsProDirty = true;
	}

	Matrix44f& CameraImpl::GetViewProMatrix( void )
	{
		if (mIsViewProDirty)
		{
			mViewProMatrix = GetViewMatrix() * GetProMatrix();
			mIsViewProDirty = false;
		}
		return mViewProMatrix;
	}

	void CameraImpl::Move( f32 x, f32 y, f32 z )
	{
		mPosition.x += x;
		mPosition.y += y;
		mPosition.z += z;

		mLookAt.x += x;
		mLookAt.y += y;
		mLookAt.z += z;
		mIsViewDirty = true;
		mIsViewProDirty = true;
	}

	void CameraImpl::RotateByX( f32 fDegrees )
	{
		Vector3Df dir = mLookAt - mPosition;
		Vector3Df xAxis = dir.Cross(mUp);
		xAxis.Normalize();
		Rotate(fDegrees, xAxis);
		//Rotate(fDegrees, Vector3Df::UNIT_X);
	}

	void CameraImpl::RotateByY( f32 fDegrees )
	{
		/*Quaternion q(fDegrees, Vector3Df::UNIT_Y);
		q.Normalize();
		mRotation = q * mRotation;
		Rotate(q);*/
		Vector3Df xAxis = mRotation * Vector3Df::UNIT_Y;
		Rotate(fDegrees, mUp);
		//Rotate(fDegrees, Vector3Df::UNIT_Y);
	}

	void CameraImpl::RotateByZ( f32 fDegrees )
	{
		Vector3Df xAxis = mRotation * Vector3Df::UNIT_Z;
		Rotate(fDegrees, xAxis);
		//Rotate(fDegrees, Vector3Df::UNIT_Z);
	}

	void CameraImpl::Rotate( f32 fDegress, const Vector3Df& axis )
	{
		Vector3Df temp = axis;
		temp.Normalize();
		Quaternion q(fDegress, temp);
		Rotate(q);
	}

	void CameraImpl::Rotate( const Quaternion& rot )
	{
		Quaternion q = rot;
		q.Normalize();

		Vector3Df temp = mLookAt - mPosition;
		Vector3Df t = q * temp;
		mLookAt = t + mPosition;

		//mUp = q * mUp;
		//mUp.Normalize();

		mIsViewDirty = true;
		mIsViewProDirty = true;

		mRotation = rot * mRotation;
	}

	void CameraImpl::SetScreenSize( s32 width, s32 height )
	{
		mScreenX = width;
		mScreenY = height;
		mAspect = (f32)width / (f32)height;
		mIsViewProDirty = true;
	}
}