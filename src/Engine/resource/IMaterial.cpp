#include "resources/IMaterial.h"
#include "MaterialImpl.h"
#include "resources/ITexture.h"

#define Ptr ((MaterialImpl*)mImpl)

namespace panda
{
	IMaterial::IMaterial( MaterialImpl* pImpl )
		:IResource(pImpl)
	{

	}

	u16 IMaterial::GetNumTechniques( void )
	{
		return Ptr->GetNumTechniques();
	}

	ITechnique* IMaterial::GetTechnique( u16 index )
	{
		return Ptr->GetTechnique(index);
	}

	ITechnique* IMaterial::CreateTechnique( void )
	{
		return Ptr->CreateTechnique();
	}

	void IMaterial::RemoveTechnique( ITechnique* technique )
	{
		Ptr->RemoveTechnique(technique);
	}

	void IMaterial::SetDiffuseTex( ResTexture tex )
	{
		if(!tex.IsNull())
		{
			tex->Load();
		}
		Ptr->mDiffuseTex = tex;
	}

	ResTexture IMaterial::GetDiffuseTex( void )
	{
		return Ptr->mDiffuseTex;
	}

	void IMaterial::SetNormalMap( ResTexture tex )
	{
		Ptr->mNormalMap = tex;
	}

	ResTexture IMaterial::GetNormalMap( void )
	{
		return Ptr->mNormalMap;
	}

	void IMaterial::SetTextureAlpha( bool enable )
	{
		Ptr->mTextureAlpha = enable;
	}

	bool IMaterial::GetTextureAlpha( void )
	{
		return Ptr->mTextureAlpha;
	}

	MaterialType::eValue IMaterial::GetMaterialType( void ) const
	{
		return Ptr->mMatType;
	}

	const Mtrl& IMaterial::GetMtrl( void ) const
	{
		return Ptr->mMtr;
	}

	void IMaterial::SetMtrl( const Mtrl& m )
	{
		Ptr->mMtr = m;
	}
}