#include "Graph2D.h"
#include "RenderSystem.h"
#include "uieffect/ImageEffect.h"
#include "uieffect/RectEffect.h"
#include "uieffect/CircleEffect.h"
#include "../ui/Font.h"

namespace panda
{
	struct Vertex
	{
		Vector3Df pos;
		Vector2Df uv;

		static const s32 FVF;
	};
	const s32 Vertex::FVF = D3DFVF_XYZ | D3DFVF_TEX1;

	Graph2D::Graph2D( void )
	{

	}

	Graph2D::~Graph2D( void )
	{


	}

	bool Graph2D::InitEffect( void )
	{
		mImageFx = new ImageEffect;
		mImageFx->mEffect = mRenderSys->CreateEffectFromFile(_T("../shader/image.fx"));
		if(!mImageFx->mEffect)
		{
			return false;
		}
		mImageFx->InitEffect();

		mRectFx = new RectEffect;
		mRectFx->mEffect = mRenderSys->CreateEffectFromFile(_T("../shader/rect.fx"));
		if(!mRectFx->mEffect)
		{
			return false;
		}
		mRectFx->InitEffect();

		mCircleFx = new CircleEffect;
		mCircleFx->mEffect = mRenderSys->CreateEffectFromFile(_T("../shader/circle.fx"));
		if(!mCircleFx->mEffect)
		{
			return false;
		}
		mCircleFx->InitEffect();

		return true;
	}

	bool Graph2D::Init(RenderSystem* renderSys)
	{
		mRenderSys = renderSys;

		if(!InitEffect())
		{
			return false;
		}

		D3DXCreateLine(mRenderSys->mDevicePtr, &mLine);
		mLineBuf = new D3DXVECTOR2[5];

		mCircleBuf = new D3DXVECTOR2[101];

		mRenderSys->mDevicePtr->CreateVertexBuffer(4 * sizeof(Vertex), 0, Vertex::FVF, D3DPOOL_MANAGED, &mVertexBuf, 0);

		// 初始化数据
		Vertex* buf;
		mVertexBuf->Lock(0, 0, (void**)&buf, 0);

		buf[0].pos = Vector3Df(0,0,0);
		buf[0].uv = Vector2Df(0,0);
		buf[1].pos = Vector3Df(1, 0, 0);
		buf[1].uv = Vector2Df(1, 0);
		buf[2].pos = Vector3Df(1,-1,0);
		buf[2].uv = Vector2Df(1,1);
		buf[3].pos = Vector3Df(0,-1,0);
		buf[3].uv = Vector2Df(0,1);

		mVertexBuf->Unlock();

		mRenderSys->mDevicePtr->CreateIndexBuffer(sizeof(s32) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &mIndexBuf, 0);
		u16* indexBuf;
		mIndexBuf->Lock(0, 0, (void**)&indexBuf, 0);
		indexBuf[0] = 0;
		indexBuf[1] = 1;
		indexBuf[2] = 2;

		indexBuf[3] = 0;
		indexBuf[4] = 2;
		indexBuf[5] = 3;
		mIndexBuf->Unlock();

		return true;
	}

	void Graph2D::BenginGraph( s32 width, s32 height )
	{
		mRectFx->Set2DSize(width, height);
		mCircleFx->Set2DSize(width, height);
		mImageFx->Set2DSize(width, height);
		mRenderSys->mDevicePtr->SetStreamSource(0, mVertexBuf, 0, sizeof(Vertex));
		mRenderSys->mDevicePtr->SetIndices(mIndexBuf);
		mRenderSys->mDevicePtr->SetFVF(Vertex::FVF);
	}

	void Graph2D::DrawPrimitive( void )
	{
		mRenderSys->mDevicePtr->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	}


	void Graph2D::DrawImage( ITexture* pTex, const Vector2Dn& pos, const Size& size )
	{
		if(NULL == pTex) return;
		mImageFx->SetSize(size.width, size.height);
		mImageFx->SetPos(pos.x + mOffsetPos.x, pos.y + mOffsetPos.y);
		mImageFx->SetTex(pTex);
		mImageFx->BeginEffect(mImageFx->mTech);
		DrawPrimitive();
		mImageFx->EndEffect();
	}

