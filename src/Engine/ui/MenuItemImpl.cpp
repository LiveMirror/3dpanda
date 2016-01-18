#include "MenuItemImpl.h"
#include "ui/Imenu.h"
#include "../renderSystem/Graph2D.h"
#include "uiManager.h"

namespace panda
{
	MenuItemImpl::MenuItemImpl( void )
		:mItemHeight(30),
		mChildHeight(0),
		mIsDelimiter(false),
		mMouseOn(false),
		mDrawChild(false),
		mMouseOnChild(NULL)
	{
		mRect.size = Size(120, 0);
		mBackColor = 0xff254e85;
		mBackColor2 = 0xff254e85;
		mDrawBorder = false;
	}

	IMenuItem* MenuItemImpl::AddItem( const tstring& text )
	{
		MenuItemImpl* impl = new MenuItemImpl;
		impl->mRect.pos.y = mChildHeight;
		if(text == _T("-"))
		{
			impl->mIsDelimiter = true;
			impl->mRect.size = Size(120, 3);
			mChildHeight += 3;
		}
		else
		{
			impl->mRect.size = Size(120, mItemHeight);
			mChildHeight += mItemHeight;
		}
		impl->mUiMgr = mUiMgr;
		impl->mText = text;
		impl->mParent = (IPanel*)mThis;
		impl->mFont = mFont;
		IMenuItem* item = new IMenuItem(impl);
		mChilds.push_back(item);
		
		return item;
	}

	void MenuItemImpl::Draw( Rect& rect, IGraph2D* graph )
	{
		Graph2D* g = (Graph2D*)graph;
		g->PushOffset(mRect.pos);
		mThis->OnRender(graph);

		if(mDrawChild && !mChilds.empty())
		{
			mShowX = mRect.size.width + 2;
			Vector2Dn curPos = g->GetOffset();
			if(curPos.x + mRect.size.width * 2 + 2 > mUiMgr->mClientRect.size.width)
			{
				mShowX = -mShowX;
			}
			mShowY = 0;
			if(curPos.y + mChildHeight > mUiMgr->mClientRect.size.height)
			{
				mShowY = -mChildHeight + mItemHeight;
			}
			Vector2Dn offset(mShowX, mShowY);
			g->PushOffset(offset);
			DrawChilds(0, 0, graph);
			g->PopOffset(offset);
		}

		if(mDrawBorder)
		{
			graph->DrawRect(0, 0, mRect.size.width, mChildHeight, mBorderColor, mBorderSize);
		}
		g->PopOffset(mRect.pos);
	}

	void MenuItemImpl::DrawChilds( s32 x, s32 y, IGraph2D* graph)
	{
		graph->FillRect(x, y, mRect.size.width, mChildHeight, mBackColor, mBackColor2);
		Color temp = mBorderColor;
		temp.A /= 2;
		graph->DrawRect(x - 1, y - 1, mRect.size.width + 2, mChildHeight + 2, temp, 2);
		graph->DrawRect(x, y, mRect.size.width, mChildHeight, mBorderColor, mBorderSize);
		IControl* pCtrl;
		CtrlList::iterator it = mChilds.begin();
		while (it != mChilds.end())
		{
			pCtrl = *it;
			pCtrl->mImpl->Draw(mRect, graph);
			it++;
		}
		
		
		
	}

	void MenuItemImpl::OnRender( IGraph2D* graph )
	{
		if(mIsDelimiter)
		{
			graph->DrawLine(5, 1, mRect.size.width - 5, 1, 0xff898989);
		}
		else
		{
			if(mDrawChild)
			{
				graph->FillRect(0, 0, mRect.size.width, mRect.size.height, 0x8f255ec5, 0xff255ec5);
			}
			graph->DrawString(mFont, 0, 0, mRect.size.width, mRect.size.height, mText, mTextColor);
			if(!mChilds.empty())
			{
				//graph->FillTriangle(mRect.size.width - 4, 2, mRect.size.width - 1, mRect.size.height / 2, mRect.size.width - 4, mRect.size.height - 2, 0xff787878);
				graph->DrawLine(mRect.size.width - 13, 10, mRect.size.width - 13, mRect.size.height - 10, 0xff787878);
				graph->DrawLine(mRect.size.width - 13, 10, mRect.size.width - 7, mRect.size.height / 2, 0xff787878);
				graph->DrawLine(mRect.size.width - 13, mRect.size.height - 10, mRect.size.width - 7, mRect.size.height / 2, 0xff787878);
			}
		}
		
	}

	IControl* MenuItemImpl::HitTest( s32 x, s32 y, Vector2Dn& outPt)
	{
		if(mDrawChild)
		{
			s32 tempX = x - mRect.pos.x;
			s32 tempY = y - mRect.pos.y;
			if(mRect.size.height > 0)
			{
				tempX -= mShowX;
				tempY -= mShowY;
			}
			CtrlList::iterator it = mChilds.begin();
			IControl* pCtrl;
			while (it != mChilds.end())
			{
				pCtrl = (*it)->mImpl->HitTest(tempX, tempY, outPt);
				if(NULL != pCtrl)
				{
					return pCtrl;
				}
				it++;
			}
		}
		if(mRect.IsPointIn(x, y))
		{
			return mThis;
		}
		return NULL;
	}

	void MenuItemImpl::OnMouseEnter()
	{
		mMouseOn = true;
		MenuItemImpl* parent = (MenuItemImpl*) mParent->mImpl;
		if(NULL != parent->mMouseOnChild)
		{
			parent->mMouseOnChild->ClearDrawChild();
		}
		parent->mMouseOnChild = this;
		mDrawChild = true;
	}

	void MenuItemImpl::OnMouseLevae()
	{
		mMouseOn = false;
	}

	void MenuItemImpl::ClearDrawChild( void )
	{
		mDrawChild = false;
		CtrlList::iterator it = mChilds.begin();
		MenuItemImpl* impl;
		while (it != mChilds.end())
		{
			impl = (MenuItemImpl*)(*it)->mImpl;
			impl->mDrawChild = false;
			it++;
		}
	}

	void MenuItemImpl::OnMouseClick(MouseEventArgs& e)
	{
		if(mChilds.empty() && !mIsDelimiter)
		{
			mUiMgr->SetPopUpCtrl(NULL);
			__super::OnMouseClick(e);
		}
	}
}