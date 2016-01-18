#include "Effect.h"
#include "base/Vector3D.h"
#include "base/Vector2D.h"
#include "../../resource/VertexData.h"
#include "../../resource/IndexData.h"
#include "resources/IResMgr.h"
#include "RenderSystem/IRenderTarget.h"
#include "../../resource/ResourceMgr.h"
#include "PostProcessPass.h"
#include "PassMgr.h"
#include "../RenderWindow.h"
#include "../RenderSystem.h"
#include "../RenderTargetImpl.h"

namespace panda
{
	struct PPVertex
	{
		Vector3Df pos;
		Vector2Df uv;
	};

	Effect::Effect( void )
		:mCurrentIndex(0),
		mNormalMap(NULL),
		mDepthMap(NULL),
		mOldColor1(NULL)
	{

	}

	Effect::~Effect()
	{
		delete mVertexData;
		delete mIndexData;
		delete mColorMap;
		delete mNormalMap;
		delete mDepthMap;
		delete mRT[0];
		delete mRT[1];
	}

	void Effect::Init(IDirect3DDevice9* device, IResMgr* pResMgr)
	{
		mDevice = device;
		mVertexData = new VertexData(device);
		mVertexData->AddElement(0, 0, DeclareType::DECLTYPE_FLOAT3, 0, DeclareUsage::DECLUSAGE_POSITION, 0);
		mVertexData->AddElement(0, 12, DeclareType::DECLTYPE_FLOAT2, 0, DeclareUsage::DECLUSAGE_TEXCOORD, 0);
		mVertexData->mVertexCount = 4;
		mVertexData->CreateHardwareBuffer(0, sizeof(PPVertex));
		PPVertex* vb = (PPVertex*)mVertexData->LockBuffer(0);
		vb[0].pos = Vector3Df(0, 0, 0);	vb[0].uv = Vector2Df(0, 0);
		vb[1].pos = Vector3Df(2, 0, 0);	vb[1].uv = Vector2Df(1, 0);
		vb[2].pos = Vector3Df(2, -2, 0);	vb[2].uv = Vector2Df(1, 1);
		vb[3].pos = Vector3Df(0, -2, 0);	vb[3].uv = Vector2Df(0, 1);
		mVertexData->Unlock(0);

		mIndexData = new IndexData(device);
		mIndexData->CreateHardwareBuffer(6, false);
		s16* ib = (s16*)mIndexData->LockBuffer();
		ib[0] = 0;	ib[1] = 1;	ib[2] = 2;
		ib[3] = 0;	ib[4] = 2;	ib[5] = 3;
		mIndexData->Unlock();

		mColorMap = pResMgr->CreateRenderTarget(mWidth, mHeight);
		mNormalMap = pResMgr->CreateRenderTarget(mWidth, mHeight);
		mDepthMap = pResMgr->CreateRenderTarget(mWidth, mHeight);
		mRT[0] = pResMgr->CreateRenderTarget(mWidth, mHeight);
		mRT[1] = pResMgr->CreateRenderTarget(mWidth, mHeight);

		ResourceMgr* resMgr = (ResourceMgr*)pResMgr;
		PostProcessPass* pass;

		/*pass = (PostProcessPass*)resMgr->mPassMgr->GetPass(_T("downFilter4"));
		pass->Resize(mWidth, mHeight);
		AddPass(pass);*/

		/*pass = (PostProcessPass*)resMgr->mPassMgr->GetPass(_T("bloomH"));
		pass->Resize(mWidth, mHeight);
		AddPass(pass);

		pass = (PostProcessPass*)resMgr->mPassMgr->GetPass(_T("bloomV"));
		pass->Resize(mWidth, mHeight);
		AddPass(pass);

		pass = (PostProcessPass*)resMgr->mPassMgr->GetPass(_T("combine4"));
		pass->Resize(mWidth, mHeight);
		AddPass(pass);*/

		pass = (PostProcessPass*)resMgr->mPassMgr->GetPass(_T("normalEdge"));
		pass->Resize(mWidth, mHeight);
		AddPass(pass);
	}

