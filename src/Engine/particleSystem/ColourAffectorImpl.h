//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/28 16:29:32_
// 描述:  
//

#ifndef _COLOURAFFECTORIMPL_2014528162932_
#define _COLOURAFFECTORIMPL_2014528162932_

#include "ParticleAffectorImpl.h"

namespace panda
{
	class ColourAffectorImpl:public ParticleAffectorImpl
	{
	public:
		ColourAffectorImpl(void);

		virtual void		AffectParticles(ParticleList& pattilces, f32 time);

	public:
		Colorf				mAddColor;
	};
}

#endif // _COLOURAFFECTORIMPL_2014528162932_