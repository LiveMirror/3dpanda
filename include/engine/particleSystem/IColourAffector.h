//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/5/28 16:27:44_
// ����:  
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