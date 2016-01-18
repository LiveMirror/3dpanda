//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/5/26 17:34:46_
// 描述:  
//

#ifndef _BILLBOARDOBJECTIMPL_2014526173446_
#define _BILLBOARDOBJECTIMPL_2014526173446_

#include "SceneObjectImpl.h"
#include <list>

namespace panda
{
	class Billboard;
	class IBillboard;
	class BillboardObjectImpl:public SceneObjectImpl
	{
	public:
		BillboardObjectImpl(ISceneMgr* pCreator);

		virtual void	UpdateRenderQueue(ICamera* pCamera, RenderQueue* pQueue);

		IBillboard*		CreateBillBoard(void);

	public:
		typedef	std::list<Billboard*>	BillboardList;
		BillboardList	mBillboards;
	};
}

#endif // _BILLBOARDOBJECTIMPL_2014526173446_