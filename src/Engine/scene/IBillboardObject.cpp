#include "scene/IBillboardObject.h"
#include "resources/IMaterial.h"
#include "BillBoardObjectImpl.h"

#define Ptr		((BillboardObjectImpl*)mImpl)

namespace panda
{
	IBillboardObject::IBillboardObject( BillboardObjectImpl* impl )
		:ISceneObject(impl)
	{

	}


	IBillboard* IBillboardObject::CreateBillBoard( void )
	{
		return Ptr->CreateBillBoard();
	}

	u32 IBillboardObject::GetNumBillBoards( void ) const
	{
		throw 0;
	}

	IBillboard* IBillboardObject::GetBillBoard( u32 index ) const
	{
		throw 0;
	}

	void IBillboardObject::RemoveBillBoard( u32 index )
	{
		throw 0;
	}

	void IBillboardObject::SetMaterial( ResMaterial mat )
	{
		throw 0;
	}

	ResMaterial IBillboardObject::GetMaterial( void ) const
	{
		throw 0;
	}
}

