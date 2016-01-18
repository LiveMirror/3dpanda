//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/21 10:35:39_
// 描述:  游戏中间件
//

#ifndef _GAME_2014521103539_
#define _GAME_2014521103539_

#include "IGame.h"
#include <map>

namespace panda
{
	class Game:public IGame
	{
	public:
		Game(void);

		virtual void			RegestSerialze(ISerialize* pSer);
		virtual void			RegestDeserialze(IDeserialize* pDeser);

		virtual ILevel*			CreateLevel(s32 width, s32 height, f32 tileSize);
		virtual ILevel*			LoadLevel(const tstring& path);
	public:
		IPanda*					mEngine;

		std::map<s32, ISerialize*>		mSerialize;
		std::map<s32, IDeserialize*>	mDeserialize;
	};
}

#endif // _GAME_2014521103539_