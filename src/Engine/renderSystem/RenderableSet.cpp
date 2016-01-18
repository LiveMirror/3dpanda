#include <WinSock2.h>
#include "RenderableSet.h"
#include "resources/IMaterial.h"
#include "../scene/CameraImpl.h"
#include "scene/ICamera.h"
#include "../resource/MaterialImpl.h"
#include "RenderSystem.h"
#include "rendersystem/ITechnique.h"
#include "materialsystem/Pass.h"

namespace panda
{
	RenderableSet::RenderableSet( void )
	{

	}

	void RenderableSet::Render( RenderSystem* pRender, ICamera* pCamera )
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
			RenderSets(pRender, pass);
			it++;
		}
	}

	void RenderableSet::RenderGeometry( RenderSystem* pRender ) const
	{
		// do nothing
	}

	void RenderableSet::RenderSets( RenderSystem* pRender, Pass* pass )
	{

	}
}