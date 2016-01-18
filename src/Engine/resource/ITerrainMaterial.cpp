#include "resources/ITerrainMaterial.h"
#include "TerrainmaterialImpl.h"
#include "resources/ITexture.h"
#define Ptr ((TerrainMaterialImpl*)mImpl)

namespace panda
{
	ITerrainMaterial::ITerrainMaterial( TerrainMaterialImpl* pImpl )
		:IMaterial(pImpl)
	{

	}

	void ITerrainMaterial::SetDetailTex( ResTexture tex )
	{
		
		if(!tex.IsNull())
		{
			tex->Load();
		}
		Ptr->mDetailTex = tex;
	}

	ResTexture ITerrainMaterial::GetDetailTex( void )
	{
		
		return Ptr->mDetailTex;
	}

	void ITerrainMaterial::SetTexture( u32 index, ResTexture tex )
	{
		
		Ptr->SetTexture(index, tex);
	}

	void ITerrainMaterial::AddTexture( ResTexture tex )
	{
		
		if(!tex.IsNull())
		{
			tex->Load();
		}
		Ptr->mTextures.push_back(tex);
	}

	void ITerrainMaterial::RemoveTexture( u32 index )
	{
		Ptr->RemoveTexture(index);
	}

	u32 ITerrainMaterial::GetNumTexture( void )
	{
		return Ptr->mTextures.size();
	}

	ResTexture ITerrainMaterial::GetTexture( u32 index )
	{
		return Ptr->GetTexture(index);
	}

	void ITerrainMaterial::SetDiffuseScale( f32 scale )
	{
		Ptr->mDiffuseScale = scale;
	}

	f32 ITerrainMaterial::GetDiffuseScale( void ) const
	{
		return Ptr->mDiffuseScale;
	}

	void ITerrainMaterial::SetTextureScale(u32 index, f32 scale )
	{
		Ptr->SetScale(index, scale);
	}

	f32 ITerrainMaterial::GetTextureScale( u32 index ) const
	{
		return Ptr->GetScale(index);
	}
}