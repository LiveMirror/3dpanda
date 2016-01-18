//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 10:39:21_
// ����:  
//

#ifndef _ANIOBJECT_201443103921_
#define _ANIOBJECT_201443103921_

#include "Base/Config.h"

namespace panda
{
	class SceneMgrImpl;
	class AniObject
	{
	public:
		AniObject(SceneMgrImpl* sceneMgr);
		virtual ~AniObject(void);

		virtual void	Update(f32 time) = 0;

		virtual void	SetEnabled(bool enabled);
		virtual bool	GetEnabled(void)const;
	public:
		SceneMgrImpl*	mSceneMgr;
		bool			mEnabled;
	};
}

#endif // _ANIOBJECT_201443103921_