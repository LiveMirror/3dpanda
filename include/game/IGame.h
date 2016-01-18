//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/21 10:33:56_
// 描述:  
//

#ifndef _IGAME_2014521103356_
#define _IGAME_2014521103356_

#ifndef GAME_EXPORTS
#define GAME_API	__declspec(dllimport)
#else
#define GAME_API	__declspec(dllexport)
#endif

#include "ILevel.h"

namespace panda
{
	class IPanda;
	class ISerialize;
	class IDeserialize;
	class IGame
	{
	public:
		virtual void			RegestSerialze(ISerialize* pSer) = 0;
		virtual void			RegestDeserialze(IDeserialize* pDeser) = 0;

		virtual ILevel*			CreateLevel(s32 width, s32 height, f32 tileSize) = 0;
		virtual ILevel*			LoadLevel(const tstring& path) = 0;
	};


	extern "C" GAME_API IGame*  CreateIGame(IPanda* pEngine);
}

#endif // _IGAME_2014521103356_