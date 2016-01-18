#include "MeshObjectImpl.h"
#include <d3dx9.h>
#include "Scene/ISceneNode.h"
#include "scene/ISceneMgr.h"
#include "resources/IResMesh.h"
#include "resources/IMaterial.h"
#include "resources/IResSkeleton.h"
#include "SubMeshObject.h"
#include "../resource/MaterialImpl.h"
#include "../resource/ResourceMgr.h"
#include "../rendersystem/renderqueue.h"
#include "../resource/resmeshimpl.h"
#include "../resource/ResSkeletonImpl.h"
#include "../animation/AnimationController.h"


namespace panda
{
	MeshObjectImpl::MeshObjectImpl( ISceneMgr* pCreator )
		:SceneObjectImpl(pCreator),
		mHasAnimation(false),
		mAniController(NULL),
		mBoneMatrixs(NULL)
	{

	}

	MeshObjectImpl::~MeshObjectImpl( void )
	{
		SubMeshObjectList::iterator itr = mSubMeshObjs.begin();
		while (itr != mSubMeshObjs.end())
		{
			delete *itr;
			itr++;
		}
		if (NULL != mBoneMatrixs)
		{
			delete[] mBoneMatrixs;
		}
		/*if(NULL != mAniCtrler)
		{
			delete mAniCtrler;
		}*/
	}

	void MeshObjectImpl::UpdateRenderQueue( ICamera* pCamera, RenderQueue* pQueue )
	{
		if (!mVisible) 
			return;

		SubMeshObjectList::iterator itr = mSubMeshObjs.begin();
		while (itr != mSubMeshObjs.end())
		{
			if ((*itr)->GetVisible())
			{
				if ((*itr)->mMaterail->GetTextureAlpha())
				{
					pQueue->AddRenderObject(*itr, RenderQueue::AlphaObject);
				}
				else
				{
					pQueue->AddRenderObject(*itr, RenderQueue::NormalObject);
				}
			}
			itr++;
		}
		_UpdateSkeletion();
	}

	bool MeshObjectImpl::Probe( const Ray& ray, ProbeResult& result)
	{
		// 模型的逆变换矩阵
		D3DXMATRIX invMat;
		D3DXMatrixInverse(&invMat, NULL, (const D3DXMATRIX*)&mParent->GetWorldMatrix());

		Vector3Df startP;
		Vector3Df endP = ray.sPosition + ray.sDirction;
		// 转换到模型坐标系
		D3DXVec3TransformCoord(
			(D3DXVECTOR3*)&startP,
			(const D3DXVECTOR3*)&ray.sPosition,
			(const D3DXMATRIX*)&invMat);

		D3DXVec3TransformCoord(
			(D3DXVECTOR3*)&endP,
			(const D3DXVECTOR3*)&endP,
			(const D3DXMATRIX*)&invMat);

		Ray r = Ray(startP, endP - startP);

		if (!ProbeBindBox(r,false))
		{
			return false;
		}
		return Intersects(r, result, false);
	}

	bool MeshObjectImpl::Intersects( const Ray& ray, ProbeResult& result, bool transformRay/* = true*/ )
	{
		// 把结果指针指向自己
		result.object = mThisPtr;
		if (transformRay)
		{
			// 模型的逆变换矩阵
			D3DXMATRIX invMat;
			D3DXMatrixInverse(&invMat, NULL, (const D3DXMATRIX*)&mParent->GetWorldMatrix());

			Vector3Df startP;
			Vector3Df endP = ray.sPosition + ray.sDirction;
			// 转换到模型坐标系
			D3DXVec3TransformCoord(
				(D3DXVECTOR3*)&startP,
				(const D3DXVECTOR3*)&ray.sPosition,
				(const D3DXMATRIX*)&invMat);

			D3DXVec3TransformCoord(
				(D3DXVECTOR3*)&endP,
				(const D3DXVECTOR3*)&endP,
				(const D3DXMATRIX*)&invMat);

			Ray r = Ray(startP, endP - startP);

			ResMeshImpl* pImpl = (ResMeshImpl*)mResMesh->mImpl;
			return pImpl->Probe(r, result);
		}
		else
		{
			ResMeshImpl* pImpl = (ResMeshImpl*)mResMesh->mImpl;
			return pImpl->Probe(ray, result);
		}
	}

