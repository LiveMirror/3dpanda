#include "RenderSystem.h"
#include "RenderWindow.h"
#include "Graph2D.h"
#include "Graph3D.h"
#include "MaterialSystem/Pass.h"
#include "../resource/Vertexdata.h"
#include "../resource/Indexdata.h"


namespace panda
{
	RenderSystem::RenderSystem( void )
	{

	}

	RenderSystem::~RenderSystem( void )
	{

	}

	IRenderWindow* RenderSystem::CreateRenderWindow( RenderWindowParam* info /*= NULL*/ )
	{
		return NULL;
	}

	void RenderSystem::UpdateWindows( void )
	{
		std::list<RenderWindow*>::iterator itr = mRenderWindows.begin();
		while (itr != mRenderWindows.end())
		{
			if ((*itr)->IsAutoUpdate())
			{
				(*itr)->Update();
			}
			itr++;
		}
	}

	HWND RenderSystem::CreatehWnd( s32 width, s32 height, const tchar* wndTitle, bool Boder, WNDPROC lpfnWndProc )
	{
		HWND hWnd = NULL;
		//---------------------------------------
		//注册类
		//---------------------------------------
		HICON icon = (HICON)LoadImage(NULL, _T("../media/logo.ico"), IMAGE_ICON,0,0,LR_LOADFROMFILE);
		WNDCLASSEX wc = {sizeof(WNDCLASSEX),CS_CLASSDC | CS_DBLCLKS,lpfnWndProc,
			0L,0L,GetModuleHandle(NULL),
			icon,NULL,NULL,NULL,
			_T("PANDA_CLASS"),NULL};

		RegisterClassEx(&wc);

		if (NULL != wc.hInstance)
		{
			int nStyle;
			if (Boder)
			{
				nStyle = WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX/* | WS_THICKFRAME | WS_MAXIMIZEBOX*/;
			}
			else
			{
				nStyle = WS_CLIPCHILDREN | WS_CLIPSIBLINGS | WS_POPUP;
			}

			hWnd = CreateWindow(_T("PANDA_CLASS"), wndTitle, nStyle,
				200, 50, width, height, NULL, NULL, wc.hInstance, NULL);


			DragAcceptFiles(hWnd,TRUE);//把文件拖拽属性打开
		}
		return hWnd;
	}

	bool RenderSystem::InitDevice( s32 width, s32 height, HWND hWnd, bool fullScreen )
	{
		IDirect3D9*	pD3D = NULL;
		if(NULL == (pD3D = Direct3DCreate9(D3D_SDK_VERSION)))
		{
			return false;
		}

		// 显卡能力检查
		D3DCAPS9 caps;
		pD3D->GetDeviceCaps(
			D3DADAPTER_DEFAULT, // 主显示设备
			D3DDEVTYPE_HAL,		// 设备类型
			&caps); // 返回填充后的D3DCAPS9 结构，包含主显示设备的能力

		int nVertexPro = 0;
		if ( caps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT )
		{
			// 支持硬件顶点处理
			nVertexPro = D3DCREATE_HARDWARE_VERTEXPROCESSING;
		}
		else
		{
			// 不支持硬件顶点处理
			nVertexPro = D3DCREATE_SOFTWARE_VERTEXPROCESSING;
		}

		nVertexPro |= D3DCREATE_MULTITHREADED;

		D3DDISPLAYMODE d3ddm;
		pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT,&d3ddm);
		ZeroMemory(&mD3dpp, sizeof(mD3dpp));

		mD3dpp.Windowed = !fullScreen;				//窗口模式显示
		mD3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;	//表面交换链方式 D3DSWAPEFFECT_DISCARD //D3DSWAPEFFECT_COPY;

		mD3dpp.BackBufferCount = 1;					//后备缓冲表面的数量
		mD3dpp.BackBufferFormat = D3DFMT_A8R8G8B8;	// d3ddm.Format;		//后备缓冲表面像素格式D3DFMT_A8R8G8B8


		// 要开启抗锯齿功能时,须使用CreateRenderTarget来生成RT
		// CreateTexture生成的纹理不支持MultiSampleType
		mD3dpp.MultiSampleType = D3DMULTISAMPLE_4_SAMPLES;	// 抗锯齿 D3DMULTISAMPLE_4_SAMPLES D3DMULTISAMPLE_NONE
		mD3dpp.MultiSampleQuality = 0;						// 抗锯齿效果

		mD3dpp.EnableAutoDepthStencil = true;				// 深度缓冲
		mD3dpp.AutoDepthStencilFormat = D3DFMT_D24X8;		// 深度缓冲格式 24位深度缓冲 8位模版缓冲
		mD3dpp.Flags = 0;
		mD3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;			//刷新率
		mD3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
		mD3dpp.BackBufferWidth = width;
		mD3dpp.BackBufferHeight = height;

