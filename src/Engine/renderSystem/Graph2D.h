//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// 作者:  htz
// 日期: 2013/1/14 14:20:31_
// 描述:  
//

#ifndef _GRAPH2D_2013114142031_
#define _GRAPH2D_2013114142031_

#include "base/Config.h"
#include <d3dx9.h>
#include "renderSystem/IGraph2D.h"
#include "base/Rect.h"

namespace panda
{
	class RenderSystem;
	class ImageEffect;
	class RectEffect;
	class CircleEffect;
	class IFont;
	class Graph2D:public IGraph2D
	{
	public:
		Graph2D(void);
		~Graph2D(void);
		bool			Init(RenderSystem* renderSys);

		//---------------------------------------------------
		//! 画线
		virtual void    DrawLine(const Vector2Dn& p1, const Vector2Dn& p2, Color color, f32 width = 1);
		virtual void    DrawLine(s32 x1, s32 y1, s32 x2, s32 y2, Color color, f32 width = 1);

		virtual void	DrawImage(ITexture* pTex, s32 x, s32 y, s32 width, s32 height);
		virtual void	DrawImage(ITexture* pTex, const Vector2Dn& pos, const Size& size);
		virtual void	DrawImage(ITexture* pTex, const Vector2Dn& pos, const Size& size, Color color);
		virtual void	DrawImage(ITexture* pTex, s32 x, s32 y, s32 width, s32 height, Color color);

		virtual void	DrawRect(const Rect& rect, Color c, f32 lineWidth = 1);
		virtual void	DrawRect(const Vector2Dn& pos, const Vector2Dn& size, Color color, f32 lineWidth = 1);
		virtual void	DrawRect(s32 x, s32 y, s32 width, s32 height, Color color, f32 lineWidth = 1);
		virtual void	DrawRoundedRect(const Vector2Dn& pos, const Vector2Dn& size, Color color, s32 Radius);

		virtual void	FillTriangle(s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3,Color color);

		virtual void	FillRect(const Vector2Dn& pos, const Vector2Dn& size, Color color);
		virtual void	FillRect(s32 x, s32 y, s32 width, s32 height, Color color);
		virtual void	FillRect(const Rect& rect, Color color);

		virtual void	DrawCircle(s32 centerX, s32 centerY, s32 radius, Color color, f32 lineWidth = 1, s32 segNum = 20);
		virtual void	FillCircle(s32 centerX, s32 centerY, s32 radius, Color color);

		// 渐进填充
		virtual void	FillRect(s32 x, s32 y, s32 width, s32 height, Color color1, Color color2, bool vertical = true);

		virtual void	DrawString(IFont* pFont, const Rect& r, const tstring& str, Color c, s32 format = FontFormat::CENTER | FontFormat::VCENTER);
		virtual void	DrawString(IFont* pFont, s32 x, s32 y, s32 width, s32 height, const tstring& str, Color c, 
			s32 format = FontFormat::CENTER | FontFormat::VCENTER);

		virtual void	SetScissor(const Rect& rect);
		virtual void	ScissorEnable(bool bEnabel);

		void			BenginGraph(s32 width, s32 height);
		void			DrawPrimitive(void);

		// 圆点位置的偏移量
		void				PushOffset(const Vector2Dn& pos);
		void				PopOffset(const Vector2Dn& pos);
		const Vector2Dn&	GetOffset(void)const;

		void			DeviceLost(void);
		void			ResetDevice(void);
		bool			InitEffect(void);

	public:
		RenderSystem*			mRenderSys;		// 设备指针
		
		IDirect3DVertexBuffer9*	mVertexBuf;
		IDirect3DIndexBuffer9*	mIndexBuf;
		D3DXVECTOR2*			mLineBuf;
		D3DXVECTOR2*			mCircleBuf;
		ID3DXLine*		mLine;
		ImageEffect*	mImageFx;
		RectEffect*		mRectFx;
		CircleEffect*	mCircleFx;
		
		Vector2Dn				mOffsetPos;
		Rect					mTempRect;
	};
}

#endif // _GRAPH2D_2013114142031_