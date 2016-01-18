#include "Panda.h"
#include "rendersystem/RenderSystem.h"
#include "rendersystem/renderwindow.h"
#include "ui/uiManager.h"
#include "ui/IUiInput.h"
#include "resource/ResourceMgr.h"

namespace panda
{
	extern "C" ENGINE_API IPanda* TheEngine()
	{
		static IPanda* _Panda = NULL;
		if (NULL == _Panda)
		{
			_Panda = new Panda;
		}
		return _Panda;
	}

	static IUiInput* gInput = NULL;
	static RenderWindow* defualtWnd = NULL;
	LRESULT WINAPI MsgProc( HWND hWnd,UINT msg,WPARAM wParam,LPARAM lParam )
	{
		static int posX, posY;
		switch(msg)
		{
		case WM_DESTROY:
			{
				PostQuitMessage(0);
				exit(0);
				return 0;
			}
		case WM_MOUSEMOVE:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)wParam;
					gInput->OnMouseMove(e);
				}				
				break;
			}
		case WM_MBUTTONDOWN:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)(wParam | MouseButtons::MButton);
					gInput->OnMouseDown(e);
				}	
				break;
			}
		case WM_RBUTTONDOWN:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)(wParam | MouseButtons::RButton);
					gInput->OnMouseDown(e);
				}	
				break;
			}
		case WM_LBUTTONDOWN:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)(wParam | MouseButtons::LButton);
					gInput->OnMouseDown(e);
				}	
				break;
			}
		case WM_MBUTTONDBLCLK:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)(wParam | MouseButtons::MButton);
					gInput->OnMouseDClick(e);
				}	
				break;
			}
		case WM_RBUTTONDBLCLK:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)(wParam | MouseButtons::RButton);
					gInput->OnMouseDClick(e);
				}	
				break;
			}
		case WM_LBUTTONDBLCLK:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)(wParam | MouseButtons::LButton);
					gInput->OnMouseDClick(e);
				}	
				break;
			}
		case WM_MBUTTONUP:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)(wParam | MouseButtons::MButton);
					gInput->OnMouseUp(e);
				}
				break;
			}
		case WM_RBUTTONUP:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)(wParam | MouseButtons::RButton);
					gInput->OnMouseUp(e);
				}
				break;
			}
		case WM_LBUTTONUP:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					e.button = (MouseButtons::eValue)(wParam | MouseButtons::LButton);
					gInput->OnMouseUp(e);
				}
				break;
			}
		case WM_KEYDOWN:
			{
				if(NULL != gInput)
				{
					KeyEventArgs e;
					e.keyCode = (s32)wParam;
					gInput->OnKeyDown(e);
				}
				break;
			}
		case WM_MOUSEWHEEL:
			{
				if(NULL != gInput)
				{
					MouseEventArgs e;
					e.delta = GET_WHEEL_DELTA_WPARAM(wParam);
					e.button = (MouseButtons::eValue)GET_KEYSTATE_WPARAM(wParam);
					e.x = LOWORD(lParam);
					e.y = HIWORD(lParam);
					gInput->OnMouseWheel(e);
				}
				break;
			}
		case WM_CHAR:
			{
				if(NULL != gInput)
				{
					gInput->OnChar((s32)wParam);
				}
				break;
			}
		case WM_SIZE:
			{
				if(NULL != gInput)
				{
					posX = LOWORD(lParam);
					posY = HIWORD(lParam);
					if(NULL != defualtWnd)
					{
						defualtWnd->Resize(posX, posY);
					}
				}
				break;
			}
		}
		return DefWindowProc(hWnd,msg,wParam,lParam);
	}


	Panda::Panda( void )
		:mRenderSystem(NULL)
	{
		srand((unsigned)time(NULL));
	}

	IRenderWindow* Panda::InitDevice( RenderWindowParam* info /*= NULL*/, void* device /*= NULL*/ )
	{
		// 重复调用初始化
		if(NULL != mRenderSystem)
		{
			return false;
		}

		// 初始化渲染器
		mRenderSystem = new RenderSystem();

		if(NULL != device)
		{
			mRenderSystem->mDevicePtr = (IDirect3DDevice9*)device;
		}
		else
		{
			static RenderWindowParam _info;
			if(NULL == info)
			{
				info = &_info;
			}

			// 如果未传入窗口句柄
			bool regestInput = false;
			if (0 == info->hWnd)
			{
				if(NULL == info->fun)
				{
					regestInput = true;
					info->fun = MsgProc;
				}
				info->hWnd = mRenderSystem->CreatehWnd(info->nWidth, info->nHeight, info->strTitle.c_str(), info->bBoder, info->fun);
				if (NULL == info->hWnd)
				{
					return false;
				}
				::ShowWindow(info->hWnd, SW_SHOW);
			}

			RECT rect;
			GetClientRect(info->hWnd, &rect);
			info->nWidth = rect.right;
			info->nHeight = rect.bottom;
			if(!mRenderSystem->InitDevice(info->nWidth, info->nHeight, info->hWnd, info->bFullScereen))
			{
				return NULL;
			}

			// 初始化资源管理器
			mResMgr = new ResourceMgr;
			mResMgr->mRenderMgr = mRenderSystem;
			mResMgr->BindDevice(mRenderSystem->mDevicePtr);

			RenderWindow* pWnd = new RenderWindow(mRenderSystem);
			defualtWnd = pWnd;
			pWnd->mDevicePtr = mRenderSystem->mDevicePtr;
			pWnd->Init(info->nWidth, info->nHeight, mResMgr);
			mRenderSystem->mDevicePtr->GetRenderTarget(0, &pWnd->mDefaultRt);
			if(regestInput)
			{
				gInput = (IUiInput*)pWnd->mUiManager;
			}
			mRenderSystem->mRenderWindows.push_back(pWnd);

			return pWnd;
		}
		return NULL;
	}

	ISceneMgr* Panda::CreateSceneMgr( void ) const
	{
		ISceneMgr* pMgr = new ISceneMgr;
		return pMgr;
	}

	void Panda::Run( void )
	{
		MSG _Msg;
		while (true)
		{
			if (PeekMessage(&_Msg,NULL,0,0,PM_REMOVE))
			{
				TranslateMessage(&_Msg);
				DispatchMessage(&_Msg);
			}
			else
			{
				Sleep(1);
			}
			_update();
		}
	}

	void Panda::Release( void )
	{
		if(NULL != mRenderSystem)
		{
			delete mRenderSystem;
			mRenderSystem = NULL;
		}
	}

	void Panda::_update( void )
	{
		mRenderSystem->UpdateWindows();
	}

	IRenderSystem* Panda::GetRenderSystem( void )
	{
		return mRenderSystem;
	}

	IResMgr* Panda::GetResMgr( void )
	{
		return mResMgr;
	}
}