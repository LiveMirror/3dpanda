////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-4-21 22:59:38
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014421225938_H_
#define	_Tian_2014421225938_H_

#include "base/Struct.h"

namespace panda
{
	class IMaterial;
	class ResourceMgr;
	class RenderSystem;
	class MaterialSerialize
	{
	public:
		static IMaterial*	CreateMaterial(MaterialType::eValue type, ResourceMgr* resMgr, RenderSystem* renderMgr);
	};
}

#endif _Tian_2014421225938_H_