	void Effect::OnLostDevice( void )
	{
		mColorMap->Release();
		mNormalMap->Release();
		mDepthMap->Release();
		mRT[0]->Release();
		mRT[1]->Release();
	}

	void Effect::AddPass( IPass* pass )
	{
		mPasses.push_back(pass);
	}

	void Effect::RemovePass( IPass* pass )
	{

	}

	IRenderTarget* Effect::GetNextSurface( void )
	{
		if(0 == mCurRt)
		{
			mCurRt = 1;
		}
		else
		{
			mCurRt = 0;
		}
		return mRT[mCurRt];
	}

	IRenderTarget* Effect::GetBackSurface( void )
	{
		if(-1 == mCurRt)
		{
			return mColorMap;
		}
		else
		{
			return mRT[mCurRt];
		}
	}

	void Effect::BeginEffect( void )
	{
		if(mPasses.empty())
		{
			return;
		}
		mOldColor0 = mParent->_GetRenderTarget(0);
		mOldColor1 = mParent->_GetRenderTarget(1);
		mDevice->GetDepthStencilSurface(&mOldDepth);
		//mOldColor2 = mParent->_GetRenderTarget(2);

		mCurRt = -1;
		mParent->_SetRenderTarget(mColorMap, 0);
		mParent->_SetRenderTarget(mNormalMap, 1);
		//mParent->_SetRenderTarget(mDepthMap, 2);
		RenderTargetImpl* impl = (RenderTargetImpl*)mDepthMap->mImpl;
		mDevice->SetDepthStencilSurface(impl->GetDepthSurface());

		mDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
		// 将NormalMap底色设置为0xFF
		mDevice->Clear(1, NULL, D3DCLEAR_TARGET, 0xFF, 1.0f, 0);
	}



	void Effect::EndEffect( void )
	{
		if(mPasses.empty())
		{
			return;
		}

		mParent->_SetRenderTarget(mOldColor1, 1);
		//mParent->_SetRenderTarget(mOldColor2, 2);

		mDevice->SetRenderState(D3DRS_ZENABLE, FALSE);

		RenderSystem* rendSys = mParent->mRenderSys;

		PostProcessPass* pass;
		PassList::iterator itr = mPasses.begin();
		int num = 0;
		while (itr != mPasses.end())
		{
			num++;
			pass = (PostProcessPass*)*itr;
			rendSys->SetPass(pass);
			pass->PPSetParam(this);

			// 更换渲染目标
			if(num == mPasses.size())
			{
				// 最后一个process 渲染到窗口缓冲
				mParent->_SetRenderTarget(mOldColor0, 0);
				mDevice->SetDepthStencilSurface(mOldDepth);
			}
			else
			{
				mParent->_SetRenderTarget(GetNextSurface(), 0);
				mDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, 0, 1.0f, 0);
			}
			rendSys->SetVertexBuffer(mVertexData);
			rendSys->SetIndexBuffer(mIndexData);
			rendSys->DrawIndexedPrimitive(RenderOperation::OT_TRIANGLE_LIST, 4, 2);
			itr++;
		}

		mDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	}


	void Effect::Resize( s32 width, s32 height )
	{
		mWidth = width;
		mHeight = height;

		RenderTargetImpl* pImpl = (RenderTargetImpl*)mNormalMap->mImpl;
		pImpl->mTexWidth = width;
		pImpl->mTexHeight = height;
		pImpl->Resize();

		pImpl = (RenderTargetImpl*)mDepthMap->mImpl;
		pImpl->mTexWidth = width;
		pImpl->mTexHeight = height;
		pImpl->Resize();

		pImpl = (RenderTargetImpl*)mRT[0]->mImpl;
		pImpl->mTexWidth = width;
		pImpl->mTexHeight = height;
		pImpl->Resize();

		pImpl = (RenderTargetImpl*)mRT[1]->mImpl;
		pImpl->mTexWidth = width;
		pImpl->mTexHeight = height;
		pImpl->Resize();

		PostProcessPass* pass;
		PassList::iterator itr = mPasses.begin();
		while (itr != mPasses.end())
		{
			pass = (PostProcessPass*)*itr;
			pass->Resize(mWidth, mHeight);
			itr++;
		}
	}

}