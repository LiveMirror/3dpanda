//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 10:30:25_
// ����:  
//

#ifndef _CAMERAIMPL_201443103025_
#define _CAMERAIMPL_201443103025_

#include "Base/Vector3D.h"
#include "Base/Quaternion.h"
#include "Base/Matrix44.h"
#include "Base/Ray.h"
#include "Base/Struct.h"
#include "SceneObjectImpl.h"

namespace panda
{
	class CameraImpl:public SceneObjectImpl
	{
	public:
		CameraImpl(ISceneMgr* pCreator);
		virtual ~CameraImpl(void);

		void			SetPos(f32 x, f32 y, f32 z);
		void			SetLookAt(f32 x, f32 y, f32 z);
		void			SetUp(f32 x, f32 y, f32 z);

		void			SetFarDistance(f32 fDistance);
		void			SetNearDistance(f32 fDistance);
		void			SetFov(f32 fov);

		//! ��ת�����
		//! ��ת�����������ʽ
		void			RotateByX(f32 fDegrees);
		void			RotateByY(f32 fDegrees);
		void			RotateByZ(f32 fDegrees);
		void			Rotate(f32 fDegress, const Vector3Df& axis);
		void			Rotate(const Quaternion& sRotate);

		Ray				MakeRay(s32 x, s32 y);

		Matrix44f&		GetViewMatrix(void);
		Matrix44f&		GetProMatrix(void);
		Matrix44f&		GetViewProMatrix(void);

		void			SetScreenSize(s32 width, s32 height);

		void			Move(f32 x, f32 y, f32 z);

		void			_UpdateViewMatrix(void);
		void			_UpdateProMatrix(void);

	public:
		Vector3Df		mPosition;		// λ��
		Vector3Df		mLookAt;
		Vector3Df		mUp;
		Quaternion		mRotation;		// ��ת

		s32				mScreenX;
		s32				mScreenY;

		f32				mFov;
		f32				mFarDistance;
		f32				mNearDistance;
		f32				mAspect;

		Matrix44f		mViewMatrix;	// �ӿھ���
		bool			mIsViewDirty;
		Matrix44f		mProj;			// ͶӰ����
		bool			mIsProDirty;

		Matrix44f		mViewProMatrix;
		bool			mIsViewProDirty;
	};
}

#endif // _CAMERAIMPL_201443103025_