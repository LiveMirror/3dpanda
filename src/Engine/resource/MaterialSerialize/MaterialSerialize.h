////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  Hu Tianzhi
// 日期: 2014-4-21 22:59:38
// 描述:  
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