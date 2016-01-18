#include "resources/IResMesh.h"
#include "ResMeshImpl.h"
#include "SubMesh.h"

#define Ptr ((ResMeshImpl*)mImpl)

namespace panda
{
	IResMesh::IResMesh( ResMeshImpl* pImpl ):IResource(pImpl)
	{

	}

	const AABBOX& IResMesh::GetAABBOX() const
	{
		return Ptr->GetAABBOX();
	}

	void IResMesh::UpdateAABB( void )
	{
		Ptr->UpdateAABB();
	}

	void IResMesh::UpdateNormals( void )
	{
		Ptr->UpdateNormals();
	}

	s32 IResMesh::GetVertexNum( void ) const
	{
		return Ptr->GetVectorNum();
	}

	s32 IResMesh::GetTriangleNum( void ) const
	{
		return Ptr->GetTriangleNum();
	}

	u32 IResMesh::GetSubSetNum( void ) const
	{
		return Ptr->GetSubSetNum();
	}

	ISubMesh* IResMesh::GetSubMesh( u32 index ) const
	{
		return Ptr->GetSubMesh(index);
	}

	ISubMesh* IResMesh::CreateSubMesh( void )
	{
		return Ptr->CreateSubMesh();
	}
}