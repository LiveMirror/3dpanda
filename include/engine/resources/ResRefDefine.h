//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/2/28 10:44:18_
// 描述:  
//

#ifndef _RESREFDEFINE_2014228104418_
#define _RESREFDEFINE_2014228104418_

#include "ref.hpp"

namespace panda
{
	class IResource;
	typedef Ref<IResource>			Resource;

	class ITexture;
	typedef Ref<ITexture>			ResTexture;

	class IResMesh;
	typedef Ref<IResMesh>			ResMesh;

	class IResTerrain;
	typedef Ref<IResTerrain>		ResTerrain;

	class ITerrainMaterial;
	typedef Ref<ITerrainMaterial>	ResTerMaterial;

	class IResSkeleton;
	typedef Ref<IResSkeleton>		ResSkeletion;

	class IParticleSys;
	typedef Ref<IParticleSys>		ResParticleSys;

	class IMaterial;
	typedef Ref<IMaterial>			ResMaterial;
}

#endif // _RESREFDEFINE_2014228104418_