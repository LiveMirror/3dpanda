//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 15:38:47_
// ����:  
//

#ifndef _PASSMGR_201443153847_
#define _PASSMGR_201443153847_

#include <map>
#include "Base/Config.h"
#include "TechniqueImpl.h"

namespace panda
{
	class ResourceMgr;
	class IPass;
	class PassMgr
	{
	public:
		PassMgr(ResourceMgr* pResMgr);
		virtual ~PassMgr(void);

		//! ��ʼ��pass
		void		Init(void);

		IPass*		GetPass(const tchar* name);

		IPass*		CreatePass(PassType::eValue type = PassType::type_StaticMesh);

	protected:
		IPass*		LoadPass(const tchar* path, const tchar name);

	public:
		typedef	std::map<tstring, IPass*>	PassList;
		PassList		mPasses;

		ResourceMgr*	mCreater;
	};
}

#endif // _PASSMGR_201443153847_