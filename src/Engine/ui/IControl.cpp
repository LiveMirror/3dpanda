#include "ui/IControl.h"
#include "ControlImpl.h"
#include "resources/ITexture.h"
#include "ui/IPanel.h"
#include "uiManager.h"

namespace panda
{
	IControl::IControl( void )
	{
		mImpl = new ControlImpl;
		mImpl->OnBindThis(this);
	}

	IControl::IControl( ControlImpl* impl )
		:mImpl(impl)
	{
		if(NULL != mImpl)
		{
			mImpl->OnBindThis(this);
		}
	}
	IControl::~IControl( void )
	{
		if(NULL != mImpl)
		{
			delete mImpl;
		}
	}

	void IControl::OnRender( IGraph2D* grahp )
	{
		mImpl->OnRender(grahp);
	}

	void IControl::SetSize(const Size& size )
	{
		SetSize(size.width, size.height);
	}

	void IControl::SetSize( s32 width, s32 height )
	{
		mImpl->SetSize(width, height);
	}

	void IControl::SetPos( const Vector2Dn& pos )
	{
		SetPos(pos.x, pos.y);
	}

	void IControl::SetPos( s32 x, s32 y )
	{
		mImpl->SetPos(x, y);
	}

	void IControl::SetBackColor( Color c )
	{
		mImpl->mBackColor = c;
	}

	void IControl::SetBorderColor( Color c )
	{
		mImpl->mBorderColor = c;
	}

	void IControl::SetBorderSize( f32 width )
	{
		mImpl->mBorderSize = width;
	}

	void IControl::SetBackImage( ResTexture image )
	{
		mImpl->mBackImage = image;
		if(!image.IsNull())
		{
			image->Load();
		}
	}

	ResTexture IControl::GetBackImage( void ) const
	{
		return mImpl->mBackImage;
	}

	Vector2Dn IControl::PointToClient( s32 x, s32 y )
	{
		Vector2Dn p(x, y);
		p -= mImpl->PointToScreen(0, 0);
		return p;
	}

	Vector2Dn IControl::PointToScreen( s32 x, s32 y )
	{
		return mImpl->PointToScreen(x, y);
	}

	IPanel* IControl::GetParent( void )
	{
		return mImpl->mParent;
	}

	const Vector2Dn& IControl::GetPos( void ) const
	{
		return mImpl->mRect.pos;
	}

	void IControl::SetText( const tstring& str )
	{
		mImpl->SetText(str);
	}

	const tstring& IControl::GetText( void )
	{
		return mImpl->mText;
	}


	void IControl::Update( s32 tick )
	{

	}

	void IControl::RealeseCapture( void )
	{
		mImpl->mUiMgr->RealeseCapture();
	}

	EventMouse& IControl::OnMouseUp( void )
	{
		return mImpl->mOnMouseUp;
	}

	EventMouse& IControl::OnMouseClick( void )
	{
		return mImpl->mOnMouseClick;
	}

	void IControl::SetFocus( void )
	{
		return mImpl->SetFocus();
	}

	const Size& IControl::GetSize( void ) const
	{
		return mImpl->mRect.size;
	}

	void IControl::SetToolTip( const tstring& str )
	{
		mImpl->SetToolTip(str);
	}

	const tstring& IControl::GetToolTip( void )const
	{
		return mImpl->GetToolTip();
	}

	EventMouse& IControl::OnMouseDown( void )
	{
		return mImpl->mOnMouseDown;
	}

	void IControl::SetVisible( bool visible )
	{
		mImpl->mIsVisible = visible;
	}

	bool IControl::GetVisible( void ) const
	{
		return mImpl->mIsVisible;
	}

	void IControl::SetEnable( bool enable )
	{
		mImpl->mEnable = enable;
	}

	bool IControl::GetEnable( void ) const
	{
		return mImpl->mEnable;
	}

	void IControl::BringToFront( void )
	{
		mImpl->BringToFront();
	}

	void IControl::SendToBack( void )
	{
		mImpl->SendToBack();
	}

	void IControl::SetUserData( s32 data )
	{
		mImpl->mUserData = data;
	}

	s32 IControl::GetUserData( void ) const
	{
		return mImpl->mUserData;
	}

	IUiManager* IControl::GetUiMgr( void )
	{
		return mImpl->mUiMgr;
	}

	void IControl::SetDrawBorder( bool draw )
	{
		mImpl->mDrawBorder = draw;
	}

	bool IControl::GetDrawBorder( void ) const
	{
		return mImpl->mDrawBorder;
	}

	EventCtrl& IControl::OnClick( void )
	{
		return mImpl->mOnClick;
	}

	EventMouse& IControl::OnMouseMove( void )
	{
		return mImpl->mOnMouseMove;
	}

	EventMouse& IControl::OnMouseWheel( void )
	{
		return mImpl->mOnMouseWheel;
	}

	EventCtrl& IControl::OnLostFocus( void )
	{
		return mImpl->mOnLostFocus;
	}

	EventKey& IControl::OnKeyDown( void )
	{
		return mImpl->mOnKeyDown;
	}
}