	void Graph2D::DrawImage( ITexture* pTex, const Vector2Dn& pos, const Size& size, Color color )
	{
		if(NULL == pTex) return;
		mImageFx->SetSize(size.width, size.height);
		mImageFx->SetPos(pos.x + mOffsetPos.x, pos.y + mOffsetPos.y);
		mImageFx->SetTex(pTex);
		mImageFx->SetColor(color);

		mImageFx->BeginEffect(mImageFx->mColorTech);
		DrawPrimitive();
		mImageFx->EndEffect();
	}

	void Graph2D::DrawImage( ITexture* pTex, s32 x, s32 y, s32 width, s32 height )
	{
		if(NULL == pTex) return;
		mImageFx->SetSize(width, height);
		mImageFx->SetPos(x + mOffsetPos.x, y + mOffsetPos.y);
		mImageFx->SetTex(pTex);
		mImageFx->BeginEffect(mImageFx->mTech);
		DrawPrimitive();
		mImageFx->EndEffect();
	}

	void Graph2D::DrawImage( ITexture* pTex, s32 x, s32 y, s32 width, s32 height, Color color )
	{
		if(NULL == pTex) return;
		mImageFx->SetSize(width, height);
		mImageFx->SetPos(x + mOffsetPos.x, y + mOffsetPos.y);
		mImageFx->SetTex(pTex);
		mImageFx->SetColor(color);

		mImageFx->BeginEffect(mImageFx->mColorTech);
		DrawPrimitive();
		mImageFx->EndEffect();
	}

	void Graph2D::DrawRect( const Vector2Dn& pos, const Vector2Dn& size, Color c , f32 lineWidth/* = 1*/)
	{
		DrawRect(pos.x, pos.y, size.x, size.y, c, lineWidth);
	}

	void Graph2D::DrawRect( s32 x, s32 y, s32 width, s32 height, Color color , f32 lineWidth/* = 1*/)
	{
		if(1 == lineWidth)
		{
			x += mOffsetPos.x;
			y += mOffsetPos.y;
			mLineBuf[0].x = (f32)x;
			mLineBuf[0].y = (f32)y;
			mLineBuf[1].x = (f32)x + width;
			mLineBuf[1].y = (f32)y;
			mLineBuf[2].x = (f32)x + width;
			mLineBuf[2].y = (f32)y + height;
			mLineBuf[3].x = (f32)x;
			mLineBuf[3].y = (f32)y + height;
			mLineBuf[4] = mLineBuf[0];
			mLine->SetWidth(lineWidth);
			mLine->Begin();
			mLine->Draw(mLineBuf, 5, color.value);
			mLine->End();
		}
		else
		{
			f32 add = (lineWidth - 1) / 2;
			DrawLine((s32)x - add, y, x + width + add, y, color, lineWidth);
			DrawLine(x + width, y - add, x + width, y + height + add, color, lineWidth);
			DrawLine(x + width + add, y + height, x - add, y + height, color, lineWidth);
			DrawLine(x, y + height + add, x, y - add, color, lineWidth);
		}
	}

	void Graph2D::DrawRect( const Rect& rect, Color c , f32 lineWidth/* = 1*/)
	{
		DrawRect(rect.pos.x, rect.pos.y, rect.size.width, rect.size.height, c, lineWidth);
	}
	
	void Graph2D::DrawRoundedRect( const Vector2Dn& pos, const Vector2Dn& size, Color color, s32 Radius )
	{

	}

	void Graph2D::DrawLine( const Vector2Dn& p1, const Vector2Dn& p2, Color color, f32 width/* = 1*/)
	{
		DrawLine(p1.x, p1.y, p2.x, p2.y, color, width);
	}

	void Graph2D::DrawLine( s32 x1, s32 y1, s32 x2, s32 y2, Color color , f32 width/* = 1*/)
	{
		mLineBuf[0].x = (f32)x1 + mOffsetPos.x;
		mLineBuf[0].y = (f32)y1 + mOffsetPos.y;
		mLineBuf[1].x = (f32)x2 + mOffsetPos.x;
		mLineBuf[1].y = (f32)y2 + mOffsetPos.y;
		mLine->SetWidth(width);
		mLine->Begin();
		mLine->Draw(mLineBuf, 2, color.value);
		mLine->End();
	}

	void Graph2D::FillRect( const Vector2Dn& pos, const Vector2Dn& size, Color color )
	{
		FillRect(pos.x, pos.y, size.x, size.y, color);
	}

	void Graph2D::FillRect( s32 x, s32 y, s32 width, s32 height, Color color )
	{
		mRectFx->SetColor(color);
		mRectFx->SetSize(width, height);
		mRectFx->SetPos(x + mOffsetPos.x, y + mOffsetPos.y);
		mRectFx->BeginEffect(mRectFx->mTech);
		DrawPrimitive();
		mRectFx->EndEffect();
	}

