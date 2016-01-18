//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/1 16:58:24_
// ����:  
//

#ifndef _ICAMERA_201441165824_
#define _ICAMERA_201441165824_

#include "Base/Ray.h"
#include "Base/Struct.h"
#include "Base/Quaternion.h"
#include "ISceneObject.h"

namespace panda
{
	class CameraImpl;
	class ICamera:public ISceneObject
	{
	public:
		ICamera(CameraImpl* pImpl);

		virtual void				SetPosition(const Vector3Df& sPos);
		virtual void				SetPosition(f32 x, f32 y, f32 z);
		virtual const Vector3Df&	GetPosition(void);

		virtual void				SetLookAt(const Vector3Df& sPos);
		virtual void				SetLookAt(f32 x, f32 y, f32 z);
		virtual const Vector3Df&	GetLookAt(void);

		virtual void				SetUp(const Vector3Df& sValue);
		virtual void				SetUp(f32 x, f32 y, f32 z);
		virtual const Vector3Df&	GetUp(void);

		virtual void				Walk(const Vector3Df& sVector);
		virtual void				Walk(f32 x, f32 y, f32 z);

		//! ��ת�����
		//! ��ת�����������ʽ
		virtual void				RotateByX(f32 fDegrees);
		virtual void				RotateByY(f32 fDegrees);
		virtual void				RotateByZ(f32 fDegrees);
		virtual void				Rotate(f32 fDegrees, const Vector3Df& axis);
		virtual void				Rotate(const Quaternion& sRotate);

		//----------------------------------------
		//! ���������ĳ���
		virtual Vector3Df			GetDirection(void);

		virtual Vector3Df			GetRightDir(void);

		//����� ��Զ���Ӿ���
		virtual void				SetFarDistance(f32 fDistance);
		virtual f32					GetFarDistance(void)const;

		//����� ������Ӿ���
		virtual void				SetNearDistance(f32 fDistance);
		virtual f32					GetNearDistance(void)const;

		virtual void				SetFov(f32 fov);
		virtual f32					GetFov(void)const;


		virtual Ray					MakeRay(s32 x, s32 y)const;

		virtual void				Release(void);
	};
}

#endif // _ICAMERA_201441165824_