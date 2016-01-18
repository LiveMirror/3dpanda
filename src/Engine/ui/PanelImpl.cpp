#include "PanelImpl.h"
#include "ui/IControl.h"
#include "../renderSystem/Graph2D.h"
#include "ui/IScrollBar.h"
#include "ui/IPanel.h"

namespace panda
{
	PanelImpl::PanelImpl( void )
		:mRadioButton(NULL),
		mScrollBar(NULL),
		mCurY(0),
		mScrollable(true)
	{
		mText = _T("Panel");
		mRect.size = Size(300, 200);
		mBackColor = 0x3f254e85;
		mBackColor2 = 0x6f254e85;
	}

	IControl* PanelImpl::HitTest( s32 x, s32 y, Vector2Dn& outPt)
	{
		if (!mIsVisible)
		{
			return NULL;
		}

		s32 tempX = x - mRect.pos.x;
		s32 tempY = y - mRect.pos.y;
		IControl* pCtrl;
		if(NULL != mScrollBar)
		{
			pCtrl = mScrollBar->mImpl->HitTest(tempX, tempY, outPt);
			if(NULL != pCtrl)
			{
				return pCtrl;
			}
		}

		if(mRect.IsPointIn(x, y))
		{
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

			outPt.x = x;
			outPt.y = y;
			outPt -= mRect.pos;
			return mThis;
		}
		return NULL;
	}

	void PanelImpl::Draw( Rect& rect, IGraph2D* graph )
	{
		// 控件不可见 不绘制
		// 与可见区域不相交，不绘制
		if(!mIsVisible || !rect.Intersect(mRect))
		{
			return;
		}

		// 有滚动条,说明需要打开裁剪
		if(NULL != mScrollBar)
		{
			graph->ScissorEnable(true);
			graph->SetScissor(mRect);
		}

		Graph2D* g = (Graph2D*)graph;
		g->PushOffset(mRect.pos);

		if(mBackColor.A > 0)
		{
			graph->FillRect(0, 0, mRect.size.width, mRect.size.height, mBackColor, mBackColor2);
		}

		Vector2Dn p(0, -mCurY);
		g->PushOffset(p);
		mThis->OnRender(graph);

		Rect r;
		r.size = mRect.size;
		r.pos.y = mCurY;
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
			r.pos.y = 0;
			mScrollBar->mImpl->Draw(r, graph);
			graph->ScissorEnable(false);
		}

		if(mDrawBorder)
		{
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, mBorderColor, mBorderSize);
		}
		g->PopOffset(mRect.pos);
	}

	void PanelImpl::OnRender( IGraph2D* graph )
	{
		
	}

	void PanelImpl::AddChild( IControl* ctrl )
	{
		ctrl->mImpl->mParent = (IPanel*)mThis;
		mChilds.push_back(ctrl);

		UpdateScrollValue();
	}

	void PanelImpl::Update( s32 tick )
	{
		if(NULL != mScrollBar)
		{
			mScrollBar->mImpl->Update(tick);
		}

		IControl* pCtrl;
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			pCtrl = *it;
			pCtrl->mImpl->Update(tick);
			it++;
		}
	}

	void PanelImpl::UpdateScrollValue( void )
	{
		if(!mScrollable)
		{
			return;
		}
		// 计算最高位置
		s32 maxHeight = mRect.size.height;
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
			else
			{
				mScrollBar->SetVisible(true);
			}

			mScrollBar->SetSize(mScrollBar->GetSize().width, mRect.size.height);
			mScrollBar->SetPos(mRect.size.width -  mScrollBar->GetSize().width, 0);
			mScrollBar->SetMaximun(maxHeight);
			mScrollBar->SetValue(0);
			mCurY = 0;
		}
		else
		{
			if(NULL != mScrollBar)
			{
				mScrollBar->SetVisible(false);
				mScrollBar->SetValue(0);
				mCurY = 0;
			}
		}
	}


	void PanelImpl::UpdateScrollValue( s32 oldY, s32 curY )
	{
		if(!mScrollable)
		{
			return;
		}
		if(oldY < mMaxHeight && curY > mMaxHeight)
		{
			mMaxHeight = curY + 2;
			if(NULL == mScrollBar)
			{
				CreateScrollBar();
			}

			mScrollBar->SetSize(mScrollBar->GetSize().width, mRect.size.height);
			mScrollBar->SetPos(mRect.size.width -  mScrollBar->GetSize().width, 0);
			mScrollBar->SetMaximun(mMaxHeight);
		}
		else if(oldY == mMaxHeight)
		{
			UpdateScrollValue();
		}
	}

	void PanelImpl::SetSize( s32 width, s32 height )
	{
		__super::SetSize(width, height);
		UpdateScrollValue();
	}

	bool PanelImpl::OnScrollChange( IControl* pCtrl, s32 x, s32 y )
	{
		mCurY = mScrollBar->GetValue();
		return true;
	}

	void PanelImpl::CreateScrollBar(void)
	{
		mScrollBar = new IScrollBar;
		mScrollBar->mImpl->OnBindUiMgr(mUiMgr);
		mScrollBar->mImpl->mParent = (IPanel*)mThis;
		mScrollBar->OnValueChange().Add(this, &PanelImpl::OnScrollChange);
	}

	Vector2Dn PanelImpl::PointToScreen( s32 x, s32 y, IControl* pChild/* = NULL*/)
	{
		Vector2Dn p(x, y);
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

	void PanelImpl::BringToFront( IControl* pCtrl )
	{
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			if(pCtrl == *it)
			{
				mChilds.erase(it);
				mChilds.push_back(pCtrl);
				return;
			}
			it++;
		}
	}

	void PanelImpl::SendToBack( IControl* pCtrl )
	{
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			if(pCtrl == *it)
			{
				mChilds.erase(it);
				mChilds.insert(mChilds.begin(), pCtrl);
				return;
			}
			it++;
		}
	}

	bool PanelImpl::HasChild( IControl* ctrl )
	{
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			if(ctrl == *it)
			{
				return true;
			}
			it++;
		}
		return false;
	}

	void PanelImpl::RemoveChild( IControl* ctrl )
	{
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			if(ctrl == *it)
			{
				mChilds.erase(it);
				return;
			}
			it++;
		}
	}

	void PanelImpl::OnMouseWheel( MouseEventArgs& e )
	{
		if(NULL != mScrollBar && mScrollBar->GetVisible())
		{
			mScrollBar->mImpl->OnMouseWheel(e);
		}
	}
}