		// 调用方法IDirect3D9::CreateDevice创建设备对象，并获取
		// 接口IDirect3DDevice9的指针，我们将通过该指针操作设备对象
		if(FAILED( pD3D->CreateDevice(
			D3DADAPTER_DEFAULT,					// 使用缺省的显卡
			D3DDEVTYPE_HAL,						// 指定设备类型为HAL
			hWnd,								// Direct3D窗口的句柄
			nVertexPro,							// 顶点处理方式
			&mD3dpp, &mDevicePtr)))
		{
			return false;
		}

		D3DVIEWPORT9 vp;
		memset(&vp, 0, sizeof(vp));
		vp.Width = width;
		vp.Height = height;
		vp.MaxZ = 1;
		mDevicePtr->SetViewport(&vp);

		// Init 2D Graph
		mGraph2D = new Graph2D();
		if(!mGraph2D->Init(this))
		{
			// waring, The init of the UI is failed
		}

		mGraph3D = new Graph3D(this);

		InitRenderState();

		return true;
	}

	void RenderSystem::InitRenderState( void )
	{
		// 未启用纹理坐标变换
		// D3DTSS_TEXTURETRANSFORMFLAGS must be 0 when programmable pipeline is used
		mDevicePtr->SetTextureStageState(0,D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_DISABLE);

		// 设置Alpha混合
		mDevicePtr->SetRenderState( D3DRS_ALPHABLENDENABLE,   true );
		mDevicePtr->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		mDevicePtr->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		mDevicePtr->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
		mDevicePtr->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);

		// 开启Alpha检测
		mDevicePtr->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
		mDevicePtr->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATEREQUAL);
		mDevicePtr->SetRenderState(D3DRS_ALPHAREF, 0x20);

		mDevicePtr->SetRenderState( D3DRS_SHADEMODE, D3DSHADE_GOURAUD );
		mDevicePtr->SetRenderState(D3DRS_SEPARATEALPHABLENDENABLE, TRUE);

		//mDevicePtr->SetRenderState(AlphaToCoverageEnable, false);

		// 不背面剔除
		mDevicePtr->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

		// 纹理寻址
		mDevicePtr->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_MIRROR);
		mDevicePtr->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_MIRROR);

		//mDevicePtr->D3DPERF_BeginEvent

		//mTheRoot->OnDeviceInit(mDevicePtr);

		//mDevicePtr->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	}

	void RenderSystem::ResetDevice( void )
	{
		RenderWindowList::iterator itr = mRenderWindows.begin();
		while (itr != mRenderWindows.end())
		{
			(*itr)->DeviceLost();
			itr++;
		}
		mGraph2D->DeviceLost();

		HRESULT hr = mDevicePtr->Reset(&mD3dpp);
		if (FAILED(hr))
		{
			return;
		}

		mGraph2D->ResetDevice();

		itr = mRenderWindows.begin();
		while (itr != mRenderWindows.end())
		{
			(*itr)->ResetDevice();
			itr++;
		}

		InitRenderState();
	}
	

	void RenderSystem::GetRenderTarget( s32 index )
	{
		//mDevicePtr->GetRenderTarget()
	}

	IGraph2D* RenderSystem::GetGraph2D( void )
	{
		return mGraph2D;
	}
	
	void RenderSystem::Clear( u32 flag, Color color, f32 z, u32 stencil )
	{
		mDevicePtr->Clear(0, NULL, flag, color.value, z, stencil);
	}

	bool RenderSystem::BeginScene( void )
	{
		HRESULT hr = mDevicePtr->BeginScene();
		
		if (SUCCEEDED(hr))
		{
			return true;
		}
		return false;
	}

	void RenderSystem::EndScene( void )
	{
		mDevicePtr->EndScene();
	}

	s32 RenderSystem::Present()
	{
		HRESULT hr = mDevicePtr->Present(NULL,NULL,NULL,NULL);
		// 判断设备丢失
		if (hr == D3DERR_DEVICELOST)
		{
			// 重新得到设备
			// 需要重置设备
			if(mDevicePtr->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
			{
				ResetDevice();
			}
		}
		return hr;
	}

	ID3DXEffect* RenderSystem::CreateEffectFromFile( const tchar* path )
	{
		DWORD dwShaderFlags = D3DXFX_NOT_CLONEABLE;

#if defined( DEBUG ) || defined( _DEBUG )
		dwShaderFlags |= D3DXSHADER_DEBUG;
#endif
		ID3DXEffect*	effect;
		HRESULT hr;
		ID3DXBuffer* errorBuffer = NULL;
		hr = D3DXCreateEffectFromFile( mDevicePtr, path, NULL, NULL, dwShaderFlags, NULL, &effect, &errorBuffer );
		
		if(NULL != errorBuffer)
		{
			std::string msg = (const char*)errorBuffer->GetBufferPointer();
			MessageBoxA(NULL, msg.c_str() , "Fx compiler error", MB_ICONERROR);
			return NULL;
		}

		if(FAILED(hr))
		{
			return NULL;
		}
		return effect;
	}

	void RenderSystem::SetPass( IPass* pass )
	{
		Pass* p = (Pass*)pass;
		mDevicePtr->SetVertexShader(p->mVertexShader);
		mDevicePtr->SetPixelShader(p->mPixelShader);
	}

	IDirect3DVertexShader9* RenderSystem::CreateVertexShader( const char* src, u32 len, const char* mainFunName, IPass* refPass )
	{
		IDirect3DVertexShader9* pVertexShader;
		ID3DXBuffer* pFun;
		DWORD compileFlags = D3DXSHADER_DEBUG;
		LPD3DXBUFFER errors = 0;
		Pass* temp = (Pass*)refPass;
		HRESULT hr = D3DXCompileShader(src,
			len, 
			0,
			0, 
			mainFunName, 
			"vs_2_0", compileFlags, &pFun, &errors, &temp->mVConstTable);
		if (FAILED(hr))
		{
#ifdef _DEBUG
			::MessageBoxA(0, (char*)errors->GetBufferPointer(), 0, 0);
#endif
			errors->Release();
			return NULL;
		}

		hr = mDevicePtr->CreateVertexShader((DWORD*)pFun->GetBufferPointer(), &pVertexShader);
		if (FAILED(hr))
		{
			return NULL;
		}

		return pVertexShader;
	}

	IDirect3DPixelShader9* RenderSystem::CreatePixelShader( const char* src, u32 len, const char* mainFunName, IPass* refPass )
	{
		IDirect3DPixelShader9* pPixelShader;
		ID3DXBuffer* pFun;
		DWORD compileFlags = 0;
		LPD3DXBUFFER errors = 0;
		Pass* temp = (Pass*)refPass;
		HRESULT hr = D3DXCompileShader(src, len, 0, 0, mainFunName, 
			"ps_2_0", compileFlags, &pFun, &errors, &temp->mPConstTable);
		if (FAILED(hr))
		{
#ifdef _DEBUG
			::MessageBoxA(0, (char*)errors->GetBufferPointer(), 0, 0);
#endif
			errors->Release();
			return NULL;
		}

		hr = mDevicePtr->CreatePixelShader((DWORD*)pFun->GetBufferPointer(), &pPixelShader);
		if (FAILED(hr))
		{
			return NULL;
		}

		return pPixelShader;
	}

	void RenderSystem::SetVertexBuffer( VertexData* pData )
	{
		mDevicePtr->SetVertexDeclaration(pData->GetDeclare());
		pData->BindStreamSource();
	}

	void RenderSystem::SetIndexBuffer( IndexData* pData )
	{
		mDevicePtr->SetIndices(pData->mBuffer);
	}
	void RenderSystem::DrawIndexedPrimitive( RenderOperation::eValue oper, u32 vertexNum, s32 num )
	{
		mDevicePtr->DrawIndexedPrimitive((D3DPRIMITIVETYPE)oper, 0, 0, vertexNum, 0, num);
	}

	void RenderSystem::RemoveRenderWindow( RenderWindow* window )
	{
		RenderWindowList::iterator itr = mRenderWindows.begin();
		while (itr != mRenderWindows.end())
		{
			if(window == *itr)
			{
				mRenderWindows.erase(itr);
				break;
			}
			itr++;
		}
	}

	void RenderSystem::SetWorldTransform( u16 index, const Matrix44f& matrix )
	{
		mDevicePtr->SetTransform( D3DTS_WORLD, (const D3DXMATRIX*)&matrix);
	}

	void RenderSystem::SetViewTransform( const Matrix44f& matrix )
	{
		mDevicePtr->SetTransform(D3DTS_VIEW, (const D3DXMATRIX*)&matrix);
	}

	void RenderSystem::SetProTransform( const Matrix44f& matrix )
	{
		mDevicePtr->SetTransform(D3DTS_PROJECTION, (const D3DXMATRIX*)&matrix);
	}

	void RenderSystem::SetAlphaBlend( bool enable )
	{
		mDevicePtr->SetRenderState( D3DRS_ALPHABLENDENABLE, enable);
	}

	void RenderSystem::RenderWireframe( bool grid )
	{
		if(grid)
		{
			mDevicePtr->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
		}
		else
		{
			mDevicePtr->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
		}
	}
}