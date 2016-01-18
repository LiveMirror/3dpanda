//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 11:34:50_
// ����:  
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

		//! ��������
		virtual MaterialType::eValue	GetMaterialType(void)const;

		virtual u16				GetNumTechniques(void);
		virtual ITechnique*		GetTechnique(u16 index);
		virtual ITechnique*		CreateTechnique(void);
		virtual void			RemoveTechnique(ITechnique* technique);

		//! ������
		virtual	void			SetDiffuseTex(ResTexture tex);
		virtual ResTexture		GetDiffuseTex(void);

		//! ������ͼ
		virtual	void			SetNormalMap(ResTexture tex);
		virtual ResTexture		GetNormalMap(void);

		//! �����aphle Test
		virtual void			SetTextureAlpha(bool enable);
		virtual bool			GetTextureAlpha(void);

		//! ��������ֵ
		virtual const Mtrl&		GetMtrl(void)const;
		virtual void			SetMtrl(const Mtrl& m);
	};
}

#endif // _IMATERIAL_201443113450_