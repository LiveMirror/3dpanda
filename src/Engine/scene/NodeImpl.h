//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/2 9:43:55_
// ����:  
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

		//! �ڵ� λ��
		void						SetPosition(const Vector3Df& sLocation);
		void						SetPosition(f32 x, f32 y, f32 z);
		const Vector3Df&			GetPosition(void)const;

		virtual void				Translate(const Vector3Df& d, TransformSpace::eValue relativeTo = TransformSpace::TS_PARENT);

		//! �ڵ� ��ת
		void						SetRotate(const Quaternion& sRotate);
		const Quaternion&			GetRotate(void)const;

		//! �ڵ� ����
		void						SetScale(const Vector3Df& sScale);
		const Vector3Df&			GetScale(void)const;

		//! ��תģ��
		//! ��ת�����������ʽ
		void						RotateByX(f32 fDegrees, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		void						RotateByY(f32 fDegrees, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		void						RotateByZ(f32 fDegrees, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		void						Rotate(f32 fDegress, const Vector3Df& axis, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);
		virtual void				Rotate(const Quaternion& sRotate, TransformSpace::eValue relativeTo = TransformSpace::TS_LOCAL);

		void						SetInitialState(void);
		virtual void				ResetToInitialState(void);

		//! �����ӽڵ�
		virtual INode*				CreateChild(void);

		INode*						GetChild(u32 index)const;


		//! �жϽڵ����������Ƿ�ı�
		bool						IsWorldDirty(s32 ver);

		//! ��ȡ�ڵ������仯����
		const Matrix44f&			GetWorldMatrix(void);

		//! �жϸ��ڵ�ı任�����Ƿ�ı�
		bool						_IsParentDirty(void);

		//! ��ȡ���ر任����
		const Matrix44f&			GetTransformMatrix(void);

		void						RemoveChild(INode* pNode);

	public:
		//! ���±仯����
		void						_UpdateTransformMatrix(void);

	public:
		typedef std::list<INode*>		NodeList;

		INode*			mThisPtr;
		INode*			mParent;			// ���ڵ�
		NodeList		mChildren;			// ���ӽڵ�

		s32				mWorldVer;			// ��ǵ�ǰ�任����İ汾��
		s32				mParentWorldVer;	// ���ڵ������任����汾��
		bool			mWorldDirty;
		Matrix44f		mWorldMat;			// ����任����
		bool			mDirty;
		Matrix44f		mTransformMat;		// ���ر任����
		Vector3Df		mPosition;			// ƽ��
		Quaternion		mRotation;			// ��ת
		Vector3Df		mScale;				// ����

		// The initial info to use as a base for keyframe animation
		Vector3Df		mInitialPosition;	// ƽ��
		Quaternion		mInitialRotation;	// ��ת
		Vector3Df		mInitialScale;		// ����

		bool			mVisible;			// �ڵ��Ƿ�ɼ�
	};
}

#endif // _NODEIMPL_20144294355_