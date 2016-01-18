#include "resources/ITerrainMaterial.h"
#include "resources/IResTerrain.h"
#include "Level.h"

namespace panda
{
	Level::Level( void )
	{

	}

	ResTerrain Level::GetTerrain( void ) const
	{
		return mTerrain;
	}

	ResTerMaterial Level::GetMaterial( void ) const
	{
		return mTerMat;
	}

	void Level::Save( void )
	{

	}

	void Level::Save( const tstring& path )
	{

	}
}