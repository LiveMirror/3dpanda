//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/1 17:03:15_
// 描述:  
//

#ifndef _INODE_201441170315_
#define _INODE_201441170315_

#include "Base/Vector3D.h"
#include "Base/Quaternion.h"
#include "Base/Struct.h"

namespace panda
{
	class NodeImpl;
	class INode
	{
	public:
		INode(NodeImpl* pImpl);
		virtual ~INode(void);

		//! 节点 位置
		virtual void				SetPosition(const Vector3Df& sPos);
		virtual void				SetPosition(f32 x, f32 y, f32 z);
		virtual const Vector3Df&	GetPosition(void)const;

		virtual void				Translate(const Vector3Df& d, TransformSpace::eValue relativeTo = TransformSpace::TS_PARENT);

		//! 节点 旋转
		virtual	void				SetRotate(const Quaternion& sRotate);
		virtual const Quaternion&	GetRotate(void)const;

		//! 节点 缩放
		virtual void				SetScale(const Vector3Df& sScale);
		virtual const Vector3Df&	GetScale(void)const;

		//! 旋转模型
		//! 旋转结果将是增量式
		virtual void				RotateByX(f32 fDegrees, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		virtual void				RotateByY(f32 fDegrees, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		virtual void				RotateByZ(f32 fDegrees, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		virtual void				Rotate(f32 fDegress, const Vector3Df& axis, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		virtual void				Rotate(const Quaternion& sRotate, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);

		//! 创建子节点
		virtual INode*				CreateChild(void);

		virtual u32					GetNumChildren(void)const;
		virtual INode*				GetChild(u32 index)const;

		//! 获取节点的绝对变换矩阵
		virtual const Matrix44f&	GetWorldMatrix(void);

		virtual INode*				GetParent(void);

		virtual void				SetInitialState(void);
		virtual void				ResetToInitialState(void);
	public:
		NodeImpl*	mImpl;
	};
}

#endif // _INODE_201441170315_