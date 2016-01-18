#include "RenderWindow.h"
#include "../ui/uimanager.h"
#include "RenderSystem.h"
#include "RenderTargetImpl.h"
#include "rendersystem/IRenderTarget.h"
#include "../scene/CameraImpl.h"
#include "scene/ICamera.h"
#include "RenderQueue.h"
#include "../scene/scenemgrimpl.h"
#include "scene/iscenemgr.h"
#include "../scene/submeshobject.h"
#include "../resource/materialimpl.h"
#include "resources/IMaterial.h"
#include "materialsystem/pass.h"
#include "rendersystem/itechnique.h"
#include "MaterialSystem/Effect.h"

namespace panda
{
	RenderWindow::RenderWindow( RenderSystem* renderSys )
		:mRenderSys(renderSys),
		mDefaultRt(NULL),
		mCamera(NULL),
		mSwapChainPtr(NULL)
	{
		mRenderQueue = new RenderQueue;
		mBackColor = 0xff12181e;
	}

	void RenderWindow::Init(s32 width, s32 height, IResMgr* pResMgr)
	{
		mWidth = width;
		mHeight = height;
		mUiManager = new uiManager(mRenderSys);
		mUiManager->mClientRect.size = Size(width, height);
		mTimer.BeginTickTime();

		mEffect = new Effect;
		mEffect->mParent = this;
		mEffect->mWidth = mWidth;
		mEffect->mHeight = mHeight;
		mEffect->Init(mDevicePtr, pResMgr);
	}

	void RenderWindow::Update( void )
	{
		// 场景
		if (NULL != mCamera)
		{
			// 清空渲染队列
			mRenderQueue->Clear();

			// 更新动画
			SceneMgrImpl* pSceneMgr = mCamera->GetSceneMgr()->mImpl;
			f32 time = (f32)mTimer.EndTickTime();
			mTimer.BeginTickTime();
			pSceneMgr->UpdateAnimation(time);
			pSceneMgr->FindVisibleObjects(mCamera, mRenderQueue);
		}

		mRenderSys->Clear(D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, mBackColor, 1.0f, 0);
		if(mRenderSys->BeginScene())
		{
			// 渲染场景
			IDirect3DSurface9* pBack = NULL;
			// 判断是否渲染到纹理
			if (!mRenderTargets.empty())
			{
				RenderTargetList::iterator itr = mRenderTargets.begin();
				while (itr != mRenderTargets.end())
				{
					RenderTargetImpl* pImpl = (RenderTargetImpl*)(*itr)->mImpl;
					mDevicePtr->SetRenderTarget(pImpl->mSurfaceIndex, pImpl->GetSurface());
					//SetRenderTarget(*itr, pImpl->mSurfaceIndex);
					itr++;
				}
			}
			else
			{
				if(NULL != mSwapChainPtr)
				{
					mSwapChainPtr->GetBackBuffer(0,D3DBACKBUFFER_TYPE_MONO, &pBack);
					mDevicePtr->SetRenderTarget(0, pBack);
				}
				else
				{
					//mDevicePtr->SetRenderTarget(0, mDefaultRt);
				}
			}

			D3DPERF_BeginEvent(0, _T("Scene"));

			//mEffect->BeginEffect();

			CameraImpl* pImpl = (CameraImpl*)mCamera->mImpl;
			mRenderSys->SetViewTransform(pImpl->GetViewMatrix());
			mRenderSys->SetProTransform(pImpl->GetProMatrix());

			_RenderQueue();

			//mEffect->EndEffect();

			D3DPERF_EndEvent();

			D3DPERF_BeginEvent(0, _T("UI"));
			// 渲染UI
			mUiManager->Render(mRenderSys->GetGraph2D(), (s32)mTimer.GetTickTime());
			
			D3DPERF_EndEvent();

			mRenderSys->EndScene();
			mRenderSys->Present();
		}
	}

	bool RenderWindow::IsAutoUpdate( void ) const
	{
		return mAutoUpdate;
	}

	void RenderWindow::SetAutoUpdate( bool bAuto )
	{
		mAutoUpdate = bAuto;
	}

	void RenderWindow::SetBackColor( const Color& color )
	{
		mBackColor = color;
	}

	const Color& RenderWindow::GetBackColor( void ) const
	{
		return mBackColor;
	}

