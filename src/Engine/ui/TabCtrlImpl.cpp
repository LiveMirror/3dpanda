#include "TabCtrlImpl.h"
#include "ui/ITabctrl.h"
#include "../renderSystem/Graph2D.h"
#include "uiManager.h"

namespace panda
{
	TabCtrlImpl::TabCtrlImpl( void )
		:mSelectIndex(0),
		mTitleHeight(25),
		mMaxPageTitleWidth(80),
		mMouseOnIndex(-1)
	{

	}

	ITabPage* TabCtrlImpl::AddPage( const tstring& name )
	{
		ITabPage* page = new ITabPage;
		page->SetText(name);
		page->mImpl->OnBindUiMgr(mUiMgr);
		page->SetSize(mRect.size.width, mRect.size.height - mTitleHeight);
		AddChild(page);

		mPageTitleWidth = (f32)mRect.size.width;
		mPageTitleWidth /= mChilds.size();
		if(mPageTitleWidth > mMaxPageTitleWidth)
		{
			mPageTitleWidth = (f32)mMaxPageTitleWidth;
		}

		return page;
	}

	void TabCtrlImpl::Draw( Rect& rect, IGraph2D* graph )
	{
		Graph2D* g = (Graph2D*)graph;
		g->PushOffset(mRect.pos);
		
		DrawTitle(graph);

		// »­´°Ìå
		Vector2Dn title(0, mTitleHeight);
		g->PushOffset(title);

		if(!mChilds.empty() && mSelectIndex >= 0)
		{
			mChilds[mSelectIndex]->mImpl->Draw(mChilds[mSelectIndex]->mImpl->mRect, graph);
		}

		g->PopOffset(title);
		if(mDrawBorder)
		{
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, mBorderColor, mBorderSize);
		}
		g->PopOffset(mRect.pos);
	}

	void TabCtrlImpl::OnRender( IGraph2D* graph )
	{

	}

	void TabCtrlImpl::DrawTitle( IGraph2D* graph )
	{
		u32 num = mChilds.size();
		
		s32 x = 0;
		for(u32 i = 0; i < num; i++)
		{
			if(i == mSelectIndex)
			{
				graph->FillRect(x, 0, (s32)mPageTitleWidth, mTitleHeight, mBorderColor);
			}
			else if(i == mMouseOnIndex)
			{
				graph->FillRect(x, 0, (s32)mPageTitleWidth, mTitleHeight, mBackColor2);
			}
			graph->DrawString(mFont, x + 3, 0, (s32)mPageTitleWidth - 6, mTitleHeight, mChilds[i]->mImpl->mText, 
				mTextColor, FontFormat::CENTER | FontFormat::VCENTER/* | FontFormat::WORD_ELLIPSIS*/);

			x += (s32)mPageTitleWidth;
		}

		graph->DrawLine(0, mTitleHeight, mRect.size.width, mTitleHeight, mBorderColor);
	}

	ITabPage* TabCtrlImpl::GetPage( u32 index ) const
	{
		if(index >= mChilds.size())
		{
			index = mChilds.size() - 1;
		}
		return (ITabPage*)mChilds[index];
	}

	IControl* TabCtrlImpl::HitTest( s32 x, s32 y, Vector2Dn& outPt)
	{
		if (!mIsVisible)
		{
			return NULL;
		}

		s32 tempX = x - mRect.pos.x;
		s32 tempY = y - mRect.pos.y - mTitleHeight;

		if(!mChilds.empty() && mSelectIndex >= 0)
		{
			IControl* pCtrl;
			pCtrl = mChilds[mSelectIndex]->mImpl->HitTest(tempX, tempY, outPt);
			if(NULL != pCtrl)
			{
				return pCtrl;
			}
		}

		if(mRect.IsPointIn(x, y))
		{
			return mThis;
		}
		return NULL;
	}

	void TabCtrlImpl::OnMouseDown( MouseEventArgs& e )
	{
		if(e.y <= mTitleHeight)
		{
			u32 index = (u32)(e.x / mPageTitleWidth);
			if(mSelectIndex != index && index < mChilds.size())
			{
				mSelectIndex = index;
				mOnSelPageChanged(mThis);
			}
		}
	}

	void TabCtrlImpl::OnMouseMove( MouseEventArgs& e )
	{
		if(e.y <= mTitleHeight)
		{
			u32 index =  (u32)(e.x / mPageTitleWidth);
			if(mMouseOnIndex != index && index < mChilds.size())
			{
				mMouseOnIndex = index;
				mTipText = mChilds[mMouseOnIndex]->GetToolTip();
				mUiMgr->ResetHover();
			}
		}
	}

	Vector2Dn TabCtrlImpl::PointToScreen( s32 x, s32 y, IControl* pChild/* = NULL*/)
	{
		Vector2Dn p(x, y + mTitleHeight);
		if(mParent != NULL)
		{
			p += mParent->mImpl->PointToScreen(mRect.pos.x, mRect.pos.y);
		}
		else
		{
			p += mRect.pos;
		}
		return p;
	}

	void TabCtrlImpl::OnMouseLevae( void )
	{
		mMouseOnIndex = -1;
	}

	ITabPage* TabCtrlImpl::GetSelPage( void ) const
	{
		if(mSelectIndex < 0)
		{
			return 0;
		}
		return (ITabPage*)mChilds[mSelectIndex];
	}
}