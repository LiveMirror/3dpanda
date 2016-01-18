//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/22 17:33:20_
// 描述:  
//

#ifndef _IPARTICLESYS_2014522173320_
#define _IPARTICLESYS_2014522173320_

#include "IResource.h"

namespace panda
{
	class IParticleTechnique;
	class ParticleSysImpl;
	class IParticleSys:public IResource
	{
	public:
		IParticleSys(ParticleSysImpl* impl);

		virtual IParticleTechnique*			CreateTechnique(const tstring& name);
		virtual u32							GetNumTechnique(void)const;
		virtual IParticleTechnique*			GetTechnique(u32 index)const;
		virtual void						RemoveTechnique(u32 index);
		virtual	void						RemoveAllTechnique(void);
	};
}

#endif // _IPARTICLESYS_2014522173320_