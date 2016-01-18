#include "DialogImpl.h"
#include "renderSystem/IGraph2D.h"
#include "../renderSystem/Graph2D.h"
#include "ui/IControl.h"
#include "ui/IPanel.h"
#include "ui/IScrollBar.h"
#include "uiManager.h"


namespace panda
{
	DialogImpl::DialogImpl( void )
		:mTitleHeight(25),
		mMouseDown(false),
		mMoveDialog(false),
		mMouseOnCloseBtn(false),
		mMouseOnMinBtn(false),
		mColseBtnDown(false),
		mEnableMove(true),
		mMode(false)
	{
		mBackColor = 0xef254e85;
		mRect.size = Size(300, 200);
		mText = _T("Dialog");
	}

	void DialogImpl::Draw( Rect& rect, IGraph2D* graph )
	{
		if(!mIsVisible || !rect.Intersect(mRect))
		{
			return;
		}

		Graph2D* g = (Graph2D*)graph;
		g->PushOffset(mRect.pos);
		
		// 背景色
		graph->FillRect(0, 0, mRect.size.width, mRect.size.height, mBackColor);

		// 画标题栏
		OnRenderTitle(graph);

		// 画窗体
		Vector2Dn title(0, mTitleHeight);
		g->PushOffset(title);
		mThis->OnRender(graph);

		// 有滚动条,说明需要打开裁剪
		if(NULL != mScrollBar)
		{
			graph->ScissorEnable(true);
			Rect r(0, 0, mRect.size.width, mRect.size.height - mTitleHeight);
			graph->SetScissor(r);
		}

		Vector2Dn p(0, -mCurY);
		g->PushOffset(p);

		Rect r;
		r.size = mRect.size;
		IControl* pCtrl;
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			pCtrl = *it;
			pCtrl->mImpl->Draw(r, graph);
			it++;
		}

		g->PopOffset(p);

		if(NULL != mScrollBar)
		{
			mScrollBar->mImpl->Draw(r, graph);
		}

		g->PopOffset(title);

		if(NULL != mScrollBar)
		{
			graph->ScissorEnable(false);
		}

