#include "MaterialSerialize.h"
#include "../MaterialImpl.h"
#include "resources/IMaterial.h"
#include "resources/ITexture.h"
#include "../../renderSystem/MaterialSystem/TechniqueImpl.h"
#include "renderSystem/ITechnique.h"
#include "renderSystem/IPass.h"
#include "../TerrainMaterialImpl.h"
#include "resources/ITerrainMaterial.h"
#include "../../renderSystem/MaterialSystem/TerPass.h"

namespace panda
{
	IMaterial* MaterialSerialize::CreateMaterial( MaterialType::eValue type, ResourceMgr* resMgr, RenderSystem* renderMgr )
	{
		switch(type)
		{
		case MaterialType::Type_StaticMesh:
			{
				MaterialImpl* pImpl = new MaterialImpl(resMgr, renderMgr);
				IMaterial* pMat = new IMaterial(pImpl);

				ITechnique* tq = pImpl->CreateTechnique();
				IPass* pass = tq->mImpl->CreatePass(PassType::type_StaticMesh);
				pass->LoadVertexShader(_T("../shader/meshN.vsh"));
				pass->LoadPixelShader(_T("../shader/meshN.psh"));
				return pMat;
			}
		case MaterialType::Type_SknMesh:
			{
				MaterialImpl* pImpl = new MaterialImpl(resMgr, renderMgr);
				pImpl->mMatType = type;
				IMaterial* pMat = new IMaterial(pImpl);

				ITechnique* tq = pImpl->CreateTechnique();
				IPass* pass = tq->mImpl->CreatePass(PassType::type_SknMesh);
				pass->LoadVertexShader(_T("../shader/skn.vsh"));
				pass->LoadPixelShader(_T("../shader/skn.psh"));
				return pMat;
			}
		case MaterialType::Type_Line:
			{
				MaterialImpl* pImpl = new MaterialImpl(resMgr, renderMgr);
				pImpl->mMatType = type;
				IMaterial* pMat = new IMaterial(pImpl);

				ITechnique* tq = pImpl->CreateTechnique();
				IPass* pass = tq->mImpl->CreatePass(PassType::type_Line);
				pass->LoadVertexShader(_T("../shader/line.vsh"));
				pass->LoadPixelShader(_T("../shader/line.psh"));
				return pMat;
			}
		case MaterialType::Type_Terrain:
			{
				TerrainMaterialImpl* pImpl = new TerrainMaterialImpl(resMgr, renderMgr);
				ITerrainMaterial* pMat = new ITerrainMaterial(pImpl);

				ITechnique* tq = pImpl->CreateTechnique();
				TerPass* pass = (TerPass*)tq->mImpl->CreatePass(PassType::type_Terrain);
				pass->LoadVertexShader(_T("../shader/terrain.vsh"));
				pass->LoadPixelShader(_T("../shader/terrain.psh"));
				return pMat;
			}
		case MaterialType::Type_Water:
			{
				/*WaterMaterialImpl* pImpl = new WaterMaterialImpl(resMgr, renderMgr);
				IWaterMaterial* pMat = new IWaterMaterial(pImpl);

				ITechnique* tq = pImpl->CreateTechnique();
				WaterPass* pass = (WaterPass*)tq->mImpl->CreatePass(PassType::type_Water);
				pass->LoadVertexShader(_T("../../shader/water.vsh"));
				pass->LoadPixelShader(_T("../../shader/water.psh"));
				return pMat;*/
			}
		case MaterialType::Type_Effect:
			{
				MaterialImpl* pImpl = new MaterialImpl(resMgr, renderMgr);
				pImpl->mMatType = type;
				IMaterial* pMat = new IMaterial(pImpl);

				ITechnique* tq = pImpl->CreateTechnique();
				IPass* pass = tq->mImpl->CreatePass(PassType::type_Effect);
				pass->LoadVertexShader(_T("../shader/effect.vsh"));
				pass->LoadPixelShader(_T("../shader/effect.psh"));
				return pMat;
			}
		}
		return NULL;
	}
}