//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/21 10:32:45_
// ����:  ����
//

#ifndef _ILEVEL_2014521103245_
#define _ILEVEL_2014521103245_

#include "resources/ResRefDefine.h"

namespace panda
{
	class ILevel
	{
	public:
		virtual ResTerrain		GetTerrain(void)const = 0;
		//virtual void			SetTerrain(ResTerrain ter) = 0;

		virtual ResTerMaterial	GetMaterial(void)const = 0;
		//virtual void			SetMaterial(ResTerMaterial mat) = 0;

		virtual void			Save(void) = 0;
		virtual void			Save(const tstring& path) = 0;
	};
}

#endif // _ILEVEL_2014521103245_