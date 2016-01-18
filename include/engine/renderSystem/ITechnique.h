//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 15:11:01_
// 描述:  
//

#ifndef _ITECHNIQUE_201443151101_
#define _ITECHNIQUE_201443151101_

#include "Base/Config.h"

namespace panda
{
	class IPass;
	class TechniqueImpl;

	class ITechnique
	{
	public:
		ITechnique(TechniqueImpl* pImpl);
		virtual ~ITechnique(void);

		virtual u16			GetNumPasses(void);
		virtual IPass*		GetPass(s16 index);
		virtual IPass*		CreatePass(void);

		virtual void		RemovePass(IPass* pass);

	public:
		TechniqueImpl*		mImpl;
	};
}

#endif // _ITECHNIQUE_201443151101_