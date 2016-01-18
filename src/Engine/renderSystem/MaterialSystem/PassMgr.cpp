#include "PassMgr.h"
#include "base/Vector2D.h"
#include "Pass.h"
#include "../../resource/resourcemgr.h"
#include "PostProcessPass.h"
#include "SknPass.h"
#include "LinePass.h"
#include "terpass.h"
#include "EffectSetPass.h"

namespace panda
{
	PassMgr::PassMgr(ResourceMgr* pResMgr)
	{
		mCreater = pResMgr;
	}

	PassMgr::~PassMgr( void )
	{
		PassList::iterator itr = mPasses.begin();
		while(itr != mPasses.end())
		{
			delete itr->second;
			itr++;
		}
	}

	Vector2Df nepixelKernel[4] = {Vector2Df(0,1),Vector2Df(1,0),Vector2Df(0,-1),Vector2Df(-1,0)};

	Vector2Df dfpixelKernel[16] = { Vector2Df( 1.5,  -1.5 ),
		Vector2Df( 1.5,  -0.5 ),
		Vector2Df( 1.5,   0.5 ),
		Vector2Df( 1.5,   1.5 ),
		Vector2Df( 0.5,  -1.5 ),
		Vector2Df( 0.5,  -0.5 ),
		Vector2Df( 0.5,   0.5 ),
		Vector2Df( 0.5,   1.5 ),
		Vector2Df(-0.5,  -1.5 ),
		Vector2Df(-0.5,  -0.5 ),
		Vector2Df(-0.5,   0.5 ),
		Vector2Df(-0.5,   1.5 ),
		Vector2Df(-1.5,  -1.5 ),
		Vector2Df(-1.5,  -0.5 ),
		Vector2Df(-1.5,   0.5 ),
		Vector2Df(-1.5,   1.5 )};

	Vector2Df bhpixelKernel[13] = { Vector2Df( -6,  0 ),
		Vector2Df( -5,  0 ),
		Vector2Df( -4,  0 ),
		Vector2Df( -3,  0 ),
		Vector2Df( -2,  0 ),
		Vector2Df( -1,  0 ),
		Vector2Df( 0,  0 ),
		Vector2Df( 1,  0 ),
		Vector2Df( 2,  0 ),
		Vector2Df( 3,  0 ),
		Vector2Df( 4,  0 ),
		Vector2Df( 5,  0 ),
		Vector2Df( 6,  0 )};

	Vector2Df bvpixelKernel[13] = { Vector2Df( 0,  -6 ),
		Vector2Df( 0,  -5 ),
		Vector2Df( 0,  -4 ),
		Vector2Df( 0,  -3 ),
		Vector2Df( 0,  -2 ),
		Vector2Df( 0,  -1 ),
		Vector2Df( 0,  0 ),
		Vector2Df( 0,  1 ),
		Vector2Df( 0,  2 ),
		Vector2Df( 0,  3 ),
		Vector2Df( 0,  4 ),
		Vector2Df( 0,  5 ),
		Vector2Df( 0,  6 )};

	void PassMgr::Init(void)
	{
		IPass* pPass = new Pass(mCreater->mDevicePtr, mCreater->mRenderMgr);
		pPass->LoadVertexShader(_T("../shader/meshN.vsh"));
		pPass->LoadPixelShader(_T("../shader/meshN.psh"));
		tstring name = _T("meshN");
		mPasses[name] = pPass;

		// ³õÊ¼»¯PostProcess
		PostProcessPass* pp;
		pp = new PostProcessPass(mCreater->mDevicePtr, mCreater->mRenderMgr);
		pp->LoadVertexShader(_T("../shader/postProcess.vsh"));
		pp->LoadPixelShader(_T("../shader/normalEdge.psh"));
		pp->SetKernel(4, nepixelKernel);
		name = _T("normalEdge");
		mPasses[name] = pp;

		/*pp = new PostProcessPass(mCreater->mDevicePtr, mCreater->mRenderMgr);
		pp->LoadVertexShader(_T("../../shader/postProcess.vsh"));
		pp->LoadPixelShader(_T("../../shader/DownFilter4.psh"));
		pp->SetKernel(16, dfpixelKernel);
		pp->SetScale(0.25f);
		name = _T("downFilter4");
		mPasses[name] = pp;

		pp = new PostProcessPass(mCreater->mDevicePtr, mCreater->mRenderMgr);
		pp->LoadVertexShader(_T("../../shader/postProcess.vsh"));
		pp->LoadPixelShader(_T("../../shader/bloom.psh"));
		pp->SetKernel(13, bhpixelKernel);
		name = _T("bloomH");
		mPasses[name] = pp;

		pp = new PostProcessPass(mCreater->mDevicePtr, mCreater->mRenderMgr);
		pp->LoadVertexShader(_T("../../shader/postProcess.vsh"));
		pp->LoadPixelShader(_T("../../shader/bloom.psh"));
		pp->SetKernel(13, bvpixelKernel);
		name = _T("bloomV");
		mPasses[name] = pp;

		pp = new PostProcessPass(mCreater->mDevicePtr, mCreater->mRenderMgr);
		pp->LoadVertexShader(_T("../../shader/postProcess.vsh"));
		pp->LoadPixelShader(_T("../../shader/combine.psh"));
		name = _T("combine4");
		mPasses[name] = pp;*/
	}

	IPass* PassMgr::GetPass( const tchar* name )
	{
		PassList::iterator itr = mPasses.find(name);
		if(itr != mPasses.end())
		{
			return itr->second;
		}
		return NULL;
	}

	IPass* PassMgr::LoadPass( const tchar* path, const tchar name )
	{
		return NULL;
	}

	IPass* PassMgr::CreatePass( PassType::eValue type /*= PassType::type_StaticMesh*/ )
	{
		Pass* p;
		switch(type)
		{
		case PassType::type_StaticMesh:
			{
				p = new Pass(mCreater->mDevicePtr, mCreater->mRenderMgr);
				break;
			}
		case PassType::type_Terrain:
			{
				p = new TerPass(mCreater->mDevicePtr, mCreater->mRenderMgr);
				break;
			}
		case PassType::type_Line:
			{
				p = new LinePass(mCreater->mDevicePtr, mCreater->mRenderMgr);
				break;
			}
		case PassType::type_SknMesh:
			{
				p = new SknPass(mCreater->mDevicePtr, mCreater->mRenderMgr);
				break;
			}
		case PassType::type_Water:
			{
				//p = new WaterPass(mCreater->mDevicePtr, mCreater->mRenderMgr);
				break;
			}
		case PassType::type_Effect:
			{
				p = new EffectSetPass(mCreater->mDevicePtr, mCreater->mRenderMgr);
				break;
			}
		}
		return p;
	}
}