	bool MeshObjectImpl::ProbeBindBox( const Ray& ray, bool transformRay/* = true*/)
	{
		if (transformRay)
		{
			// 模型的逆变换矩阵
			D3DXMATRIX invMat;
			D3DXMatrixInverse(&invMat, NULL, (const D3DXMATRIX*)&mParent->GetWorldMatrix());

			Vector3Df startP;
			Vector3Df endP = ray.sPosition + ray.sDirction;
			// 转换到模型坐标系
			D3DXVec3TransformCoord(
				(D3DXVECTOR3*)&startP,
				(const D3DXVECTOR3*)&ray.sPosition,
				(const D3DXMATRIX*)&invMat);
			D3DXVec3TransformCoord(
				(D3DXVECTOR3*)&endP,
				(const D3DXVECTOR3*)&endP,
				(const D3DXMATRIX*)&invMat);
			Ray r = Ray(startP, endP - startP);
			ResMeshImpl* pImpl = (ResMeshImpl*)mResMesh->mImpl;
			Vector3Df outPos;
			return pImpl->mAABBOX.IntersectsWithRay(r, outPos);
		}
		else
		{
			ResMeshImpl* pImpl = (ResMeshImpl*)mResMesh->mImpl;
			Vector3Df outPos;
			return pImpl->mAABBOX.IntersectsWithRay(ray, outPos);
		}
	}

	void MeshObjectImpl::BindMesh( ResMesh mesh )
	{
		mSubMeshObjs.clear();
		if (!mesh.IsNull())
		{
			mesh->Load();
		}
		mResMesh = mesh;
		_BuildSubObjectList();
	}

	void MeshObjectImpl::SetMaterial( u16 index, ResMaterial mat )
	{
		if(index >= mSubMeshObjs.size())
		{
			return;
		}
		if (!mat.IsNull())
		{
			mat->Load();
		}
		mSubMeshObjs[index]->mMaterail = mat;
		MaterialImpl* pImpl = (MaterialImpl*)mat->mImpl;
		pImpl->OnBind(mThisPtr);
	}

	void MeshObjectImpl::SetMaterial( ResMaterial mat )
	{
		if (!mat.IsNull())
		{
			mat->Load();
		}
		u32 num = mSubMeshObjs.size();
		for (u32 i = 0; i < num; i++)
		{
			mSubMeshObjs[i]->mMaterail = mat;
		}
		MaterialImpl* pImpl = (MaterialImpl*)mat->mImpl;
		pImpl->OnBind(mThisPtr);
	}

	ResMaterial MeshObjectImpl::GetMaterial( u16 index )
	{
		if(index >= mSubMeshObjs.size())
		{
			return NULL;
		}
		return mSubMeshObjs[index]->mMaterail;
	}

	void MeshObjectImpl::SetSubMeshVisible( u32 index, bool visible )
	{
		if (index >= mSubMeshObjs.size())
		{
			return;
		}
		mSubMeshObjs[index]->SetVisible(visible);
	}

	void MeshObjectImpl::_BuildSubObjectList()
	{
		u32 num = mResMesh->GetSubSetNum();
		for (u32 i = 0; i < num; i++)
		{
			SubMeshObject* pSubObj = new SubMeshObject(this);
			pSubObj->mSubMesh = (SubMesh*)mResMesh->GetSubMesh(i);
			pSubObj->mMaterail = mResMesh->mImpl->mResMgr->GetDefaultMat();		// 设置默认的材质
			mSubMeshObjs.push_back(pSubObj);
		}
	}

	void MeshObjectImpl::SetSkeletion( ResSkeletion skn )
	{
		if(skn == mSkeletion)
		{
			return;
		}
		mSkeletion = skn;
		if (!mSkeletion.IsNull())
		{
			// Create a aniController if it's NULL
			if (NULL == mAniController)
			{
				mAniController = new AnimationController(mCreator->mImpl);
			}
			mAniController->InitWithSkn(mSkeletion);

			mHasAnimation = true;
			if (NULL != mBoneMatrixs)
			{
				delete[] mBoneMatrixs;
			}
			mBoneMatrixs = new Matrix44f[mSkeletion->GetNumBones()];

			ResSkeletonImpl* pSkn = (ResSkeletonImpl*)mSkeletion->mImpl;

			pSkn->_DeriveRootBone();
			pSkn->SetBindingPose();
			pSkn->GetBoneMatrices(mBoneMatrixs);
			_UpdateSkeletion();
		}
		else
		{
			mHasAnimation = false;
		}
	}

	void MeshObjectImpl::_UpdateSkeletion( void )
	{
		if (!mHasAnimation)
		{
			return;
		}

		ResSkeletonImpl* pImpl = (ResSkeletonImpl*)mSkeletion->mImpl;
		// 重置骨骼到绑定位置,以便进行骨骼变形
		pImpl->ResetBone();
		// 应用变形动画
		mAniController->Apply();

		// Cache the matrices for render
		pImpl->GetBoneMatrices(mBoneMatrixs);
	}
}