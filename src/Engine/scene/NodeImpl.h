//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/2 9:43:55_
// 描述:  
//

#ifndef _NODEIMPL_20144294355_
#define _NODEIMPL_20144294355_

#include "base/Vector3D.h"
#include "base/Struct.h"
#include "base/Quaternion.h"

namespace panda
{
	class INode;
	class NodeImpl
	{
	public:
		NodeImpl(void);
		virtual ~NodeImpl(void);

		//! 节点 位置
		void						SetPosition(const Vector3Df& sLocation);
		void						SetPosition(f32 x, f32 y, f32 z);
		const Vector3Df&			GetPosition(void)const;

		virtual void				Translate(const Vector3Df& d, TransformSpace::eValue relativeTo = TransformSpace::TS_PARENT);

		//! 节点 旋转
		void						SetRotate(const Quaternion& sRotate);
		const Quaternion&			GetRotate(void)const;

		//! 节点 缩放
		void						SetScale(const Vector3Df& sScale);
		const Vector3Df&			GetScale(void)const;

		//! 旋转模型
		//! 旋转结果将是增量式
		void						RotateByX(f32 fDegrees, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		void						RotateByY(f32 fDegrees, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		void						RotateByZ(f32 fDegrees, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		void						Rotate(f32 fDegress, const Vector3Df& axis, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		virtual void				Rotate(const Quaternion& sRotate, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);

		void						SetInitialState(void);
		virtual void				ResetToInitialState(void);

		//! 创建子节点
		virtual INode*				CreateChild(void);

		INode*						GetChild(u32 index)const;


		//! 判断节点的世界矩阵是否改变
		bool						IsWorldDirty(s32 ver);

		//! 获取节点的世界变化矩阵
		const Matrix44f&			GetWorldMatrix(void);

		//! 判断父节点的变换矩阵是否改变
		bool						_IsParentDirty(void);

		//! 获取本地变换矩阵
		const Matrix44f&			GetTransformMatrix(void);

		void						RemoveChild(INode* pNode);

	public:
		//! 更新变化矩阵
		void						_UpdateTransformMatrix(void);

	public:
		typedef std::list<INode*>		NodeList;

		INode*			mThisPtr;
		INode*			mParent;			// 父节点
		NodeList		mChildren;			// 孩子节点

		s32				mWorldVer;			// 标记当前变换矩阵的版本号
		s32				mParentWorldVer;	// 父节点的世界变换矩阵版本号
		bool			mWorldDirty;
		Matrix44f		mWorldMat;			// 世界变换矩阵
		bool			mDirty;
		Matrix44f		mTransformMat;		// 本地变换矩阵
		Vector3Df		mPosition;			// 平移
		Quaternion		mRotation;			// 旋转
		Vector3Df		mScale;				// 缩放

		// The initial info to use as a base for keyframe animation
		Vector3Df		mInitialPosition;	// 平移
		Quaternion		mInitialRotation;	// 旋转
		Vector3Df		mInitialScale;		// 缩放

		bool			mVisible;			// 节点是否可见
	};
}

#endif // _NODEIMPL_20144294355_