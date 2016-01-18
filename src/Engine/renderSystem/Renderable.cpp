#include "Renderable.h"

#include "RenderSystem.h"
#include "resources/IMaterial.h"
#include "MaterialSystem/Pass.h"
#include "renderSystem/ITechnique.h"
#include "scene/ICamera.h"

#include "../scene/CameraImpl.h"
#include "../resource/Materialimpl.h"

namespace panda
{
	Renderable::Renderable( void )
		:mVisible(true)
	{

	}

	void Renderable::Render( RenderSystem* pRender, ICamera* pCamera)
	{
		CameraImpl* pCameraImpl = (CameraImpl*)pCamera->mImpl;
		const Matrix44f& matrix = GetWorldTransforms();
		MaterialImpl* mat = (MaterialImpl*)mMaterail->mImpl;
		MaterialImpl::TechniqueList::iterator it = mat->mTechniques.begin();
		pRender->SetWorldTransform(0, matrix);

		while (it != mat->mTechniques.end())
		{
			ITechnique* tq = *it;
			Pass* pass = (Pass*)tq->GetPass(0);
			pRender->SetPass(pass);
			pass->SetParam(mat, pCameraImpl, this);
			RenderGeometry(pRender);
			it++;
		}
	}

	ResMaterial Renderable::GetMaterial( void ) const
	{
		return mMaterail;
	}

	void Renderable::SetVisible( bool visible )
	{
		mVisible = visible;
	}

	bool Renderable::GetVisible( void ) const
	{
		return mVisible;
	}
}