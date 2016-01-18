//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/8 14:46:17_
// ����:  �ؼ�֡
//

#ifndef _IKEYFRAME_201458144617_
#define _IKEYFRAME_201458144617_

#include "Base/Config.h"
#include "Base/Vector3D.h"
#include "Base/Quaternion.h"

namespace panda
{
	class KeyFrameImpl;
	class IKeyFrame
	{
	public:
		IKeyFrame(KeyFrameImpl* pImpl);
		virtual ~IKeyFrame(void);

		virtual f32			GetTime(void);

	public:
		KeyFrameImpl*	mImpl;
	};

	class TransformKeyFrameImpl;
	class ITransformKeyFrame:public IKeyFrame
	{
	public:
		ITransformKeyFrame(TransformKeyFrameImpl* pImpl);

		virtual void				SetTranslate(const Vector3Df& trans);
		virtual const Vector3Df&	GetTranslate(void)const;

		virtual void				SetScale(const Vector3Df& scale);
		virtual const Vector3Df&	GetScale(void)const;

		virtual void				SetRotation(const Quaternion& rot);
		virtual const Quaternion&	GetRotation(void)const;
	};
}

#endif // _IKEYFRAME_201458144617_