	void Graph2D::FillRect( s32 x, s32 y, s32 width, s32 height, Color color1, Color color2, bool vertical/* = true*/)
	{
		mRectFx->SetColor(color1);
		mRectFx->SetColor2(color2);
		mRectFx->SetSize(width, height);
		mRectFx->SetPos(x + mOffsetPos.x, y + mOffsetPos.y);
		mRectFx->SetVertical(vertical);
		mRectFx->BeginEffect(mRectFx->mGradualTech);
		DrawPrimitive();
		mRectFx->EndEffect();
	}

	void Graph2D::FillRect( const Rect& rect, Color color )
	{
		FillRect(rect.pos.x, rect.pos.y, rect.size.width, rect.size.height, color);
	}

	void Graph2D::SetScissor( const Rect& rect )
	{
		RECT r;
		r.top = rect.pos.y + mOffsetPos.y;
		r.left = rect.pos.x + mOffsetPos.x;
		r.bottom = r.top + rect.size.height;
		r.right = r.left + rect.size.width;
		mRenderSys->mDevicePtr->SetScissorRect(&r);
	}

	void Graph2D::ScissorEnable( bool bEnabel )
	{
		mRenderSys->mDevicePtr->SetRenderState(D3DRS_SCISSORTESTENABLE, bEnabel);
	}

	void Graph2D::FillCircle( s32 centerX, s32 centerY, s32 radius, Color color)
	{
		mCircleFx->SetCenter(centerX + mOffsetPos.x, centerY + mOffsetPos.y);
		mCircleFx->SetRadius((f32)radius);
		mCircleFx->SetColor(color);

		mCircleFx->BeginEffect(mCircleFx->mFillTech);
		DrawPrimitive();
		mCircleFx->EndEffect();
	}

	void Graph2D::DrawCircle( s32 centerX, s32 centerY, s32 radius, Color color, f32 lineWidth /*= 1*/, s32 segNum/* = 20 */)
	{
		centerX += mOffsetPos.x;
		centerY += mOffsetPos.y;

		f32 d = 0;
		for(s32 i = 0; i <= segNum; i++)
		{
			d = i * PI * 2 / segNum;
			mCircleBuf[i].x = centerX + math::Sin(d) * radius;
			mCircleBuf[i].y = centerY + math::Cos(d) * radius;
		}

		mLine->SetWidth(lineWidth);
		mLine->Begin();
		mLine->Draw(mCircleBuf, segNum + 1, color.value);
		mLine->End();
	}

	void Graph2D::DrawString( IFont* pFont, const Rect& r, const tstring& str, Color c , s32 format/* = FontFormat::CENTER | FontFormat::VCENTER*/)
	{
		Font* f = (Font*)pFont;
		mTempRect = r;
		mTempRect.pos += mOffsetPos;
		f->DrawString(mTempRect, str, c, format);
	}

	void Graph2D::DrawString( IFont* pFont, s32 x, s32 y, s32 width, s32 height, const tstring& str, Color c, s32 format /*= FontFormat::CENTER | FontFormat::VCENTER*/ )
	{
		Font* f = (Font*)pFont;
		mTempRect.pos = mOffsetPos;
		mTempRect.pos.x += x;
		mTempRect.pos.y += y;
		mTempRect.size.width = width;
		mTempRect.size.height = height;
		f->DrawString(mTempRect, str, c, format);
	}

	void Graph2D::PushOffset( const Vector2Dn& pos )
	{
		mOffsetPos += pos;
	}

	void Graph2D::PopOffset( const Vector2Dn& pos )
	{
		mOffsetPos -= pos;
	}

	void Graph2D::FillTriangle( s32 x1, s32 y1, s32 x2, s32 y2, s32 x3, s32 y3,Color color )
	{

	}

	const Vector2Dn& Graph2D::GetOffset( void ) const
	{
		return mOffsetPos;
	}
	
	void Graph2D::DeviceLost( void )
	{
		mImageFx->DeviceLost();
		mRectFx->DeviceLost();
		mCircleFx->DeviceLost();
		mLine->OnLostDevice();
	}

	void Graph2D::ResetDevice( void )
	{
		mImageFx->ResetDevice();
		mRectFx->ResetDevice();
		mCircleFx->ResetDevice();
		mLine->OnResetDevice();
	}
}