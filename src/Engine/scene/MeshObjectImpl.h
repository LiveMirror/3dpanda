//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2014/4/3 10:33:36_
// ����:  
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

		// ��ȷ����ײ���
		virtual bool	Intersects(const Ray& ray, ProbeResult& result, bool transformRay = true);

		// ����Ƿ����Χ���ཻ
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
		Matrix44f*				mBoneMatrixs;			// �����ı任����
		AnimationController*	mAniController;
	};
}

#endif // _MESHOBJECTIMPL_201443103336_