#include "resources/IResTerrain.h"
#include "ResTerrainImpl.h"

#define Ptr		((ResTerrainImpl*)mImpl)

namespace panda
{
	IResTerrain::IResTerrain( ResTerrainImpl* pImpl )
		:IResMesh(pImpl)
	{

	}

	s32 IResTerrain::GetWidth( void )
	{
		return Ptr->mWidth;
	}

	s32 IResTerrain::GetHeight( void )
	{
		return Ptr->mHeight;
	}

	f32 IResTerrain::GetHeight( f32 x, f32 y )
	{
		return Ptr->GetHeight(x, y);
	}

	f32 IResTerrain::GetHeight( f32 x, f32 y, TerrainVertex* vb )
	{
		return Ptr->GetHeight(x, y, vb);
	}

	f32 IResTerrain::GetTileSize( void )
	{
		return Ptr->mTileSize;
	}

	TerrainVertex* IResTerrain::LockVertexBuffer( void )
	{
		return Ptr->LockVertexBuffer();
	}

	TerrainVertex* IResTerrain::LockVertexBuffer( u32 offset, u32 len )
	{
		return Ptr->LockVertexBuffer(offset, len);
	}

	void IResTerrain::UnLockBuffer( void )
	{
		Ptr->UnLockBuffer();
	}
}