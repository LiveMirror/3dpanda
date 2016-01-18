#include <WinSock2.h>
#include "Serialize/ISerialize.h"
#include "Deserialize/IDeserialize.h"
#include "level.h"
#include "IPanda.h"
#include "Game.h"

namespace panda
{
	extern "C" GAME_API IGame* CreateIGame( IPanda* pEngine )
	{
		Game* pGame = new Game;
		pGame->mEngine = pEngine;
		return pGame;
	}

	Game::Game( void )
	{

	}

	void Game::RegestSerialze( ISerialize* pSer )
	{
		std::map<s32, ISerialize*>::iterator it = mSerialize.find(pSer->GetChunk());
		if(it == mSerialize.end())
		{
			mSerialize[pSer->GetChunk()] = pSer;
		}
	}

	void Game::RegestDeserialze( IDeserialize* pDeser )
	{
		std::map<s32, IDeserialize*>::iterator it = mDeserialize.find(pDeser->GetChunk());
		if(it == mDeserialize.end())
		{
			mDeserialize[pDeser->GetChunk()] = pDeser;
		}
	}

	ILevel* Game::CreateLevel( s32 width, s32 height, f32 tileSize )
	{
		Level* pLevel = new Level;
		pLevel->mTerrain = mEngine->GetResMgr()->CreateTerrain(width, height, tileSize);
		pLevel->mTerMat = mEngine->GetResMgr()->CreateMaterial(MaterialType::Type_Terrain);
		return pLevel;
	}

	ILevel* Game::LoadLevel( const tstring& path )
	{
		return NULL;
	}
}