////////////////////////////////////////////////////////
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  Hu Tianzhi
// ����: 2014-2-22 10:43:43
// ����:  
////////////////////////////////////////////////////////

#ifndef	_Tian_2014222104343_H_
#define	_Tian_2014222104343_H_

#include "core.h"
#include "renderSystem/IRenderSystem.h"
#include <d3dx9.h>
#include "base/Matrix44.h"

namespace panda
{
	class IGraph2D;
	class Graph2D;
	class Graph3D;
	class RenderWindow;
	class IPass;
	class VertexData;
	class IndexData;

	/*
	*
	*/
	class RenderSystem:public IRenderSystem
	{
	public:
		RenderSystem(void);
		~RenderSystem(void);
		//----------------------------------------
		//! ����һ����Ⱦ����
		virtual IRenderWindow*	CreateRenderWindow(RenderWindowParam* info = NULL);

		virtual void			UpdateWindows(void);

		virtual void			RenderWireframe(bool grid);

		void					SetPass(IPass* pass);

		// ��������shader
		IDirect3DVertexShader9*	CreateVertexShader(const char* src, u32 len, const char* mainFunName, IPass* refPass);
		// ��������shader
		IDirect3DPixelShader9*	CreatePixelShader(const char* src, u32 len, const char* mainFunName, IPass* refPass);

		void					SetVertexBuffer(VertexData* pData);
		void					SetIndexBuffer(IndexData* pData);
		void					DrawIndexedPrimitive(RenderOperation::eValue oper, u32 vertexNum, s32 num);	

		// �Ӷ������Ƴ�
		void					RemoveRenderWindow(RenderWindow* window);

		void					SetAlphaBlend(bool enable);

	public:
		IGraph2D*				GetGraph2D(void);
		HWND					CreatehWnd(s32 width, s32 height, const tchar* wndTitle, bool Boder, WNDPROC lpfnWndProc);
		bool					InitDevice(s32 width, s32 height, HWND hWnd, bool fullScreen);
		void					ResetDevice(void);

		void					SetWorldTransform(u16 index, const Matrix44f& matrix);
		void					SetViewTransform(const Matrix44f& matrix);
		void					SetProTransform(const Matrix44f& matrix);

		bool					BeginScene(void);
		void					EndScene(void);
		void					Clear(u32 flag, Color color, f32 z, u32 stencil);
		s32						Present();
		void					GetRenderTarget(s32 index);

		ID3DXEffect*			CreateEffectFromFile(const tchar* path);
	protected:
		void					InitRenderState(void);

	public:
		Graph2D*					mGraph2D;
		Graph3D*					mGraph3D;
		IDirect3DDevice9*			mDevicePtr;		// �豸ָ��
		D3DPRESENT_PARAMETERS		mD3dpp;

		typedef std::list<RenderWindow*>	RenderWindowList;
		RenderWindowList			mRenderWindows;
	};
}

#endif _Tian_2014222104343_H_