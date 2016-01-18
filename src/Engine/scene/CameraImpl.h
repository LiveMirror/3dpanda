//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 10:30:25_
// 描述:  
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

		//! 旋转摄像机
		//! 旋转结果将是增量式
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
		Vector3Df		mPosition;		// 位置
		Vector3Df		mLookAt;
		Vector3Df		mUp;
		Quaternion		mRotation;		// 旋转

		s32				mScreenX;
		s32				mScreenY;

		f32				mFov;
		f32				mFarDistance;
		f32				mNearDistance;
		f32				mAspect;

		Matrix44f		mViewMatrix;	// 视口矩阵
		bool			mIsViewDirty;
		Matrix44f		mProj;			// 投影矩阵
		bool			mIsProDirty;

		Matrix44f		mViewProMatrix;
		bool			mIsViewProDirty;
	};
}

#endif // _CAMERAIMPL_201443103025_