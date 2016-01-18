#include "BillboardObjectImpl.h"
#include "Billboard.h"

namespace panda
{
	BillboardObjectImpl::BillboardObjectImpl( ISceneMgr* pCreator )
		:SceneObjectImpl(pCreator)
	{

	}

	void BillboardObjectImpl::UpdateRenderQueue( ICamera* pCamera, RenderQueue* pQueue )
	{
		if (!mVisible)
			return;
	}

	IBillboard* BillboardObjectImpl::CreateBillBoard( void )
	{
		Billboard* board = new Billboard;
		mBillboards.push_back(board);
		return board;
	}
}