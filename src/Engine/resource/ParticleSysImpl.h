//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/23 15:37:25_
// 描述:  
//

#ifndef _PARTICLESYSIMPL_2014523153725_
#define _PARTICLESYSIMPL_2014523153725_

#include "ResourceImpl.h"
#include <vector>

namespace panda
{
	class IParticleTechnique;
	class ParticleSysImpl:public ResourceImpl
	{
	public:
		ParticleSysImpl(ResourceMgr* resMgr);
		virtual ~ParticleSysImpl(void);

		virtual bool	_Load(void);
		virtual void	_UnLoad(void);
		virtual void	_Save(const tchar* path);
		IParticleTechnique*			CreateTechnique(const tstring& name);
		IParticleTechnique*			GetTechnique(u32 index)const;
		void						RemoveTechnique(u32 index);
		void						RemoveAllTechnique(void);

	public:
		typedef std::vector<IParticleTechnique*>	TechniqueList;
		TechniqueList		mTechniques;
	};
}

#endif // _PARTICLESYSIMPL_2014523153725_