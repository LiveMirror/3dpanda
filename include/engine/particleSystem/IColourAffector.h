//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/28 16:27:44_
// 描述:  
//

#ifndef _ICOLOURAFFECTOR_2014528162744_
#define _ICOLOURAFFECTOR_2014528162744_

#include "IParticleAffector.h"

namespace panda
{
	class ColourAffectorImpl;
	class IColourAffector:public IParticleAffector
	{
	public:
		IColourAffector(ColourAffectorImpl* impl);

		virtual void				SetColor(const Colorf& color);
		virtual const Colorf&		GetColor(void)const;
	};
}

#endif // _ICOLOURAFFECTOR_2014528162744_