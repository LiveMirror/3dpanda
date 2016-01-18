//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 11:34:50_
// 描述:  
//

#ifndef _IMATERIAL_201443113450_
#define _IMATERIAL_201443113450_

#include "IResource.h"
#include "ResRefDefine.h"

namespace panda
{
	class ITechnique;
	class MaterialImpl;

	class IMaterial:public IResource
	{
	public:
		IMaterial(MaterialImpl* pImpl);

		//! 材质类型
		virtual MaterialType::eValue	GetMaterialType(void)const;

		virtual u16				GetNumTechniques(void);
		virtual ITechnique*		GetTechnique(u16 index);
		virtual ITechnique*		CreateTechnique(void);
		virtual void			RemoveTechnique(ITechnique* technique);

		//! 漫反射
		virtual	void			SetDiffuseTex(ResTexture tex);
		virtual ResTexture		GetDiffuseTex(void);

		//! 法线贴图
		virtual	void			SetNormalMap(ResTexture tex);
		virtual ResTexture		GetNormalMap(void);

		//! 纹理的aphle Test
		virtual void			SetTextureAlpha(bool enable);
		virtual bool			GetTextureAlpha(void);

		//! 材质属性值
		virtual const Mtrl&		GetMtrl(void)const;
		virtual void			SetMtrl(const Mtrl& m);
	};
}

#endif // _IMATERIAL_201443113450_