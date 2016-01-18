//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/26 17:33:14_
// 描述:  
//

#ifndef _IBILLBOARDOBJECT_2014526173314_
#define _IBILLBOARDOBJECT_2014526173314_

#include "ISceneObject.h"
#include "base/Vector2D.h"
#include "base/Vector3D.h"
#include "resources/ResRefDefine.h"

namespace panda
{
	class IBillboard
	{
	public:
		virtual void				SetPosition(const Vector3Df& pos) = 0;
		virtual const Vector3Df&	GetPosition(void)const = 0;

		virtual void				SetSize(const Vector2Df& siez) = 0;
		virtual const Vector2Df&	GetSize(void)const = 0;

		//! This rotation is relative to the center of the billboard
		virtual void				SetRotation(f32 rotation) = 0;
		virtual f32					GetRotation(void)const = 0;
	};

	class BillboardObjectImpl;
	class IBillboardObject:public ISceneObject
	{
	public:
		IBillboardObject(BillboardObjectImpl* impl);

		virtual IBillboard*		CreateBillBoard(void);
		virtual u32				GetNumBillBoards(void)const;
		virtual IBillboard*		GetBillBoard(u32 index)const;
		virtual void			RemoveBillBoard(u32 index);

		virtual void			SetMaterial(ResMaterial mat);
		virtual ResMaterial		GetMaterial(void)const;
	};
}

#endif // _IBILLBOARDOBJECT_2014526173314_