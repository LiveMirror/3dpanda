
////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-5-16 23:51:00
// 描述:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014516235100_H_
#define	_Tian_2014516235100_H_

#include "MaterialImpl.h"
#include <vector>

namespace panda
{
	struct TerTexture
	{
		TerTexture():scale(10){}
		TerTexture(ResTexture tex):img(tex),scale(10){}

		ResTexture	img;
		f32			scale;
	};
	class TerrainMaterialImpl:public MaterialImpl
	{
	public:
		TerrainMaterialImpl(ResourceMgr* resMgr, RenderSystem* pRenderMgr);

		virtual void	_Save(FileStream& file);
		virtual bool	_Load(FileStream& file);

		void			SetTexture(u32 index, ResTexture tex);
		void			SetScale(u32 index, f32 scale);
		void			RemoveTexture(u32 index);
		ResTexture		GetTexture(u32 index);
		f32				GetScale(u32 index);

	public:
		f32				mDiffuseScale;
		ResTexture		mDetailTex;		// 细节纹理
		Vector3Df		mLightDir;
		typedef std::vector<TerTexture>	TextureList;
		TextureList		mTextures;
	};
}

#endif _Tian_2014516235100_H_