	void RenderWindow::SetRenderTarget( IRenderTarget* pTarget, s32 index /*= 0*/ )
	{
		if(NULL != pTarget)
		{
			RenderTargetImpl* pImpl = (RenderTargetImpl*)pTarget->mImpl;
			pImpl->SetTexDirty();
			pImpl->mSurfaceIndex = index;

			if(mRenderTargets.empty())
			{
				mRenderTargets.push_back(pTarget);
			}
			else
			{
				RenderTargetList::iterator itr = mRenderTargets.begin();
				while (itr != mRenderTargets.end())
				{
					RenderTargetImpl* pImpl = (RenderTargetImpl*)(*itr)->mImpl;
					if(pImpl->mSurfaceIndex == index)
					{
						*itr = pTarget;
						return;
					}
					itr++;
				}
			}
		}
		else
		{
			RenderTargetList::iterator itr = mRenderTargets.begin();
			while (itr != mRenderTargets.end())
			{
				RenderTargetImpl* pImpl = (RenderTargetImpl*)(*itr)->mImpl;
				if(pImpl->mSurfaceIndex == index)
				{
					mRenderTargets.erase(itr);
					mDevicePtr->SetRenderTarget(index, NULL);
					return;
				}
				itr++;
			}
		}
	}

	IRenderTarget* RenderWindow::GetRenderTarget( s32 index )
	{
		RenderTargetList::iterator itr = mRenderTargets.begin();
		while (itr != mRenderTargets.end())
		{
			RenderTargetImpl* pImpl = (RenderTargetImpl*)(*itr)->mImpl;
			if(pImpl->mSurfaceIndex == index)
			{
				return *itr;
			}
			itr++;
		}
		return NULL;
	}

	void RenderWindow::SetCamera( ICamera* pCam )
	{
		mCamera = pCam;
		CameraImpl* pImpl = (CameraImpl*)pCam->mImpl;
		pImpl->SetScreenSize(mWidth, mHeight);
	}

	ICamera* RenderWindow::GetCamera( void )
	{
		return mCamera;
	}

	void RenderWindow::Resize( s32 width, s32 height )
	{
		if(mWidth == width && mHeight == height)
		{
			return;
		}
		if(0 == width || 0 == height)
		{
			return;
		}
		mWidth = width;
		mHeight = height;
		mUiManager->Resize(width, height);

		if (NULL != mCamera)
		{
			CameraImpl* pImpl = (CameraImpl*)mCamera->mImpl;
			pImpl->SetScreenSize(mWidth, mHeight);
		}
		mRenderSys->mD3dpp.BackBufferWidth = width;
		mRenderSys->mD3dpp.BackBufferHeight = height;
		mRenderSys->ResetDevice();
	}
	
	void RenderWindow::Release( void )
	{
		mRenderSys->RemoveRenderWindow(this);
		delete this;
	}

	IUiManager* RenderWindow::GetUiManager( void )
	{
		return mUiManager;
	}

	s32 RenderWindow::GetWidth( void ) const
	{
		return mWidth;
	}

	s32 RenderWindow::GetHeight( void ) const
	{
		return mHeight;
	}

	void RenderWindow::DeviceLost( void )
	{
		mUiManager->DeviceLost();
		if(NULL != mDefaultRt)
		{
			mDefaultRt->Release();
			mDefaultRt = NULL;
		}
	}

	void RenderWindow::ResetDevice( void )
	{
		mUiManager->ResetDevice();
		if(mDefaultRt != NULL)
		{
			mRenderSys->mDevicePtr->GetRenderTarget(0, &mDefaultRt);
		}
	}

	void RenderWindow::_RenderQueue( void )
	{
		for (s32 i = 0; i < RenderQueue::QueueCount; i++)
		{
			RenderQueue::ObjectList& temp = mRenderQueue->mQueues[i];
			RenderQueue::ObjectList::iterator itr = temp.begin();
			while (itr != temp.end())
			{
				(*itr)->Render(mRenderSys, mCamera);
				itr++;
			}
		}
	}

	void RenderWindow::_SetRenderTarget( IDirect3DSurface9* pSurface, s32 index )
	{
		mDevicePtr->SetRenderTarget(index, pSurface);
	}

	void RenderWindow::_SetRenderTarget( IRenderTarget* pTarget, s32 index )
	{
		RenderTargetImpl* pImpl = (RenderTargetImpl*)pTarget->mImpl;
		pImpl->SetTexDirty();
		mDevicePtr->SetRenderTarget(index, pImpl->GetSurface());
		mDevicePtr->SetDepthStencilSurface(pImpl->GetDepthSurface());
	}

	IDirect3DSurface9* RenderWindow::_GetRenderTarget( s32 index )
	{
		IDirect3DSurface9* pSurface = NULL;
		mDevicePtr->GetRenderTarget(index, &pSurface);
		return pSurface;
	}
}