//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/21 17:37:51_
// ����:  
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