		if(mDrawBorder)
		{
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, mBorderColor, mBorderSize);
		}
		g->PopOffset(mRect.pos);
	}

	void DialogImpl::OnRenderTitle( IGraph2D* graph )
	{
		graph->FillRect(0, 0, mRect.size.width, mTitleHeight, mBackColor2);
		graph->DrawString(mFont, 0, 0, mRect.size.width, mTitleHeight, mText, mTextColor);
		graph->DrawLine(2, mTitleHeight, mRect.size.width - 3, mTitleHeight, mBorderColor);

		// min button
		/*graph->DrawLine(mRect.size.width - mTitleHeight * 2 + 6, mTitleHeight / 2, mRect.size.width - mTitleHeight - 6, mTitleHeight / 2, 0xffFFffFF, 1);
		if(mMouseOnMinBtn)
		{
			graph->DrawRect(mRect.size.width - mTitleHeight * 2 + 4, mTitleHeight / 3 - 4, 17, 16, mBorderColor);
		}*/

		// close button
		if(mMouseOnCloseBtn)
		{
			graph->FillRect(mRect.size.width - mTitleHeight + 4, mTitleHeight / 3 - 4, 17, 16, 0xafff0000);
			graph->DrawRect(mRect.size.width - mTitleHeight + 4, mTitleHeight / 3 - 4, 17, 16, mBorderColor);
		}
		graph->DrawLine(mRect.size.width - mTitleHeight + 6, mTitleHeight / 3, mRect.size.width - 6, mTitleHeight * 2 / 3, 0xffFFffFF, 1);
		graph->DrawLine(mRect.size.width - mTitleHeight + 6, mTitleHeight * 2 / 3, mRect.size.width - 6, mTitleHeight / 3, 0xffFFffFF, 1);
		
	}

	void DialogImpl::OnRender( IGraph2D* graph )
	{
		
	}

	void DialogImpl::OnMouseDown( MouseEventArgs& e )
	{
		__super::OnMouseDown(e);
		if(mMouseOnCloseBtn)
		{
			mColseBtnDown = true;
			return;
		}
		mColseBtnDown = false;

		if(e.y - mCurY <= 0)
		{
			mOldX = e.x;
			mOldY = e.y;
			mMoveDialog = true;
		}
		else
		{
			mMoveDialog = false;
		}
		mMouseDown = true;
	}

	void DialogImpl::OnMouseUp(MouseEventArgs& e )
	{
		__super::OnMouseUp(e);
		if(mMouseOnCloseBtn && mColseBtnDown)
		{
			CloseDlg();
			return;
		}
		mMouseDown = false;
		mMoveDialog = false;
	}



	void DialogImpl::OnMouseMove( MouseEventArgs& e )
	{
		mMouseOnCloseBtn = false;
		//mMouseOnMinBtn = false;
		if(mMoveDialog && mMouseDown && mEnableMove)
		{
			mRect.pos.x += (e.x - mOldX);
			mRect.pos.y += (e.y - mOldY);
		}
		else if(e.y - mCurY < -3  && e.y - mCurY > -mTitleHeight + 3)
		{
			/*if(x > mRect.size.width - mTitleHeight * 2 + 4 && x < mRect.size.width - mTitleHeight + 4 )
			{
				mMouseOnMinBtn = true;
			}
			else */if(e.x > mRect.size.width - mTitleHeight + 4 && e.x < mRect.size.width - 4)
			{
				mMouseOnCloseBtn = true;
			}
		}
	}

	IControl* DialogImpl::HitTest( s32 x, s32 y, Vector2Dn& outPt)
	{
		if (!mIsVisible)
		{
			return NULL;
		}

		s32 tempX = x - mRect.pos.x;
		s32 tempY = y - mRect.pos.y - mTitleHeight;

		if(tempY < 0 && mRect.IsPointIn(x, y))
		{
			outPt.x = tempX;
			outPt.y = tempY;
			return mThis;
		}

		IControl* pCtrl;
		if(NULL != mScrollBar)
		{
			pCtrl = mScrollBar->mImpl->HitTest(tempX, tempY, outPt);
			if(NULL != pCtrl)
			{
				return pCtrl;
			}
		}

		tempY += mCurY;
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			pCtrl = (*it)->mImpl->HitTest(tempX, tempY, outPt);
			if(NULL != pCtrl)
			{
				return pCtrl;
			}
			it++;
		}

		if(mRect.IsPointIn(x, y))
		{
			return mThis;
		}
		return NULL;
	}

	Vector2Dn DialogImpl::PointToScreen( s32 x, s32 y, IControl* pChild/* = NULL*/)
	{
		Vector2Dn p(x, y + mTitleHeight);
		if(pChild != mScrollBar)
		{
			p.y -= mCurY;
		}
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

	void DialogImpl::UpdateScrollValue( void )
	{
		s32 maxHeight = mRect.size.height - mTitleHeight;
		CtrlList::iterator it = mChilds.begin();
		IControl* pCtrl;
		while (it != mChilds.end())
		{
			pCtrl = *it;
			if(maxHeight < pCtrl->mImpl->mRect.size.height + pCtrl->mImpl->mRect.pos.y)
			{
				maxHeight = pCtrl->mImpl->mRect.size.height + pCtrl->mImpl->mRect.pos.y + 2;
			}
			it++;
		}
		mMaxHeight = maxHeight;
		if(maxHeight > mRect.size.height)
		{
			if(NULL == mScrollBar)
			{
				CreateScrollBar();
			}

			mScrollBar->SetSize(mScrollBar->GetSize().width, mRect.size.height - mTitleHeight);
			mScrollBar->SetPos(mRect.size.width -  mScrollBar->GetSize().width, 0);
			mScrollBar->SetMaximun(maxHeight);
		}
	}

	void DialogImpl::DoMode( void )
	{
		mMode = true;
		mIsVisible = true;
		mUiMgr->SetModeDialog((IDialog*)mThis);
	}

	void DialogImpl::CloseDlg( void )
	{
		mIsVisible = false;
		mMouseOnCloseBtn = false;
		if(mMode)
		{
			mUiMgr->SetModeDialog(NULL);
			mMode = false;
		}
		
	}
}
