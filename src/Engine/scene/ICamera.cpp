#include "scene/ICamera.h"
#include "CameraImpl.h"

#define Ptr ((CameraImpl*)mImpl)

namespace panda
{
	ICamera::ICamera( CameraImpl* pImpl )
		:ISceneObject(pImpl)
	{

	}

	void ICamera::SetPosition( const Vector3Df& sPos )
	{
		
		Ptr->SetPos(sPos.x, sPos.y, sPos.z);
	}

	void ICamera::SetPosition( f32 x, f32 y, f32 z )
	{
		
		Ptr->SetPos(x, y, z);
	}

	const Vector3Df& ICamera::GetPosition( void )
	{
		
		return Ptr->mPosition;
	}

	void ICamera::SetLookAt( const Vector3Df& sPos )
	{
		
		Ptr->SetLookAt(sPos.x, sPos.y, sPos.z);
	}

	void ICamera::SetLookAt( f32 x, f32 y, f32 z )
	{
		
		Ptr->SetLookAt(x, y, z);
	}

	const Vector3Df& ICamera::GetLookAt( void )
	{
		
		return Ptr->mLookAt;
	}

	void ICamera::SetUp( const Vector3Df& sValue )
	{
		
		Ptr->SetUp(sValue.x, sValue.y, sValue.z);
	}

	void ICamera::SetUp( f32 x, f32 y, f32 z )
	{
		
		Ptr->SetUp(x, y, z);
	}

	const Vector3Df& ICamera::GetUp( void )
	{
		
		return Ptr->mUp;
	}

	void ICamera::SetFarDistance( f32 fDistance )
	{
		
	}

	f32 ICamera::GetFarDistance( void ) const
	{
		
		return Ptr->mFarDistance;
	}

	void ICamera::SetNearDistance( f32 fDistance )
	{

	}

	f32 ICamera::GetNearDistance( void ) const
	{
		
		return Ptr->mNearDistance;
	}

	Ray ICamera::MakeRay( s32 x, s32 y ) const
	{
		
		return Ptr->MakeRay(x, y);
	}

	void ICamera::SetFov( f32 fov )
	{

	}

	f32 ICamera::GetFov( void ) const
	{
		
		return Ptr->mFov;
	}

	void ICamera::Walk( const Vector3Df& sVector )
	{
		Walk(sVector.x, sVector.y, sVector.z);
	}

	void ICamera::Walk( f32 x, f32 y, f32 z )
	{
		
		Ptr->Move(x,y,z);
	}

	Vector3Df ICamera::GetDirection( void )
	{
		
		return Ptr->mLookAt - Ptr->mPosition;
	}

	void ICamera::Release( void )
	{
		delete this;
	}

	void ICamera::RotateByX( f32 fDegrees )
	{
		
		Ptr->RotateByX(fDegrees);
	}

	void ICamera::RotateByY( f32 fDegrees )
	{
		
		Ptr->RotateByY(fDegrees);
	}

	void ICamera::RotateByZ( f32 fDegrees)
	{
		
		Ptr->RotateByZ(fDegrees);
	}

	void ICamera::Rotate( f32 fDegrees, const Vector3Df& axis )
	{
		
		Ptr->Rotate(fDegrees, axis);
	}

	void ICamera::Rotate( const Quaternion& sRotate )
	{
		
		Ptr->Rotate(sRotate);
	}

	Vector3Df ICamera::GetRightDir( void )
	{
		Vector3Df dir = GetDirection();
		return dir.Cross(GetUp());
	}
}