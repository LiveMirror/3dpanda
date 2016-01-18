#include "scene/IMeshObject.h"
#include "MeshObjectImpl.h"
#include "SubMeshObject.h"
#include "resources/IResMesh.h"
#include "resources/IMaterial.h"
#include "resources/IResSkeleton.h"

#include "../animation/AnimationController.h"

#define Ptr ((MeshObjectImpl*)mImpl)

namespace panda
{
	IMeshObject::IMeshObject( MeshObjectImpl* pImpl )
		:ISceneObject(pImpl)
	{

	}

	void IMeshObject::BindResMesh( ResMesh mesh )
	{
		Ptr->BindMesh(mesh);
	}

	ResMesh IMeshObject::GetResMesh( void )
	{
		
		return Ptr->mResMesh;
	}

	void IMeshObject::SetMaterial( s16 nIndex, ResMaterial mat )
	{
		
		Ptr->SetMaterial(nIndex, mat);
	}

	void IMeshObject::SetMaterial( ResMaterial mat )
	{
		Ptr->SetMaterial(mat);
	}

	void IMeshObject::SetSkeletion( ResSkeletion skn )
	{
		return Ptr->SetSkeletion(skn);
	}

	ResSkeletion IMeshObject::GetSkeletion( void )
	{
		return Ptr->mSkeletion;
	}
	void IMeshObject::SetSubMeshVisible( u32 index, bool visible )
	{
		return Ptr->SetSubMeshVisible(index, visible);
	}

	u16 IMeshObject::GetNumSubset( void ) const
	{
		return Ptr->mSubMeshObjs.size();
	}

	ResMaterial IMeshObject::GetMaterial( u16 nIndex ) const
	{
		if (nIndex >= Ptr->mSubMeshObjs.size())
		{
			return NULL;
		}
		return Ptr->mSubMeshObjs[nIndex]->mMaterail;
	}

	IAnimationController* IMeshObject::GetAnimationController( void )
	{
		return Ptr->mAniController;
	}
}