//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2014/4/3 10:33:36_
// 描述:  
//

#ifndef _MESHOBJECTIMPL_201443103336_
#define _MESHOBJECTIMPL_201443103336_

#include <vector>
#include "SceneObjectImpl.h"
#include "Resources/ResRefDefine.h"

namespace panda
{
	class SubMeshObject;
	class AnimationController;
	class MeshObjectImpl:public SceneObjectImpl
	{
	public:
		MeshObjectImpl(ISceneMgr* pCreator);
		virtual ~MeshObjectImpl(void);

		virtual void	UpdateRenderQueue(ICamera* pCamera, RenderQueue* pQueue);

		virtual bool	Probe(const Ray& ray, ProbeResult& result);

		// 精确的碰撞检测
		virtual bool	Intersects(const Ray& ray, ProbeResult& result, bool transformRay = true);

		// 检查是否与包围盒相交
		virtual bool	ProbeBindBox(const Ray& ray, bool transformRay = true);

		void			BindMesh(ResMesh mesh);
		void			SetMaterial(u16 index, ResMaterial mat);
		void			SetMaterial(ResMaterial mat);
		ResMaterial		GetMaterial(u16 index);

		void			SetSkeletion(ResSkeletion skn);

		void			SetSubMeshVisible(u32 index, bool visible);

		//! Builds a list of SubObjects based on the SubMeshes contained in the Mesh
		void			_BuildSubObjectList(void);

		void			_UpdateSkeletion(void);

	public:
		ResMesh					mResMesh;
		typedef	std::vector<SubMeshObject*>	SubMeshObjectList;
		SubMeshObjectList		mSubMeshObjs;

		bool					mHasAnimation;
		ResSkeletion			mSkeletion;
		Matrix44f*				mBoneMatrixs;			// 骨骼的变换矩阵
		AnimationController*	mAniController;
	};
}

#endif // _MESHOBJECTIMPL_201443103336_