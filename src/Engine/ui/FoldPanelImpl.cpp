#include "FoldPanelImpl.h"
#include "ui/IFoldPanel.h"
#include "renderSystem/IGraph2D.h"
#include "../renderSystem/Graph2D.h"

namespace panda
{
	FoldPanelImpl::FoldPanelImpl( void )
		:mSelectIndex(-1),
		mTitleHeight(25)
	{

	}

	void FoldPanelImpl::Draw( Rect& rect, IGraph2D* graph )
	{
		// 控件不可见 不绘制
		// 与可见区域不相交，不绘制
		if(!mIsVisible || !rect.Intersect(mRect))
		{
			return;
		}

		Graph2D* g = (Graph2D*)graph;
		g->PushOffset(mRect.pos);

		DrawTitle(graph);

		if(!mChilds.empty() && mSelectIndex >= 0)
		{
			mChilds[mSelectIndex]->mImpl->Draw(mChilds[mSelectIndex]->mImpl->mRect, graph);
		}

		if(mDrawBorder)
		{
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, mBorderColor, mBorderSize);
		}
		g->PopOffset(mRect.pos);
	}

	void FoldPanelImpl::OnRender( IGraph2D* graph )
	{

	}

	void FoldPanelImpl::DrawTitle( IGraph2D* graph )
	{
		u32 num = mChilds.size();
		s32 y = 0;
		s32 i = 0;
		for(; i <= mSelectIndex; i++)
		{
			if(i == mSelectIndex)
			{
				graph->FillRect(0, y, mRect.size.width, mTitleHeight, mBorderColor);
			}
			else if(i == mMouseOnIndex)
			{
				graph->FillRect(0, y, mRect.size.width, mTitleHeight, mBackColor2);
			}
			graph->DrawString(mFont, 0, y, mRect.size.width, mTitleHeight,  mChilds[i]->mImpl->mText, mTextColor);
			graph->DrawRect(0, y, mRect.size.width, mTitleHeight, mBorderColor);
			y += mTitleHeight;
		}

		y = mRect.size.height - (mChilds.size() - mSelectIndex - 1) * mTitleHeight;
		for(; i < num; i++)
		{
			if(i == mSelectIndex)
			{
				graph->FillRect(0, y, mRect.size.width, mTitleHeight, mBorderColor);
			}
			else if(i == mMouseOnIndex)
			{
				graph->FillRect(0, y, mRect.size.width, mTitleHeight, mBackColor2);
			}
			graph->DrawString(mFont, 0, y, mRect.size.width, mTitleHeight,  mChilds[i]->mImpl->mText, mTextColor);
			graph->DrawRect(0, y, mRect.size.width, mTitleHeight, mBorderColor);
			y += mTitleHeight;
		}
	}

	IFoldPage* FoldPanelImpl::AddPage( const tstring& name )
	{
		IFoldPage* page = new IFoldPage;
		page->SetText(name);
		page->mImpl->OnBindUiMgr(mUiMgr);
		AddChild(page);

		if(-1 == mSelectIndex)
		{
			mSelectIndex = 0;
		}

		Size s = mRect.size;
		s.height = s.height - mTitleHeight * mChilds.size();
		s32 y = mTitleHeight;
		for(s32 i = 0; i < mChilds.size(); i++)
		{
			mChilds[i]->SetSize(s.width, s.height);
			mChilds[i]->SetPos(0, y);
			y += mTitleHeight;
		}
		mPanelOffset.y = mTitleHeight * (mSelectIndex + 1);
		return page;
	}

	void FoldPanelImpl::OnMouseMove( MouseEventArgs& e )
	{
		mMouseOnIndex = -1;
		if(e.y <= mPanelOffset.y)
		{
			u32 index =  e.y / mTitleHeight;
			if(mMouseOnIndex != index && index < mChilds.size())
			{
				mMouseOnIndex = index;
			}
		}
		else
		{
			s32 y = mRect.size.height - e.y;
			u32 count = y / mTitleHeight;
			s32 index = mChilds.size() - count - 1;
			if(mMouseOnIndex != index && index < mChilds.size())
			{
				mMouseOnIndex = index;
			}
		}
	}

	void FoldPanelImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);
		if(mSelectIndex != mMouseOnIndex && -1 != mMouseOnIndex)
		{
			mSelectIndex = mMouseOnIndex;
			mPanelOffset.y = (mSelectIndex + 1) * mTitleHeight;
		}
	}

	void FoldPanelImpl::OnMouseLevae( void )
	{
		mMouseOnIndex = -1;
	}

	IControl* FoldPanelImpl::HitTest( s32 x, s32 y, Vector2Dn& outPt )
	{
		if (!mIsVisible)
		{
			return NULL;
		}

		s32 tempX = x - mRect.pos.x;
		s32 tempY = y - mRect.pos.y;

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
}