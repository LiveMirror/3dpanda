//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/26 18:00:38_
// 描述:  
//

#ifndef _BILLBOARD_2014526180038_
#define _BILLBOARD_2014526180038_

#include "scene/IBillboardObject.h"

namespace panda
{
	class Billboard:public IBillboard
	{
	public:
		Billboard(void);

		virtual void				SetPosition(const Vector3Df& pos);
		virtual const Vector3Df&	GetPosition(void)const;

		virtual void				SetSize(const Vector2Df& siez);
		virtual const Vector2Df&	GetSize(void)const;

		//! This rotation is relative to the center of the billboard
		virtual void				SetRotation(f32 rotation);
		virtual f32					GetRotation(void)const;

	public:
		Vector3Df		mPos;
		Vector2Df		mSize;
		f32				mRotation;
	};
}

#endif // _BILLBOARD_2014526180038_