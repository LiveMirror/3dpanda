//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/21 17:37:51_
// 描述:  
//

#ifndef _LEVEL_2014521173751_
#define _LEVEL_2014521173751_

#include "ILevel.h"

namespace panda
{
	class Level:public ILevel
	{
	public:
		Level(void);

		virtual ResTerrain		GetTerrain(void)const;
		//virtual void			SetTerrain(ResTerrain ter);

		virtual ResTerMaterial	GetMaterial(void)const;

		virtual void			Save(void);
		virtual void			Save(const tstring& path);

	public:
		ResTerrain			mTerrain;
		ResTerMaterial		mTerMat;
	};
}

#endif // _LEVEL_2014521173751_