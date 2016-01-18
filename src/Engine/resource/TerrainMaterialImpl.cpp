#include "TerrainMaterialImpl.h"
#include "Resources/ITexture.h"
#include "ResourceMgr.h"

namespace panda
{
	TerrainMaterialImpl::TerrainMaterialImpl( ResourceMgr* resMgr, RenderSystem* pRenderMgr )
		:MaterialImpl(resMgr, pRenderMgr),
		mDiffuseScale(1)
	{
		mLightDir = Vector3Df(1, -1, -1);
		mMatType = MaterialType::Type_Terrain;
	}

	void TerrainMaterialImpl::SetTexture( u32 index, ResTexture tex )
	{
		if (!tex.IsNull())
		{
			tex->Load();
		}
		if (index < mTextures.size())
		{
			mTextures[index] = tex;
		}
	}

	void TerrainMaterialImpl::RemoveTexture( u32 index )
	{
		if (index < mTextures.size())
		{
			TextureList::iterator itr = mTextures.begin();
			itr += index;
			mTextures.erase(itr);
		}
	}

	void TerrainMaterialImpl::_Save( FileStream& file )
	{
		u32 num = mTextures.size();
		file.Write(num);
		tstring str;
		for(u32 i = 0; i < num; i++)
		{
			str = mTextures[i].img->GetResPath();
			file.WriteStr(str);
		}
	}

	bool TerrainMaterialImpl::_Load( FileStream& file )
	{
		u32 num;
		file.Read(num);
		tstring str;
		ResTexture tex;
		for(u32 i = 0; i < num; i++)
		{
			file.ReadStr(str);
			tex = mResMgr->LoadTexture(str.c_str());
			tex->Load();
			mTextures.push_back(tex);
		}
		return true;
	}

	ResTexture TerrainMaterialImpl::GetTexture( u32 index )
	{
		if (index < mTextures.size())
		{
			return mTextures[index].img;
		}
		return NULL;
	}

	void TerrainMaterialImpl::SetScale( u32 index, f32 scale )
	{
		if (index < mTextures.size())
		{
			mTextures[index].scale = scale;
		}
	}

	f32 TerrainMaterialImpl::GetScale( u32 index )
	{
		if (index < mTextures.size())
		{
			return mTextures[index].scale;
		}
		return 0;
	}
}