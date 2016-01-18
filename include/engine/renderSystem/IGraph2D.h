//
// Copyright(c) 1986-2100, TT, All Rights Reserved
// ����:  htz
// ����: 2013/1/14 11:42:39_
// ����:  2D ͼ�νӿ�
//

#ifndef _IGRAPH2D_2013114114239_
#define _IGRAPH2D_2013114114239_

#include "base/vector2d.h"
#include "base/color.h"
#include "base/Rect.h"
#include "base/Struct.h"

namespace panda
{
	class IFont;
	class ITexture;
	class IGraph2D
	{
	public:
		//---------------------------------------------------
		//! ����
		virtual void    DrawLine(const Vector2Dn& p1, const Vector2Dn& p2, Color color, f32 width = 1) = 0;
		virtual void    DrawLine(s32 x1, s32 y1, s32 x2, s32 y2, Color color, f32 width = 1) = 0;

		virtual void	DrawImage(ITexture* pTex, s32 x, s32 y, s32 width, s32 height) = 0;
		virtual void	DrawImage(ITexture* pTex, const Vector2Dn& pos, const Size& size) = 0;
		virtual void	DrawImage(ITexture* pTex, const Vector2Dn& pos, const Size& size, Color color) = 0;
		virtual void	DrawImage(ITexture* pTex, s32 x, s32 y, s32 width, s32 height, Color color) = 0;

		virtual void	DrawRect(const Rect& rect, Color c, f32 lineWidth = 1) = 0;
		virtual void	DrawRect(const Vector2Dn& pos, const Vector2Dn& size, Color color, f32 lineWidth = 1) = 0;
		virtual void	DrawRect(s32 x, s32 y, s32 width, s32 height, Color color, f32 lineWidth = 1) = 0;
		virtual void	DrawRoundedRect(const Vector2Dn& pos, const Vector2Dn& size, Color color, s32 Radius) = 0;

		// ��������
		virtual void	FillTriangle(s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3,Color color) = 0;

		virtual void	FillRect(const Rect& rect, Color color) = 0;
		virtual void	FillRect(const Vector2Dn& pos, const Vector2Dn& size, Color color) = 0;
		virtual void	FillRect(s32 x, s32 y, s32 width, s32 height, Color color) = 0;

		// segNum��Բ���߶�����(���ܴ���100)
		virtual void	DrawCircle(s32 centerX, s32 centerY, s32 radius, Color color, f32 lineWidth = 1, s32 segNum = 20) = 0;
		virtual void	FillCircle(s32 centerX, s32 centerY, s32 radius, Color color) = 0;

		// �������
		virtual void	FillRect(s32 x, s32 y, s32 width, s32 height, Color color1, Color color2, bool vertical = true) = 0;

		/*
		* format:��ʽ
		*/
		virtual void	DrawString(IFont* pFont, const Rect& r, const tstring& str, Color c, s32 format = FontFormat::CENTER | FontFormat::VCENTER) = 0;
		virtual void	DrawString(IFont* pFont, s32 x, s32 y, s32 width, s32 height, const tstring& str, Color c, 
			s32 format = FontFormat::CENTER | FontFormat::VCENTER) = 0;

		virtual void	SetScissor(const Rect& rect) = 0;
		virtual void	ScissorEnable(bool bEnabel) = 0;
	};
}

#endif // _IGRAPH2D_2013114114239_