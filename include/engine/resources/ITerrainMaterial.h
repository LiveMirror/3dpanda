////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-5-16 23:56:58
// ����:  ���β���
////////////////////////////////////////////////////////

#ifndef	_Tian_2014516235658_H_
#define	_Tian_2014516235658_H_

#include "IMaterial.h"

namespace panda
{
	class TerrainMaterialImpl;
	class ITerrainMaterial:public IMaterial
	{
	public:
		ITerrainMaterial(TerrainMaterialImpl* pImpl);

		//! ����ϸ������
		virtual void		SetDetailTex(ResTexture tex);
		virtual ResTexture	GetDetailTex(void);

		virtual void		SetDiffuseScale(f32 scale);
		virtual f32			GetDiffuseScale(void)const;

		virtual void		SetTextureScale(u32 index, f32 scale);
		virtual f32			GetTextureScale(u32 index)const;

		//! ��������
		virtual void		SetTexture(u32 index, ResTexture tex);
		virtual void		AddTexture(ResTexture tex);
		virtual void		RemoveTexture(u32 index);
		virtual u32			GetNumTexture(void);
		virtual ResTexture	GetTexture(u32 index);
	};
}

#endif _Tian_2014516235658_H_