#include "ControlImpl.h"
#include "ui/IControl.h"
#include "ui/IPanel.h"
#include "../renderSystem/Graph2D.h"
#include "resources/ITexture.h"
#include "uiManager.h"
#include "PanelImpl.h"

namespace panda
{
	ControlImpl::ControlImpl( void )
		:mIsVisible(true),
		mBackColor(0x3f254e85),
		mBackColor2(0x8f2b7fdb),
		mBorderColor(0xff2b7fdb),
		mBorderSize(1),
		mTextColor(0xFFefeFef),
		mDrawBorder(true),
		mParent(NULL),
		mUiMgr(NULL),
		mIsFocus(false),
		mMouseOn(false),
		mEnable(true),
		mUserData(NULL)
	{
		mRect.size.width = 100;
		mRect.size.height = 25;
	}

	ControlImpl::~ControlImpl( void )
	{
		if(NULL != mParent)
		{
			mParent->RemoveChild(mThis);
			mParent = NULL;
		}
		else if(NULL != mUiMgr)
		{
			mUiMgr->RemoveCtrl(mThis);
		}
	}

	void ControlImpl::OnBindThis( IControl* pThis )
	{
		mThis = pThis;
	}

	

	void ControlImpl::Draw( Rect& rect, IGraph2D* graph )
	{
		// 控件不可见 不绘制
		// 与可见区域不相交，不绘制
		if(!mIsVisible || !rect.Intersect(mRect))
		{
			return;
		}

		Graph2D* g = (Graph2D*)graph;
		g->PushOffset(mRect.pos);
		mThis->OnRender(graph);
		if(mDrawBorder)
		{
			graph->DrawRect(0, 0, mRect.size.width, mRect.size.height, mBorderColor, mBorderSize);
		}
		g->PopOffset(mRect.pos);
	}

	void ControlImpl::OnRender( IGraph2D* graph )
	{

	}

	void ControlImpl::Update( s32 tick )
	{

	}

	void ControlImpl::SetSize( s32 width, s32 height )
	{
		s32 oldY = mRect.pos.y + mRect.size.height;
		mRect.size.width = width;
		mRect.size.height = height;
		if(NULL != mParent)
		{
			s32 curY = mRect.pos.y + height;
			PanelImpl* impl = (PanelImpl*)mParent->mImpl;
			impl->UpdateScrollValue(oldY, curY);
		}
	}

	void ControlImpl::SetPos( s32 x, s32 y )
	{
		s32 oldY = mRect.pos.y + mRect.size.height;
		mRect.pos.x = x;
		mRect.pos.y = y;
		if(NULL != mParent)
		{
			s32 curY = mRect.pos.y + mRect.size.height;
			PanelImpl* impl = (PanelImpl*)mParent->mImpl;
			impl->UpdateScrollValue(oldY, curY);
		}
	}

	IControl* ControlImpl::HitTest( s32 x, s32 y, Vector2Dn& outPt)
	{
		if (!mIsVisible)
		{
			return NULL;
		}
		if(mRect.IsPointIn(x, y))
		{
			outPt.x = x;
			outPt.y = y;
			outPt -= mRect.pos;
			return mThis;
		}
		return NULL;
	}

	void ControlImpl::OnMouseMove( MouseEventArgs& e )
	{

	}

	void ControlImpl::OnMouseEnter(void)
	{
		mMouseOn = true;
	}

	void ControlImpl::OnMouseLevae(void)
	{
		mMouseOn = false;
	}

	void ControlImpl::OnMouseDown( MouseEventArgs& e )
	{
		this->SetFocus();
	}

	void ControlImpl::OnMouseUp( MouseEventArgs& e )
	{

	}

	void ControlImpl::SetVisible( bool visible )
	{
		mIsVisible = visible;
	}

	void ControlImpl::SetFocus( void )
	{
		mUiMgr->SetFocus(mThis);
	}

	void ControlImpl::OnLostFocus( void )
	{
		
	}

	void ControlImpl::OnGotFocus( void )
	{
		
	}

	void ControlImpl::SetText( const tstring& text )
	{
		mText = text;
	}

	void ControlImpl::OnMouseClick(MouseEventArgs& e)
	{
		if(e.button & MouseButtons::LButton)
		{
			mOnClick(mThis);
		}
	}

	void ControlImpl::OnKeyDown( KeyEventArgs& e )
	{

	}

	void ControlImpl::OnChar( s32 key )
	{

	}

	Vector2Dn ControlImpl::PointToScreen( s32 x, s32 y, IControl* pChild/* = NULL*/)
	{
		Vector2Dn p(x, y);
		if(mParent != NULL)
		{
			p += mParent->mImpl->PointToScreen(mRect.pos.x, mRect.pos.y, mThis);
		}
		else
		{
			p += mRect.pos;
		}
		return p;
	}

	void ControlImpl::OnMouseHover( MouseEventArgs& e )
	{

	}

	void ControlImpl::OnBindUiMgr( uiManager* uiMgr )
	{
		mUiMgr = uiMgr;
	}

	bool ControlImpl::IsAncestor( IControl* pCtrl )
	{
		IPanel* parent = mParent;
		while(NULL != parent)
		{
			if (pCtrl == parent)
			{
				return true;
			}
			parent = parent->GetParent();
		}
		return false;
	}

	void ControlImpl::SetToolTip( const tstring& str )
	{
		mTipText = str;
	}

	const tstring& ControlImpl::GetToolTip( void ) const
	{
		return mTipText;
	}

	void ControlImpl::OnMouseDClick( MouseEventArgs& e )
	{

	}

	void ControlImpl::BringToFront( void )
	{
		if(NULL != mParent)
		{
			((PanelImpl*)mParent->mImpl)->BringToFront(mThis);
		}
		else
		{
			mUiMgr->BringToFront(mThis);
		}
	}

	void ControlImpl::SendToBack( void )
	{
		if(NULL != mParent)
		{
			((PanelImpl*)mParent->mImpl)->SendToBack(mThis);
		}
		else
		{
			mUiMgr->SendToBack(mThis);
		}
	}

	void ControlImpl::OnMouseWheel( MouseEventArgs& e )
	{

	}
}